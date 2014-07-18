/*
 * global.h
 *
 * Created: 2014-04-15 20:53:16
 *  Author: Aivaras
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#define F_CPU 8000000
#define BAUD 9600UL

//Local device address for I2C
#define LOCAL_ADDR	100 << 1

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/parity.h>

#include "UART/UART.h"
#include "Reader/Reader.h"

#include "i2c/avrlibdefs.h"
#include "i2c/avrlibtypes.h"
#include "i2c/i2c.h"

#endif /* GLOBAL_H_ */