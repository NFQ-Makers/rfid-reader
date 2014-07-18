/*
 * UART.c
 *
 * Created: 2014-04-15 21:00:03
 *  Author: Aivaras
 */ 

#include "../global.h"

/************************************************************************/
/* Initialize UART transmitter                                          */
/************************************************************************/
void initUart()
{
	//Enable transmitter
	UCSRB |= (1 << TXEN);
	
	//8bit data, 1bit stop, no parity, async mode
	UCSRC |= (1<<UCSZ1) | (1<<UCSZ0);

	//Set UART rate
	UBRRH = (UBRR_VAL >> 8);
	UBRRL = UBRR_VAL;
}

/************************************************************************/
/* Uart send char                                                       */
/************************************************************************/
int uart_putc(uint8_t c)
{
	//Wait until uart buffers ready
	while (!(UCSRA & (1<<UDRE))){}
	
	UDR = c;
	return 0;
}

/************************************************************************/
/* Uart send string                                                     */
/************************************************************************/
void uart_puts (char *s)
{
	while (*s)
	{
		uart_putc(*s);
		s++;
	}
}