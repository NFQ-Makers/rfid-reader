RFID Reader
===========

A simple 125KHz rfid reader based on a ATMega8

Build around a single timer (Timer1) uses 2 interrupts (INT0 and TIMER1_COMPA) transmits data via UART
Manchester code decoding based on Timing approach. Base clock 8MHz. On successful tag read the PB0 is raised HIGH
for 1 sec. In that time I2C routines are available to read the user ID.

------

Input
-------
- **PD2** (INT0) - Input of Card data (after amplifier)
- **PC5** - TWI SDC (internal pull-up)

Outputs
-------
- **PB1** - Carrier wave (125KHz square)
 - **PB0** - Interrupt after a successful tag read

Mixed
------
- **PC4** - TWI SDA (internal pull-up)


PCB
------
Single layer through-hole in KiCad format
 - Drill: 1 mm
 - Pads: 2mm
 - Tracks 0.4 mm


---
**Thanks to:**

- [Vassilis Serasidis](http://www.serasidis.gr/circuits/RFID_reader/125kHz_RFID_reader.htm) - RFID analog stuff, code ideas :)
- [Pascal Stang](http://www.procyonengineering.com/embedded/avr/avrlib/) - AVRLib
