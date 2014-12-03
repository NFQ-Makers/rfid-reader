#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

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
/* 16.5MHz calibration routine                                          */
/************************************************************************/
static void calibrateOscillator(void)
{
    uint8_t step = 128;
    uint8_t trialValue = 0;
    uint8_t optimumValue;
    int x, optimumDev, targetValue = (unsigned)(1499 * (double)F_CPU / 10.5e6 + 0.5);

    /* do a binary search: */
    do{
        OSCCAL = trialValue + step;
        x = usbMeasureFrameLength();    /* proportional to current real frequency */
        if(x < targetValue)             /* frequency still too low */
            trialValue += step;
        step >>= 1;
    }while(step > 0);

    /* We have a precision of +/- 1 for optimum OSCCAL here */
    /* now do a neighborhood search for optimum value */
    optimumValue = trialValue;
    optimumDev = x; /* this is certainly far away from optimum */

    for(OSCCAL = trialValue - 1; OSCCAL <= trialValue + 1; OSCCAL++){
        x = usbMeasureFrameLength() - targetValue;
        if(x < 0)
            x = -x;
        if(x < optimumDev){
            optimumDev = x;
            optimumValue = OSCCAL;
        }
    }
    OSCCAL = optimumValue;
}

/************************************************************************/
/* USB reset event hook                                                 */
/************************************************************************/
void usbEventResetReady(void)
{
    cli();
    calibrateOscillator();
    sei();
    eeprom_write_byte(0, OSCCAL);   /* store the calibrated value in EEPROM */
}

/************************************************************************/
/* Fill in USB HID report and send it                                   */
/************************************************************************/
void sendReport(uchar c)
{
    reportBuffer[0] = 0; // No additional modifiers

    if (c == 48) {
        c = 39;
    } else if (c != 0) {
        c -= 19;
    }

    reportBuffer[1] = c;

    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
}

/************************************************************************/
/* Lets rock & roll                                                     */
/************************************************************************/
int main(void)
{
    // In case we have a reset without USB reset event load last calibrated value
    uint8_t calibrationValue = eeprom_read_byte(0);
    if (calibrationValue != 0xFF) {
        OSCCAL = calibrationValue;
    }

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
    // Well if windows will install any drivers it will need more that 1s
    // but this is just a safeguard for normal operation
    usbDeviceConnect();
    smartDelay(1000, 1);

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

            sprintf(idString, "%010lu", idData);
            idString[10] = 59; // ENTER 19 will be subtracted
            idString[11] = 0; // All keys are released

            // Turn red led and a sub woofer - BUSY! USB transmission in progress
            PORTB &= ~1;
            uint8_t sendEmpty = 0;

            while (pos < 12 || sendEmpty) {
                if(usbInterruptIsReady()){ // We can send another report
                    wdt_reset();
                    if (sendEmpty) {
                        // No buttons pressed, we need this to be not affected by the host
                        // keyboard key down delay
                        sendReport(0);
                        sendEmpty = 0;
                        continue;
                    } else {
                        sendReport(idString[pos]);
                        pos++;
                        sendEmpty = 1;
                    }
                }
            }

            // Turn off that buzzer, please!!
            PORTB |= 1;

            // Some delay to minimize double reads
            smartDelay(400, 1);
            startReader();
        }
    }

    return 0;
}
