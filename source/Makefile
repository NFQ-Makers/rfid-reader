# Name: Makefile
# Author: Aiavras
# License: @see LICENSE

DEVICE     = attiny85
CLOCK      = 20000000
PROGRAMMER = usbasp
OBJECTS    = RFID.o Reader/Reader.o usbdrv/usbdrv.o usbdrv/usbdrvasm.o
FUSES      = -U lfuse:w:0xe1:m -U hfuse:w:0xd5:m
OSCCAL     = 117

AVRDUDE = avrdude -c $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	RFID.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:RFID.hex:i

fuse:
	$(AVRDUDE) $(FUSES)
	
tune:
	$(AVRDUDE) -U eeprom:w:$(OSCCAL):m

install: flash fuse tune

clean:
	rm -f RFID.hex RFID.elf $(OBJECTS)

# file targets:
RFID.elf: $(OBJECTS)
	$(COMPILE) -o RFID.elf $(OBJECTS)

RFID.hex: RFID.elf
	rm -f RFID.hex
	avr-objcopy -j .text -j .data -O ihex RFID.elf RFID.hex
	avr-size --format=avr --mcu=$(DEVICE) RFID.elf
	
# Targets for code debugging and analysis:
disasm:	RFID.elf
	avr-objdump -d RFID.elf

cpp:
	$(COMPILE) -E RFID.c
