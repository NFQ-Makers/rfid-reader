#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Reader/Reader.h"

int main(void)
{
    // ID for comparison
    uint32_t goodUser = 0x00000000;

    // Turbo charge internal clock to ~20 MHz (this value will differ for each chip)
    OSCCAL = 111;

    // PINB1 AND PINB0 as outputs
    DDRB |= 0b11;

    // Turn of RF front-end (fancy effects)
    PORTB |= (1 << PINB1);
    PORTB &= ~1;
    _delay_ms(300);

    // Enable interrupts
    GIMSK |= (1 << PCIE);
    sei();

    // Start checking for RF tags
    startReader();

    while (1) {
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
