CFLAGS ?= -Os -DF_APU=16000000UL -mmcu=atmega328p
LDFLAGS ?= -mmcu=atmega328p

ARDUINO_USB ?= /dev/ttyACM0

all: app.hex

app.hex: app.elf
	avr-objcopy -O ihex -R .eeprom $< $@

app.elf: app.o XqUart.o XqGpio.o XqLcd.o
	avr-gcc $(LDFLAGS) -o $@ $^

app.o: app.c
	avr-gcc $(CFLAGS) -c -o $@ $<

XqUart.o: XqUart.c XqUart.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqGpio.o: XqGpio.c XqGpio.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqLcd.o: XqLcd.c XqLcd.h
	avr-gcc $(CFLAGS) -c -o $@ $<

deploy: app.hex
	avrdude -F -V -c arduino -p ATMEGA328p -P ${ARDUINO_USB} -b 115200 -U flash:w:app.hex

clean: 
	rm -f *.elf *.hex *.o app
