RFID Reader
===========

A not so simple 125KHz rfid reader based on a ATTiny and EM4095

Build around a single timer (Timer0), uses two interrupts pin change and INT0
Manchester code decoding based on Timing approach. Base clock 16.5MHz.

Input
-------
- **PB2** - Input of Card data (after EM)

Outputs
-------
- **PB1** - EM4095 disable / Red led
- **PB0** - Green led

Quite interseting
------
This device tries to calibrate itself to 16.5MHz by measuring usb packet lenght. It also stores its last calibration
value to EEPROM byte address 0 (first byte as this can be read by avrdude)

Also never compile this with optimization level -O3 as USB will not work. -Os (size) seems to be ok

Makefile
------
For convinience there is a make file with instructions:
- **make** - compiles the compileables
- **make flash** - flashes flash with a flash file
- **make fuse** - tries to fuse the fuses
- **make install** - compiles, flashes, fuses

PCB
------
Double layer SMD in KiCad format

AVR Memory Usage
------
```
Device: attiny85

Program:    2456 bytes (30.0% Full)
(.text + .data + .bootloader)

Data:         70 bytes (13.7% Full)
(.data + .bss + .noinit)
```
---
**Thanks to:**

- [Vassilis Serasidis](http://www.serasidis.gr/circuits/RFID_reader/125kHz_RFID_reader.htm) - Manchester code ideas
- [V-USB](http://www.obdev.at/products/vusb/index.html) - Software USB support :)
