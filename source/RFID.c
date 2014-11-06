#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "Reader/Reader.h"
#include "usbdrv/usbdrv.h"

const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = { /* USB report descriptor */
        0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,                    // USAGE (Keyboard)
        0xa1, 0x01,                    // COLLECTION (Application)
        0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
        0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,                    //   REPORT_SIZE (1)
        0x95, 0x08,                    //   REPORT_COUNT (8)
        0x81, 0x02,                    //   INPUT (Data,Var,Abs)
        0x95, 0x01,                    //   REPORT_COUNT (1)
        0x75, 0x08,                    //   REPORT_SIZE (8)
        0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
        0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
        0xc0                           // END_COLLECTION
    };

static uchar    reportBuffer[2];    /* buffer for HID reports */
static uchar    idleRate;           /* in 4 ms units */

uchar   usbFunctionSetup(uchar data[8])
{
    usbRequest_t    *rq = (void *)data;

    usbMsgPtr = reportBuffer;
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            /* we only have one report type, so don't look at wValue */
            return sizeof(reportBuffer);
        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }
    }else{
        /* no vendor specific requests implemented */
    }
    return 0;
}

int main(void)
{
    // ID for comparison
    uint32_t goodUser = 0x00000000;

    // Turbo charge internal clock to ~20 MHz (this value will differ for each chip)
    OSCCAL = 118;

    // PINB1 AND PINB0 as outputs
    DDRB |= 0b11;

    // Turn of RF front-end (fancy effects)
    PORTB |= (1 << PINB1);
    PORTB &= ~1;

    // Disconect USB device
    usbDeviceDisconnect();

    _delay_ms(300);

    PORTB &= ~(1 << PINB1);
    usbDeviceConnect();

    wdt_enable(WDTO_1S);

    usbInit();

    // Enable interrupts
    GIMSK |= (1 << PCIE);
    MCUCR |= (1 << ISC00);
    sei();

    // Start checking for RF tags
    startReader();

    while (1) {
        wdt_reset();
                usbPoll();

                if(usbInterruptIsReady()){ /* we can send another key */
                    reportBuffer[0] = 0;    /* no modifiers */
                    reportBuffer[1] = 37;
                    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
                }

        if (rStatus & (1 << R_ID_READY)) {
            if (goodUser == idData) {
                PORTB &= ~(1 << PB1);
                PORTB |= 1;
            }
            else {
                PORTB |= (1 << PB1);
                PORTB &= ~1;
            }

            _delay_ms(50);
            startReader();
        }
    }

    return 0;
}
