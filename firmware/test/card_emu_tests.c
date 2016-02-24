#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "card_emu.h"
#include "cardemu_prot.h"
#include "tc_etu.h"
#include "req_ctx.h"

/* stub functions required by card_emu.c */

int card_emu_uart_update_fidi(uint8_t uart_chan, unsigned int fidi)
{
	printf("uart_update_fidi(uart_chan=%u, fidi=%u)\n", uart_chan, fidi);
	return 0;
}

int card_emu_uart_tx(uint8_t uart_chan, uint8_t byte)
{
	printf("UART_TX(%02x)\n", byte);
	return 1;
}

void card_emu_uart_enable(uint8_t uart_chan, uint8_t rxtx)
{
	char *rts;
	switch (rxtx) {
	case 0:
		rts = "OFF";
		break;
	case ENABLE_TX:
		rts = "TX";
		break;
	case ENABLE_RX:
		rts = "RX";
		break;
	default:
		rts = "unknown";
		break;
	};

	printf("uart_enable(uart_chan=%u, %s)\n", uart_chan, rts);
}

void tc_etu_set_wtime(uint8_t tc_chan, uint16_t wtime)
{
	printf("tc_etu_set_wtime(tc_chan=%u, wtime=%u)\n", tc_chan, wtime);
}

void tc_etu_set_etu(uint8_t tc_chan, uint16_t etu)
{
	printf("tc_etu_set_etu(tc_chan=%u, etu=%u)\n", tc_chan, etu);
}

void tc_etu_init(uint8_t chan_nr, void *handle)
{
	printf("tc_etu_init(tc_chan=%u)\n", chan_nr);
}

void tc_etu_enable(uint8_t chan_nr)
{
	printf("tc_etu_enable(tc_chan=%u)\n", chan_nr);
}

void tc_etu_disable(uint8_t chan_nr)
{
	printf("tc_etu_disable(tc_chan=%u)\n", chan_nr);
}


#if 0
/* process a single byte received from the reader */
void card_emu_process_rx_byte(struct card_handle *ch, uint8_t byte);

/* hardware driver informs us that a card I/O signal has changed */
void card_emu_io_statechg(struct card_handle *ch, enum card_io io, int active);

/* User sets a new ATR to be returned during next card reset */
int card_emu_set_atr(struct card_handle *ch, const uint8_t *atr, uint8_t len);
#endif


static int verify_atr(struct card_handle *ch)
{
	uint8_t atr[4];
	uint8_t byte;
	unsigned int i;

	printf("receiving + verifying ATR:\n");
	for (i = 0; i < sizeof(atr); i++) {
		assert(card_emu_tx_byte(ch) == 1);
	}
	assert(card_emu_tx_byte(ch) == 0);

	return 1;
}

static void io_start_card(struct card_handle *ch)
{
	/* bring the card up from the dead */
	card_emu_io_statechg(ch, CARD_IO_VCC, 1);
	assert(card_emu_tx_byte(ch) == 0);
	card_emu_io_statechg(ch, CARD_IO_CLK, 1);
	assert(card_emu_tx_byte(ch) == 0);
	card_emu_io_statechg(ch, CARD_IO_RST, 1);
	assert(card_emu_tx_byte(ch) == 0);

	/* release from reset and verify th ATR */
	card_emu_io_statechg(ch, CARD_IO_RST, 0);
	verify_atr(ch);
}

static void send_bytes(struct card_handle *ch, const uint8_t *bytes, unsigned int len)
{
	unsigned int i;
	for (i = 0; i < len; i++) {
		printf("UART_RX(%02x)\n", bytes[i]);
		card_emu_process_rx_byte(ch, bytes[i]);
	}
}

static void dump_rctx(struct req_ctx *rctx)
{
	struct cardemu_usb_msg_hdr *mh =
		(struct cardemu_usb_msg_hdr *) rctx->data;
	struct cardemu_usb_msg_rx_data *rxd;
	int i;

	printf("req_ctx(%p): state=%u, size=%u, tot_len=%u, idx=%u, data=%p\n",
		rctx, rctx->state, rctx->size, rctx->tot_len, rctx->idx, rctx->data);
	printf("  msg_type=%u, seq_nr=%u, data_len=%u\n",
		mh->msg_type, mh->seq_nr, mh->data_len);

	switch (mh->msg_type) {
	case CEMU_USB_MSGT_DO_RX_DATA:
		rxd = (struct cardemu_usb_msg_rx_data *)mh;
		printf("    flags=%x, data=", rxd->flags);
		for (i = 0; i < mh->data_len; i++)
			printf(" %02x", rxd->data[i]);
		printf("\n");
		break;
	}
}

