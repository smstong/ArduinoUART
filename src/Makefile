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

%.o : %.c %.h
	avr-gcc -c $(CFLAGS) -o $@ $<
