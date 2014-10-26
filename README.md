RFID Reader
===========

A simple 125KHz rfid reader based on a ATTiny and EM4095

Build around a single timer (Timer0), uses single interrupt (pin change) 
Manchester code decoding based on Timing approach. Base clock 20MHz.
------

Input
-------
- **PB2** - Input of Card data (after EM)

Outputs
-------
- **PB1** - EM4095 disable / Red led
- **PB0** - Green led

PCB
------
Double layer SMD in KiCad format

---
**Thanks to:**

- [Vassilis Serasidis](http://www.serasidis.gr/circuits/RFID_reader/125kHz_RFID_reader.htm) - RFID analog stuff, code ideas :)
