#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "Reader/Reader.h"
#include "usbdrv/usbdrv.h"

/************************************************************************/
/* Lets say something about what we are                                 */
/************************************************************************/
const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
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

/************************************************************************/
/* USB TX Buffer data                                                   */
/************************************************************************/
static uchar     reportBuffer[2];

/************************************************************************/
/* HID seems to be controller by the usbdrv itself                      */
/************************************************************************/
uchar   usbFunctionSetup(uchar data[8])
{
    return 0;
}

/************************************************************************/
/* Delay with a tamed watchdog                                          */
/************************************************************************/
void smartDelay(uint16_t ms, uint8_t usb)
{
    while (ms) {
        wdt_reset();

        if (usb) {
            usbPoll();
        }

        _delay_us(990);
        ms--;
    }
}

/************************************************************************/
/* Lets rock & roll                                                     */
/************************************************************************/
int main(void)
{
    // Turbo charge internal clock to ~20 MHz if no value is set in eeprom try 117
    // it seems its quite near
    uint8_t calibration = eeprom_read_byte(0);
    OSCCAL = (calibration != 0xFF) ? calibration : 117;

    // A short watchdog
    wdt_enable(WDTO_120MS);

    // USB init needs to be called before interrupts are enabled
    usbInit();

    // Simulate unpluging device to host
    usbDeviceDisconnect();

    // PINB1 AND PINB0 as outputs
    DDRB |= 0b11;

    // Turn of RF front-end, leds off
    PORTB |= 0b11;

    // Delay to give some time for host to process device removal
    smartDelay(300, 0);

    // Enable interrupts
    sei();

    // Simulate device connection in host and delay to process.
    // Well if windows will install any drivers it will need more that 300ms
    // but this is just a safeguard for normal operation
    usbDeviceConnect();
    smartDelay(300, 1);

    // Start checking for RF tags
    startReader();

    while (1) {
        // We are alive. Aren't we?
        wdt_reset();
        usbPoll();

        // We got a user ID ready (card red duhh....)
        if (rStatus & (1 << R_ID_READY)) {
            // Some string and number porn
            char idString[12];
            uint8_t pos = 0;

            ltoa(idData, idString, 10);
            idString[10] = 59; // ENTER 19 will be subtracted
            idString[11] = 0; // All keys are released

            // Turn red led and a sub woofer - BUSY! USB transmission in progress
            PORTB &= ~1;

            // We could use pointers here but, adding 2 additional calls for ENTER and
            // NO KEY PRESSED is just as horrible as array position tracking
            // also with this approach we will send few additional NO KEY (0) reports if id is
            // shorter that 10 chars
            while (pos < 12) {
                if(usbInterruptIsReady()){ // We can send another report
                    uint8_t c = idString[pos];
                    reportBuffer[0] = 0;    // No modifiers like ctrl, alt etc
                    reportBuffer[1] = (c == 48) ? 39 : c - 19;
                    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
                    pos++;
                }
            }

            // In case that buzzer was not annoying enough, heres additional ~100ms of that
            smartDelay(100, 1);
            PORTB |= 1;

            // Additional delay before starting next read session, but this time without the buzzer
            smartDelay(400, 1);
            startReader();
        }
    }

    return 0;
}
