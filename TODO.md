# TODO regarding USB support
1. Current setup work on hand tuned OSSCAL value. firmware loads it from EEPROM address **0** (first byte). It can be written using avr dude: `avrdude -c usbasp -p attiny85 -U eeprom:w:value:m` where value is ant int. A working example is based around 117. OSSCAL value has 2 regions 0-127 and 128-255 these regions do overlap so going above 127 doesn't mean that freacuency will be bigger than 127. More can be red in attiny datasheet regarding OSCCAL register description.
  * Freaquency of specific OSCCAL value can be checked in crude method. Set required frequency in the Makefile and add code in `main()`
  ```
  OSSCAL = 115;
  PORTB |= (1 << PINB1);
  while (1) {
      PORTB ^= 1;
      _delay_ms(1);
  }
  return 0;
  ```
  Then just add a probe on green led output and check if high or low width is 1ms if its lower decreas OSSCAL and repeat, if its higher increase.

2. A proper way would be to decrease the clock to **16.5MHz** instead of **20**. The reason behind that is 16.5Mhz can have deviations up to 1% and on 20MHz only 200ppm is allowed. Also using 16.5MHz an auto calibration of OSCCAL can be introduces (well with some modification it can probably be done on 20MHz as well)

  To achieve that some things needs to be changed
  * First change the value of clock speed to **16500000** in Makefile of if you using any IDE change the clock speed in its settings
  * Try the hand tunning of OSCCAL as described above to see if you can make it work on this freq. (Only usb part will work with lowered frequency)
  * Next step would be to integrate auto tunning by first uncomenting block in **usbconfig.h**
  ```
#ifndef __ASSEMBLER__
#ifndef __ASSEMBLER__
      extern void usbEventResetReady(void);
#endif
#define USB_RESET_HOOK(isReset) if(!isReset){usbEventResetReady();}
  ```
  * in **usbconfig.h** enable `USB_CFG_HAVE_MEASURE_FRAME_LENGTH`
  * Next in **RFID.c** you should add method `usbEventReset()` which will do all the calibration. It can be taken from [EasyLoger](http://www.obdev.at/products/vusb/easylogger.html)
  * If you make `usbEventReset()` yourself then edit **RFID.c** `main()` method and change OSSCAL loading (first lines).
  * This should fix USB issues. The next part is to adapt Manchester decoding to new frequency. In **Reader.c** there is a method `uint8_t getPeriod(uint8_t cycles)` which desides on periods between 2 edge triggers on RF frontend output. Cycles are `Timer0` counts from `TCNT0` register. Now `Timer0` is configured with prescaler of **1024** meaning each 1024 cpu cycles `TCNT0` will be increased by **1**. So each value is about **61.2ms**
  * Tipical **T** range is around **256us** and **2T** is **512us**
  * First thing would be do decrease the prescaler of `Timer0`. Prescaler is set in **Reader.c**  Line 114 `TCCR0B |= 0b101;` . Be avare that if prescaler is to low, `TCNT0` will overflow as it is only 8bits long. So choose a proper value or implement overflow counting as well.
  * After `Timer0` prescaler will be changed next step is to tweak the T and 2T perdion valuesin **Reader.c** method `getPeriod()`
  * And thats all, **HAVE FUN!!**
