/*
 * UART.h
 *
 * Created: 2014-04-15 20:56:18
 *  Author: Aivaras
 */ 


#ifndef UART_H_
#define UART_H_

#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
	#error Uart error rate is larger than 1%
#endif

/************************************************************************/
/* METHODS                                                              */
/************************************************************************/
void initUart();
int uart_putc(uint8_t c);
void uart_puts (char *s);


#endif /* UART_H_ */