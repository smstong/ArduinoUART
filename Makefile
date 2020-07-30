CFLAGS ?= -Os -DF_APU=16000000UL -mmcu=atmega328p 
LDFLAGS ?= -mmcu=atmega328p

ARDUINO_USB ?= /dev/ttyACM0

all: app.hex

app.hex: app.elf
	avr-objcopy -O ihex -R .eeprom $< $@

app.elf: app.o XqUart.o XqGpio.o XqLcd.o XqKb.o XqAdc.o \
	XqTimer.o XqStepMotor.o XqD7.o XqSpi.o
	avr-gcc $(LDFLAGS) -o $@ $^

app.o: app.c
	avr-gcc $(CFLAGS) -c -o $@ $<

XqUart.o: XqUart.c XqUart.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqGpio.o: XqGpio.c XqGpio.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqLcd.o: XqLcd.c XqLcd.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqKb.o: XqKb.c XqKb.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqAdc.o: XqAdc.c XqAdc.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqTimer.o: XqTimer.c XqTimer.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqStepMotor.o: XqStepMotor.c XqStepMotor.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqD7.o: XqD7.c XqD7.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqSpi.o: XqSpi.c XqSpi.h
	avr-gcc $(CFLAGS) -c -o $@ $<

deploy: app.hex
	avrdude -F -V -c arduino -p ATMEGA328p -P ${ARDUINO_USB} -b 115200 -U flash:w:app.hex

clean: 
	rm -f *.elf *.hex *.o app
