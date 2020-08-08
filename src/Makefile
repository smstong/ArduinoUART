CFLAGS ?= -Os -DF_APU=16000000UL -mmcu=atmega328p 
LDFLAGS ?= -mmcu=atmega328p
BIN_DIR = ..

all: libXqArduino.a
	cp $< ../
clean: 
	rm -f *.o *.a

libXqArduino.a: \
	XqUart.o \
	XqGpio.o \
	XqLcd.o \
	XqKb.o \
	XqAdc.o \
	XqTimer.o \
	XqStepMotor.o \
	XqD7.o \
	XqSpi.o \
	XqVirtualUart.o \
	XqI2c.o \
	XqDs1307.o \
	XqServo.o

	avr-ar rcs $@ $^

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

XqVirtualUart.o: XqVirtualUart.c XqVirtualUart.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqI2c.o: XqI2c.c XqI2c.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqDs1307.o: XqDs1307.c XqDs1307.h
	avr-gcc $(CFLAGS) -c -o $@ $<

XqServo.o: XqServo.c XqServo.h
	avr-gcc $(CFLAGS) -c -o $@ $<
