/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "utils.h"

#include <cciddriverdescriptors.h>

/*------------------------------------------------------------------------------
 *       USB String descriptors 
 *------------------------------------------------------------------------------*/


static const unsigned char langDesc[] = {

    USBStringDescriptor_LENGTH(1),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_ENGLISH_US
};

const unsigned char manufStringDescriptor[] = {

    USBStringDescriptor_LENGTH(24),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('s'),
    USBStringDescriptor_UNICODE('y'),
    USBStringDescriptor_UNICODE('s'),
    USBStringDescriptor_UNICODE('m'),
    USBStringDescriptor_UNICODE('o'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('o'),
    USBStringDescriptor_UNICODE('m'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('-'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('s'),
    USBStringDescriptor_UNICODE('.'),
    USBStringDescriptor_UNICODE('f'),
    USBStringDescriptor_UNICODE('.'),
    USBStringDescriptor_UNICODE('m'),
    USBStringDescriptor_UNICODE('.'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('.'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('G'),
    USBStringDescriptor_UNICODE('m'),
    USBStringDescriptor_UNICODE('b'),
    USBStringDescriptor_UNICODE('H'),
};

const unsigned char productStringDescriptor[] = {

    USBStringDescriptor_LENGTH(10),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('t'),
    USBStringDescriptor_UNICODE('r'),
    USBStringDescriptor_UNICODE('a'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('e'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('2'),
};

const unsigned char snifferConfigStringDescriptor[] = {

    USBStringDescriptor_LENGTH(16),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('t'),
    USBStringDescriptor_UNICODE('r'),
    USBStringDescriptor_UNICODE('a'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('e'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('n'),
    USBStringDescriptor_UNICODE('i'),
    USBStringDescriptor_UNICODE('f'),
    USBStringDescriptor_UNICODE('f'),
    USBStringDescriptor_UNICODE('e'),
    USBStringDescriptor_UNICODE('r'),
};

const unsigned char CCIDConfigStringDescriptor[] = {

    USBStringDescriptor_LENGTH(13),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('t'),
    USBStringDescriptor_UNICODE('r'),
    USBStringDescriptor_UNICODE('a'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('e'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('C'),
    USBStringDescriptor_UNICODE('C'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('D'),
};

const unsigned char phoneConfigStringDescriptor[] = {

    USBStringDescriptor_LENGTH(14),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('t'),
    USBStringDescriptor_UNICODE('r'),
    USBStringDescriptor_UNICODE('a'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('e'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('P'),
    USBStringDescriptor_UNICODE('h'),
    USBStringDescriptor_UNICODE('o'),
    USBStringDescriptor_UNICODE('n'),
    USBStringDescriptor_UNICODE('e'),
};


const unsigned char MITMConfigStringDescriptor[] = {

    USBStringDescriptor_LENGTH(13),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('t'),
    USBStringDescriptor_UNICODE('r'),
    USBStringDescriptor_UNICODE('a'),
    USBStringDescriptor_UNICODE('c'),
    USBStringDescriptor_UNICODE('e'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('M'),
};

enum strDescNum {
    PRODUCT_STRING = 1, MANUF_STR, SNIFFER_CONF_STR, CCID_CONF_STR, PHONE_CONF_STR, MITM_CONF_STR, STRING_DESC_CNT
};

/** List of string descriptors used by the device */
static const unsigned char *stringDescriptors[] = {
    langDesc,
    [PRODUCT_STRING]	= productStringDescriptor,
    [MANUF_STR]	= manufStringDescriptor,
    [SNIFFER_CONF_STR] 	= snifferConfigStringDescriptor,
    [CCID_CONF_STR] 	= CCIDConfigStringDescriptor,
    [PHONE_CONF_STR]	= phoneConfigStringDescriptor,
    [MITM_CONF_STR]	= MITMConfigStringDescriptor
};

/*------------------------------------------------------------------------------
 *       USB Device descriptors 
 *------------------------------------------------------------------------------*/

#ifdef HAVE_SNIFFER
typedef struct _SIMTraceDriverConfigurationDescriptorSniffer {

    /** Standard configuration descriptor. */
    USBConfigurationDescriptor  configuration;
    USBInterfaceDescriptor      sniffer;
    USBEndpointDescriptor       sniffer_dataOut;
    USBEndpointDescriptor       sniffer_dataIn;
    USBEndpointDescriptor       sniffer_interruptIn;

} __attribute__ ((packed)) SIMTraceDriverConfigurationDescriptorSniffer;

static const SIMTraceDriverConfigurationDescriptorSniffer configurationDescriptorSniffer = {
    /* Standard configuration descriptor */
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_CONFIGURATION,
        sizeof(SIMTraceDriverConfigurationDescriptorSniffer),
        1, /* There is one interface in this configuration */
        CFG_NUM_SNIFF, /* configuration number */
        SNIFFER_CONF_STR, /* string descriptor for this configuration */
        USBD_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    /* Communication class interface standard descriptor */
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0, /* This is interface #0 */
        0, /* This is alternate setting #0 for this interface */
        3, /* Number of endpoints */
        0xff, /* Descriptor Class: Vendor specific */
        0, /* No subclass */
        0, /* No l */
        SNIFFER_CONF_STR  /* Third in string descriptor for this interface */
    },
    /* Bulk-OUT endpoint standard descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT,
                                      PHONE_DATAOUT),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_DATAOUT),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0 /* Must be 0 for full-speed bulk endpoints */
    },
    /* Bulk-IN endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
                                      PHONE_DATAIN),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_DATAIN),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0 /* Must be 0 for full-speed bulk endpoints */
    },
    // Notification endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, PHONE_INT ),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_INT),
            USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
        0x10
    }
};
#endif /* HAVE_SNIFFER */


#ifdef HAVE_CCID
/*
/// CCIDDriverConfiguration Descriptors
/// List of descriptors that make up the configuration descriptors of a
/// device using the CCID driver.
typedef struct {

    /// Configuration descriptor
    USBConfigurationDescriptor configuration;
    /// Interface descriptor
    USBInterfaceDescriptor     interface;
    /// CCID descriptor
    CCIDDescriptor             ccid;
    /// Bulk OUT endpoint descriptor
    USBEndpointDescriptor      bulkOut;
    /// Bulk IN endpoint descriptor
    USBEndpointDescriptor      bulkIn;
    /// Interrupt OUT endpoint descriptor
    USBEndpointDescriptor      interruptIn;
} __attribute__ ((packed)) CCIDDriverConfigurationDescriptors;
*/

static const CCIDDriverConfigurationDescriptors configurationDescriptorCCID = {

    // Standard USB configuration descriptor
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_CONFIGURATION,
        sizeof(CCIDDriverConfigurationDescriptors),
        1, // One interface in this configuration
        CFG_NUM_CCID, // This is configuration #1
        CCID_CONF_STR, // associated string descriptor
        BOARD_USB_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    // CCID interface descriptor
    // Table 4.3-1 Interface Descriptor
    // Interface descriptor
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0,                       // Interface 0
        0,                       // No alternate settings
        3,                       // uses bulk-IN, bulk-OUT and interrupt IN
        SMART_CARD_DEVICE_CLASS,
        0,                       // Subclass code
        0,                       // bulk transfers optional interrupt-IN
        CCID_CONF_STR            // associated string descriptor
    },
    {
        sizeof(CCIDDescriptor), // bLength: Size of this descriptor in bytes
        CCID_DECRIPTOR_TYPE,    // bDescriptorType:Functional descriptor type
        CCID1_10,               // bcdCCID: CCID version
        0,               // bMaxSlotIndex: Value 0 indicates that one slot is supported
        VOLTS_3_0,       // bVoltageSupport
        (1 << PROTOCOL_TO),     // dwProtocols
        3580,            // dwDefaultClock
        3580,            // dwMaxClock
        0,               // bNumClockSupported
        9600,            // dwDataRate : 9600 bauds
        9600,            // dwMaxDataRate : 9600 bauds
        0,               // bNumDataRatesSupported
        0xfe,            // dwMaxIFSD
        0,               // dwSynchProtocols
        0,               // dwMechanical
        //0x00010042,      // dwFeatures: Short APDU level exchanges
        CCID_FEATURES_AUTO_CLOCK | CCID_FEATURES_AUTO_BAUD |
        CCID_FEATURES_AUTO_PCONF | CCID_FEATURES_AUTO_PNEGO | CCID_FEATURES_EXC_TPDU,
        0x0000010F,      // dwMaxCCIDMessageLength: For extended APDU level the value shall be between 261 + 10
        0xFF,            // bClassGetResponse: Echoes the class of the APDU
        0xFF,            // bClassEnvelope: Echoes the class of the APDU
        0,               // wLcdLayout: no LCD
        0,               // bPINSupport: No PIN
        1                // bMaxCCIDBusySlot
    },
    // Bulk-OUT endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_OUT, CCID_EPT_DATA_OUT ),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(CCID_EPT_DATA_OUT),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0x00                               // Does not apply to Bulk endpoints
    },
    // Bulk-IN endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, CCID_EPT_DATA_IN ),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(CCID_EPT_DATA_IN),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0x00                               // Does not apply to Bulk endpoints
    },
    // Notification endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, CCID_EPT_NOTIFICATION ),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(CCID_EPT_NOTIFICATION),
            USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
        0x10                              
    },
};
#endif /* HAVE_CCID */


#ifdef HAVE_CARDEM
/* SIM card emulator */
typedef struct _SIMTraceDriverConfigurationDescriptorPhone {

    /** Standard configuration descriptor. */
    USBConfigurationDescriptor  configuration;
    USBInterfaceDescriptor      phone;
    USBEndpointDescriptor       phone_dataOut;
    USBEndpointDescriptor       phone_dataIn;
    USBEndpointDescriptor       phone_interruptIn;
} __attribute__ ((packed)) SIMTraceDriverConfigurationDescriptorPhone;

static const SIMTraceDriverConfigurationDescriptorPhone configurationDescriptorPhone = {
    /* Standard configuration descriptor */
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_CONFIGURATION,
        sizeof(SIMTraceDriverConfigurationDescriptorPhone),
        1, /* There is one interface in this configuration */
        CFG_NUM_PHONE, /* configuration number */
        PHONE_CONF_STR, /* string descriptor for this configuration */
        USBD_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    /* Communication class interface standard descriptor */
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0, /* This is interface #0 */
        0, /* This is alternate setting #0 for this interface */
        3, /* Number of endpoints */
        0xff, /* Descriptor Class: Vendor specific */
        0, /* No subclass */
        0, /* No l */
        PHONE_CONF_STR  /* Third in string descriptor for this interface */
    },
    /* Bulk-OUT endpoint standard descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT,
                                      PHONE_DATAOUT),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_DATAOUT),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0 /* Must be 0 for full-speed bulk endpoints */
    },
    /* Bulk-IN endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
                                      PHONE_DATAIN),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_DATAIN),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0 /* Must be 0 for full-speed bulk endpoints */
    },
    /* Notification endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, PHONE_INT ),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_INT),
            USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
        0x10
    }
};
#endif /* HAVE_CARDEM */

#ifdef HAVE_MITM
typedef struct _SIMTraceDriverConfigurationDescriptorMITM {

    /** Standard configuration descriptor. */
    USBConfigurationDescriptor  configuration;
    USBInterfaceDescriptor      simcard;
    /// CCID descriptor
    CCIDDescriptor              ccid;
    /// Bulk OUT endpoint descriptor
    USBEndpointDescriptor       simcard_dataOut;
    /// Bulk IN endpoint descriptor
    USBEndpointDescriptor       simcard_dataIn;
    /// Interrupt OUT endpoint descriptor
    USBEndpointDescriptor       simcard_interruptIn;

    USBInterfaceDescriptor      phone;
    USBEndpointDescriptor       phone_dataOut;
    USBEndpointDescriptor       phone_dataIn;
    USBEndpointDescriptor       phone_interruptIn;

} __attribute__ ((packed)) SIMTraceDriverConfigurationDescriptorMITM;

static const SIMTraceDriverConfigurationDescriptorMITM configurationDescriptorMITM = {
    /* Standard configuration descriptor */
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_CONFIGURATION,
        sizeof(SIMTraceDriverConfigurationDescriptorMITM),
        2, /* There are two interfaces in this configuration */
        CFG_NUM_MITM, /* configuration number */
        MITM_CONF_STR, /* string descriptor for this configuration */
        USBD_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    // CCID interface descriptor
    // Table 4.3-1 Interface Descriptor
    // Interface descriptor
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0,                       // Interface 0
        0,                       // No alternate settings
        3,                       // uses bulk-IN, bulk-OUT and interrupt IN
        SMART_CARD_DEVICE_CLASS,
        0,                       // Subclass code
        0,                       // bulk transfers optional interrupt-IN
        CCID_CONF_STR            // associated string descriptor
    },
    {
        sizeof(CCIDDescriptor), // bLength: Size of this descriptor in bytes
        CCID_DECRIPTOR_TYPE,    // bDescriptorType:Functional descriptor type
        CCID1_10,               // bcdCCID: CCID version
        0,               // bMaxSlotIndex: Value 0 indicates that one slot is supported
        VOLTS_3_0,       // bVoltageSupport
        (1 << PROTOCOL_TO),     // dwProtocols
        3580,            // dwDefaultClock
        3580,            // dwMaxClock
        0,               // bNumClockSupported
        9600,            // dwDataRate : 9600 bauds
        9600,            // dwMaxDataRate : 9600 bauds
        0,               // bNumDataRatesSupported
        0xfe,            // dwMaxIFSD
        0,               // dwSynchProtocols
        0,               // dwMechanical
        //0x00010042,      // dwFeatures: Short APDU level exchanges
        CCID_FEATURES_AUTO_CLOCK | CCID_FEATURES_AUTO_BAUD |
        CCID_FEATURES_AUTO_PCONF | CCID_FEATURES_AUTO_PNEGO | CCID_FEATURES_EXC_TPDU,
        0x0000010F,      // dwMaxCCIDMessageLength: For extended APDU level the value shall be between 261 + 10
        0xFF,            // bClassGetResponse: Echoes the class of the APDU
        0xFF,            // bClassEnvelope: Echoes the class of the APDU
        0,               // wLcdLayout: no LCD
        0,               // bPINSupport: No PIN
        1                // bMaxCCIDBusySlot
    },
    // Bulk-OUT endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_OUT, CCID_EPT_DATA_OUT ),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(CCID_EPT_DATA_OUT),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0x00                               // Does not apply to Bulk endpoints
    },
    // Bulk-IN endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, CCID_EPT_DATA_IN ),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(CCID_EPT_DATA_IN),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0x00                               // Does not apply to Bulk endpoints
    },
    // Notification endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, CCID_EPT_NOTIFICATION ),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(CCID_EPT_NOTIFICATION),
            USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
        0x10
    },
    /* Communication class interface standard descriptor */
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        1, /* This is interface #1 */
        0, /* This is alternate setting #0 for this interface */
        3, /* Number of endpoints */
        0xff,
        0,
        0,
        PHONE_CONF_STR, /* string descriptor for this interface */
    },
    /* Bulk-OUT endpoint standard descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT,
                                      PHONE_DATAOUT),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_DATAOUT),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0 /* Must be 0 for full-speed bulk endpoints */
    },
    /* Bulk-IN endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
                                      PHONE_DATAIN),
        USBEndpointDescriptor_BULK,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_DATAIN),
            USBEndpointDescriptor_MAXBULKSIZE_FS),
        0 /* Must be 0 for full-speed bulk endpoints */
    },
    /* Notification endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS( USBEndpointDescriptor_IN, PHONE_INT ),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(PHONE_INT),
            USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
        0x10
    }
};
#endif /* HAVE_CARDEM */

