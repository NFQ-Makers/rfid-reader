# Name: Makefile
# Author: Aiavras
# License: @see LICENSE

DEVICE     = attiny13a
PROGDEVICE = attiny13
CLOCK      = 20000000
PROGRAMMER = usbasp
OBJECTS    = RFID.o Reader/Reader.o
FUSES      = -U lfuse:w:0x3a:m -U hfuse:w:0xff:m

AVRDUDE = avrdude -c $(PROGRAMMER) -p $(PROGDEVICE)
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

install: flash fuse

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
