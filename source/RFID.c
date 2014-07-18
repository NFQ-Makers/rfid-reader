/*
 * RFID.c
 *
 * Created: 2014-04-11 22:03:34
 *  Author: Aivaras
 */ 


#include "global.h"

unsigned char requestedAddress = 0x00;

void i2cSlaveReceiveService(u08 receiveDataLength, u08* receiveData)
{
	requestedAddress = *receiveData++;
}

u08 i2cSlaveTransmitService(u08 transmitDataLengthMax, u08* transmitData)
{
	if (requestedAddress != 0x10) {
		*transmitData++ = 0xff;
		return 1;
	}
	
	u32 player = getSerialData();
	*transmitData++ = (u08)(player >> 24);
	*transmitData++ = (u08)(player >> 16);
	*transmitData++ = (u08)(player >> 8);
	*transmitData++ = (u08)player;
	
	return 4;
}

int main(void)
{	
	initCarier();
	
	DDRB |= (1 << PINB0);
	PORTB &= ~(1 << PINB0);
	
	i2cSetLocalDeviceAddr(LOCAL_ADDR, FALSE);
	i2cSetSlaveTransmitHandler( i2cSlaveTransmitService );
	i2cSetSlaveReceiveHandler( i2cSlaveReceiveService );
	
	//Enable global interrupts
	sei();
	enableRead();
		
    while(1)
    {
		if (readPoll()) {
			i2cInit();
			PORTB |= (1 << PINB0);
			
			//Some Delay for I2C bus
			_delay_ms(1000);
			PORTB &= ~(1 << PINB0);
			i2cDestroy();
			enableRead();
		}
    }
}