const USBConfigurationDescriptor *configurationDescriptorsArr[] = {
#ifdef HAVE_SNIFFER
    &configurationDescriptorSniffer.configuration,
#endif
#ifdef HAVE_CCID
    &configurationDescriptorCCID.configuration,
#endif
#ifdef HAVE_CARDEM
    &configurationDescriptorPhone.configuration,
#endif
#ifdef HAVE_MITM
    &configurationDescriptorMITM.configuration,
#endif
};

/** Standard USB device descriptor for the CDC serial driver */
const USBDeviceDescriptor deviceDescriptor = {

    sizeof(USBDeviceDescriptor),
    USBGenericDescriptor_DEVICE,
    USBDeviceDescriptor_USB2_00,
    0xff,
//    CDCDeviceDescriptor_CLASS,
    0xff,
//    CDCDeviceDescriptor_SUBCLASS,
    0xff,
//    CDCDeviceDescriptor_PROTOCOL,
    BOARD_USB_ENDPOINTS_MAXPACKETSIZE(0),
    SIMTRACE_VENDOR_ID,
    SIMTRACE_PRODUCT_ID,
    1, /* Release number */
    MANUF_STR, /* Indesx of manufacturer string descriptor */
    PRODUCT_STRING, /* Index of product string descriptor */
    0, /* No string descriptor for serial number */
    ARRAY_SIZE(configurationDescriptorsArr) /* Device has N possible configs */
};

