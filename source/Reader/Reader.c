#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/parity.h>

#include "Reader.h"

/************************************************************************/
/* Variables                                                            */
/************************************************************************/
volatile uint8_t rStatus = 0;
uint32_t vendorData = 0;
uint32_t idData = 0;

uint8_t startBits = 0;          // Start signal bit counter 0-9
uint8_t dataPos = 0;          // Current data bit counter 0-31

/************************************************************************/
/* Calculate period between 2 edge triggers as T or T2                  */
/* Single counter cycle ~61.2uS                                         */
/************************************************************************/
uint8_t getPeriod(uint8_t cycles)
{
    if (cycles >= 2 && cycles <= 6) {
        return 1;
    }
    else if (cycles >= 7 && cycles <= 12) {
        return 2;
    }

    return 3;
}

/************************************************************************/
/* Set current data bit, based on past period value                     */
/************************************************************************/
void getBit(uint8_t period)
{
    if (period == 2) {
        if (rStatus & (1 << R_CURRENT_BIT)) {
            if (startBits < 9) {
                // 0 bit on star sequence, pretend new start was captured
                rStatus = 0;
                sb(rStatus, R_START);
                return;
            }
            cb(rStatus, R_CURRENT_BIT);
        }
        else {
            sb(rStatus, R_CURRENT_BIT);
        }
        sb(rStatus, R_BIT_READY);
        return;
    }
    else if (period == 1) {
        if (rStatus & (1 << R_IN_PROGRESS)) {
            cb(rStatus, R_IN_PROGRESS);
            sb(rStatus, R_BIT_READY);
        }
        else {
            sb(rStatus, R_IN_PROGRESS);
            cb(rStatus, R_BIT_READY);
        }
        return;
    }

    rStatus = 0;
    return;
}

/************************************************************************/
/* Fill provided data pointer with current bit each call until          */
/* bits red = size. After each 4 bits the next one is a parity bit      */
/************************************************************************/
void readBit(uint32_t *dataBlock, uint8_t size, uint8_t statusBit)
{
    uint8_t currentBit = ((rStatus & (1 << R_CURRENT_BIT)) >> R_CURRENT_BIT);

    if (rStatus & (1 << R_PARITY_READ)) {
        cb(rStatus, R_PARITY_READ);

        if (parity_even_bit(*dataBlock & 0x0F) != currentBit) {
            rStatus = 0;
            return;
        }

        if (dataPos == size) {
            dataPos = 0;
            sb(rStatus, statusBit);
        }

        return;
    }

    *dataBlock = (*dataBlock << 1) | currentBit;
    dataPos++;

    if (dataPos % 4 == 0) {
        sb(rStatus, R_PARITY_READ);
    }

    return;
}

/************************************************************************/
/* Edge change interrupt                                                */
/************************************************************************/
ISR(PCINT0_vect)
{
    if (!(rStatus & (1 << R_START))) {
        if (!(PINB & (1 << PINB2))) {
            sb(rStatus, R_START);

            TCCR0B |= 0b101;
            TCNT0 = 0;
        }
        return;
    }

    uint8_t period = getPeriod(TCNT0);
    TCNT0 = 0;

    if (!(rStatus & (1 << R_SYNCED))) {
        if (period == 2) {
            sb(rStatus, R_SYNCED);
            sb(rStatus, R_CURRENT_BIT);

            startBits = 1;
            dataPos = 0;
        }
        else {
            rStatus = 0;
        }

        return;
    }

    getBit(period);
    if (!(rStatus & (1 << R_BIT_READY))) {
        return;
    }

    if (startBits < 9) {
        if (!(rStatus & (1 << R_CURRENT_BIT))) {
            rStatus = 0;
        }
        else {
            startBits++;
        }
        return;
    }

    if (!(rStatus & (1 << R_VENDOR_READY))) {
        readBit(&vendorData, 8, R_VENDOR_READY);
        return;
    }

    if (!(rStatus & (1 << R_ID_READY))) {
        readBit(&idData, 32, R_ID_READY);
        return;
    }

    stopReader();
}

void stopReader()
{
    TCCR0B = 0;
    PCMSK &= (1 << PCINT2);
}

void startReader()
{
    PORTB &= ~0b11;
    rStatus = 0;
    PCMSK |= (1 << PCINT2);
}
