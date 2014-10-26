#ifndef READER_H_
#define READER_H_

/************************************************************************/
/* Status variable bit positions                                        */
/************************************************************************/
#define R_START 0           // Falling edge detected
#define R_SYNCED 1          // 2T after falling edge detected (sync signal captured)

#define R_IN_PROGRESS 2     // Data bit read in progress (occurs after 1T)
#define R_BIT_READY 3       // Data bit ready to process
#define R_PARITY_READ 4     // Next data bit is parity check
#define R_CURRENT_BIT 5     // Data bit value after read

#define R_VENDOR_READY 6    // Vendor data fully red
#define R_ID_READY 7        // ID data fully red

/************************************************************************/
/* Helpers                                                              */
/************************************************************************/
#define cb(reg,bit) (reg&=~(1<<bit)) // Clear bit
#define sb(reg,bit) (reg|=(1<<bit))  // Set bit

/************************************************************************/
/* Variables                                                            */
/************************************************************************/
volatile extern uint8_t rStatus; // Process status variable, see bit locations for info

extern uint32_t vendorData;     // Vendor data holder
extern uint32_t idData;         // ID data holder

void stopReader();
void startReader();

#endif /* READER_H_ */