/* emulate a TPDU header being sent by the reader/phone */
static void send_tpdu_hdr(struct card_handle *ch, const uint8_t *tpdu_hdr)
{
	struct req_ctx *rctx;

	/* we don't want a receive context to become available during
	 * the first four bytes */
	send_bytes(ch, tpdu_hdr, 4);
	assert(!req_ctx_find_get(0, RCTX_S_USB_TX_PENDING, RCTX_S_USB_TX_BUSY));

	send_bytes(ch, tpdu_hdr+4, 1);
	/* but then after the final byte of the TPDU header, we want a
	 * receive context to be available for USB transmission */
	rctx = req_ctx_find_get(0, RCTX_S_USB_TX_PENDING, RCTX_S_USB_TX_BUSY);
	assert(rctx);
	dump_rctx(rctx);

	/* free the req_ctx, indicating it has fully arrived on the host */
	req_ctx_set_state(rctx, RCTX_S_FREE);
}

/* emulate a CEMU_USB_MSGT_DT_TX_DATA received from USB */
static void host_to_device_data(const uint8_t *data, uint16_t len, int continue_rx)
{
	struct req_ctx *rctx;
	struct cardemu_usb_msg_tx_data *rd;

	/* allocate a free req_ctx */
	rctx = req_ctx_find_get(0, RCTX_S_FREE, RCTX_S_USB_RX_BUSY);
	assert(rctx);

	/* initialize the header */
	rd = (struct cardemu_usb_msg_rx_data *) rctx->data;
	rctx->tot_len = sizeof(*rd);
	cardemu_hdr_set(&rd->hdr, CEMU_USB_MSGT_DT_TX_DATA);
	rd->flags = CEMU_DATA_F_FINAL;
	if (continue_rx)
		rd->flags |= CEMU_DATA_F_PB_AND_RX;
	else
		rd->flags |= CEMU_DATA_F_PB_AND_TX;
	/* copy data and set length */
	rd->hdr.data_len = len;
	memcpy(rd->data, data, len);

	/* hand the req_ctx to the UART transmit code */
	req_ctx_set_state(rctx, RCTX_S_UART_TX_PENDING);
}

static int print_tx_chars(struct card_handle *ch)
{
	uint8_t byte;
	int count = 0;

	while (card_emu_tx_byte(ch)) {
		count++;
	}
	return count;
}

const uint8_t tpdu_hdr_sel_mf[] = { 0xA0, 0xA4, 0x00, 0x00, 0x00 };
const uint8_t tpdu_pb_sw[] = { 0x90, 0x00 };

const uint8_t tpdu_hdr_upd_bin[] = { 0xA0, 0xB2, 0x00, 0x00, 0x0A };
const uint8_t tpdu_body_upd_bin[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };

int main(int argc, char **argv)
{
	struct card_handle *ch;
	struct req_ctx *rctx;
	unsigned int i;

	req_ctx_init();

	ch = card_emu_init(0, 23, 42);
	assert(ch);

	/* start up the card (VCC/RST, ATR) */
	io_start_card(ch);
	assert(!print_tx_chars(ch));

	for (i = 0; i < 2; i++) {
		printf("\n==> transmitting APDU (SW 90 00 #%u)\n", i);
		/* emulate the reader sending a TPDU header */
		send_tpdu_hdr(ch, tpdu_hdr_sel_mf);
		assert(!print_tx_chars(ch));
		/* card emulator sends a response via USB */
		host_to_device_data(tpdu_pb_sw, sizeof(tpdu_pb_sw), 0);
		/* obtain any pending tx chars */
		assert(print_tx_chars(ch) == sizeof(tpdu_pb_sw));

		/* simulate some clock stop */
		card_emu_io_statechg(ch, CARD_IO_CLK, 0);
		card_emu_io_statechg(ch, CARD_IO_CLK, 1);
	}

	for (i = 0; i < 2; i++) {
		printf("\n==> transmitting APDU (PB + RX #%u)\n", i);
		/* emulate the reader sending a TPDU header */
		send_tpdu_hdr(ch, tpdu_hdr_upd_bin);
		assert(!print_tx_chars(ch));
		/* card emulator sends a response via USB */
		host_to_device_data(tpdu_hdr_upd_bin+1, 1, 1);
		/* obtain any pending tx chars */
		assert(print_tx_chars(ch) == 1);

		/* emulate more characters from reader to card */
		send_bytes(ch, tpdu_body_upd_bin, sizeof(tpdu_body_upd_bin));

		/* check if we have received them on the USB side */
		rctx = req_ctx_find_get(0, RCTX_S_USB_TX_PENDING, RCTX_S_USB_TX_BUSY);
		assert(rctx);
		dump_rctx(rctx);
		req_ctx_set_state(rctx, RCTX_S_FREE);

		/* ensure there is no extra data received on usb */
		assert(!req_ctx_find_get(0, RCTX_S_USB_TX_PENDING, RCTX_S_USB_TX_BUSY));

		/* card emulator sends SW via USB */
		host_to_device_data(tpdu_pb_sw, sizeof(tpdu_pb_sw), 0);
		/* obtain any pending tx chars */
		assert(print_tx_chars(ch) == sizeof(tpdu_pb_sw));

		/* simulate some clock stop */
		card_emu_io_statechg(ch, CARD_IO_CLK, 0);
		card_emu_io_statechg(ch, CARD_IO_CLK, 1);
	}

	exit(0);
}