/* AT91SAM3S only supports full speed, but not high speed USB */
static const USBDDriverDescriptors driverDescriptors = {
    &deviceDescriptor,
    (const USBConfigurationDescriptor **) &(configurationDescriptorsArr),   /* first full-speed configuration descriptor */
    0, /* No full-speed device qualifier descriptor */
    0, /* No full-speed other speed configuration */
    0, /* No high-speed device descriptor */
    0, /* No high-speed configuration descriptor */
    0, /* No high-speed device qualifier descriptor */
    0, /* No high-speed other speed configuration descriptor */
    stringDescriptors,
    STRING_DESC_CNT /* cnt string descriptors in list */
};


/*----------------------------------------------------------------------------
 *        Functions 
 *----------------------------------------------------------------------------*/

/**
 * \brief Configure 48MHz Clock for USB
 */
static void _ConfigureUsbClock(void)
{
    /* Enable PLLB for USB */
    PMC->CKGR_PLLBR = CKGR_PLLBR_DIVB(5)
                    | CKGR_PLLBR_MULB(0xc)  /* MULT+1=0xd*/
                    | CKGR_PLLBR_PLLBCOUNT_Msk;
    while((PMC->PMC_SR & PMC_SR_LOCKB) == 0);
    /* USB Clock uses PLLB */
    PMC->PMC_USB = PMC_USB_USBDIV(0)       /* /1 (no divider)  */
                 | PMC_USB_USBS;           /* PLLB */
}


void SIMtrace_USB_Initialize( void )
{
    _ConfigureUsbClock();
    // Get std USB driver
    USBDDriver *pUsbd = USBD_GetDriver();

    TRACE_DEBUG(".");

    // Initialize standard USB driver
    USBDDriver_Initialize(pUsbd,
                          &driverDescriptors,
                          0); // Multiple interface settings not supported
    USBD_Init();
    USBD_Connect();

    NVIC_EnableIRQ( UDP_IRQn );
}
