/*
 * Reader.c
 *
 * Created: 2014-04-15 21:10:01
 *  Author: Aivaras
 */ 
#include "../global.h"

//Counter for each edge in carrier between input edges
volatile uint8_t clock = 0;

//When return edge triggers interrupt, clock is copied to cycles
volatile uint8_t cycles = 0;

//Input edge trigger 0 none, 1 rising 2 falling
volatile uint8_t edge = 0;

//set when first edge of return signal is captured
uint8_t started = 0;

//set when first 2T period between edges are encountered
uint8_t sync = 0;

//9 start bits indicates commutation start all bits are 1
uint8_t startBits = 0;

//last captured bit value. Manchester code indicated changes from previous bit.
uint8_t lastBit = 0;

//Current captured bit in current edge trigger
uint8_t currentBit = 0;

//Is current bit ready for read
uint8_t bitReady = 0;

//When T is encountered in Manchester code, next edge should also be T so this is set after first T
uint8_t readInProgress = 0;

//Data of VendorId
uint8_t vendorData = 0;

//Is vendorId is ready to read
uint8_t vendorReady = 0;

//Data of 32 car serial number
uint32_t serialData = 0;

//Is Serial number ready to read
uint8_t serialReady = 0;

//Internal pointer for tracking which bit is already red
uint8_t dataPos = 0;

//Is current bit a parity bit?
uint8_t parityCheck = 0;


/************************************************************************/
/* External pin interrupt, for returning signal from opamp              */
/************************************************************************/
ISR (INT0_vect) {
	//If time between last edge is less than 4th of T ignore trigger
	//This simple noise filter increases distance
	if (clock < 25) {
		return;
	}
	
	edge = (PIND & (1 << PIND2)) ? 1 : 2;
	cycles = clock;
	clock = 0;
}

/************************************************************************/
/* Interrupt of carrier edge chage                                      */
/************************************************************************/
ISR (TIMER1_COMPA_vect) {
	clock++;
}

/************************************************************************/
/* Init 125Khz carrier wave                                             */
/************************************************************************/
void initCarier()
{
	//OC1A pin as output (carrier wave)
	DDRB |= (1 << PINB1);
	
	//Set Timer1 in CTC mode toggle OC1A on compare match pre-scaler 1
	TCCR1A |= (1 << COM1A0);
	TCCR1B |= (1 << WGM12) | (1 << CS10);
	
	//Compare value for 250KHz toggle (125KHz carrier)
	OCR1A = 0x1F;

	MCUCR |= (1 << ISC00);
}

void enableRead()
{
	//Enable OC1A toggle interrupt
	TIMSK |= (1 << OCIE1A);
	
	//Enable external pin interrupts any edge
	GICR |= (1 << INT0);
}

void disableRead()
{
	//Disable interrupts to leave as much time as possible for i2c
	TIMSK &= ~(1 << OCIE1A);
	GICR &= ~(1 << INT0);
}

/************************************************************************/
/* Capture not started, receiver clock not synced                       */
/************************************************************************/
void discard()
{
	started = 0;
	sync = 0;
}

/************************************************************************/
/* Got first edge, prepare data, wait for clock sync                    */
/************************************************************************/
void startCapture()
{
	started = 1;
	sync = 0;
	bitReady = 0;
	
	vendorReady = 0;
	serialReady = 0;
	
	dataPos = 0;
	parityCheck = 0;
}

/************************************************************************/
/* If period between last and current edge is 2T set as sync point       */
/************************************************************************/
void syncCapure(uint8_t period)
{
	if (period == 2) {
		//Bit needs to be just 0 or 1 no masked values
		lastBit = (PIND & _BV(PIND2)) ? 1 : 0;
		
		//If the first bit after sync is not 1 it means we can be in a middle of data transmission
		if (!lastBit) {
			discard();
			return;
		}
		
		sync = 1;
		startBits = 1;
		
		bitReady = 0;
		readInProgress = 0;
		} else {
		discard();
	}
}

/************************************************************************/
/* Compute time from carrier as T or 2T                                 */
/************************************************************************/
uint8_t getPeriod()
{
	uint8_t temp = cycles;
	
	if (temp >= 34 && temp <= 94) {
		return 1;
		} else if(temp >= 98 && temp <= 158) {
		return 2;
	}
	
	return 3;
}

/************************************************************************/
/* Decide what current bit is now high or low, or maybe still in        */
/* transition, based on period between edges T/T2                       */
/* discard transmission on error                                         */
/************************************************************************/
void doRead(uint8_t period)
{
	if (period == 2) {
		currentBit = (lastBit) ? 0 : 1;
		lastBit = currentBit;
		bitReady = 1;
		} else if (period == 1) {
		if (readInProgress) {
			readInProgress = 0;
			currentBit = lastBit;
			bitReady = 1;
			} else {
			readInProgress = 1;
			bitReady = 0;
		}
		} else {
		bitReady = 0;
		discard();
	}
}

/************************************************************************/
/* Fill provided data pointer with current bit each call until          */
/* bits red = size. Each 4 bits the next one is a parity bit            */
/************************************************************************/
void readData(uint32_t *dataBlock, uint8_t size, uint8_t *status)
{
	if (parityCheck) {
		parityCheck = 0;
		if (parity_even_bit(*dataBlock & 0x0F) != currentBit) {
			discard();
			return;
		}
		
		if (dataPos == size) {
			*status = 1;
			dataPos = 0;
		}
		return;
	}
	
	*dataBlock = *dataBlock << 1 | currentBit;
	dataPos++;
	
	if (dataPos % 4 == 0) {
		parityCheck = 1;
	}
}

/************************************************************************/
/* Main logic for reading and parsing data of RFID, needs to be called  */
/* periodically in main system cycle. Late execution, can lead in lost  */
/* data																    */
/* @return 1 if serialData is ready                                     */
/************************************************************************/
uint8_t readPoll()
{
	if (!edge) {
		return 0;
	}
	
	if (!started) {
		if (edge != 2) {
			return 0;
		}
		startCapture();
		edge = 0;
		return 0;
	}
	edge = 0;
	
	uint8_t period = getPeriod();
	if (!sync) {
		syncCapure(period);
		return 0;
	}
	
	doRead(period);
	if (!bitReady) {
		return 0;
	}
	
	if (startBits < 9) {
		if (currentBit) {
			startBits++;
			} else {
			discard();
		}
		return 0;
	}
	
	if (!vendorReady) {
		readData((uint32_t *)&vendorData, 8, &vendorReady);
		return 0;
	}
	
	if (!serialReady) {
		readData(&serialData, 32, &serialReady);
		return 0;
	}
	
	disableRead();	
	discard();
	
	return 1;
}

uint32_t getSerialData()
{
	if (!serialReady) {
		return 0;
	}

	return serialData;
}

uint8_t getVendorData()
{
	if (!vendorReady) {
		return 0;
	}
	
	return vendorData;
}