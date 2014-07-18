/*
 * Reader.h
 *
 * Created: 2014-04-15 21:09:02
 *  Author: Aivaras
 */ 


#ifndef READER_H_
#define READER_H_

/************************************************************************/
/* METHODS                                                              */
/************************************************************************/
void initCarier();
void enableRead();
void disableRead();

uint8_t readPoll();

uint32_t getSerialData();
uint8_t getVendorData();


#endif /* READER_H_ */