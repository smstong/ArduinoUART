CFLAGS ?= -Os -DF_APU=16000000UL -mmcu=atmega328p 
LDFLAGS ?= -mmcu=atmega328p

ARDUINO_USB ?= /dev/ttyACM0

all: app.hex

deploy: app.hex
	avrdude -F -V -c arduino -p ATMEGA328p -P ${ARDUINO_USB} -b 115200 -U flash:w:$<

clean: 
	rm -f *.elf *.hex *.o *.a app
	cd src && make clean

app.hex: app.elf
	avr-objcopy -O ihex -R .eeprom $< $@

app.elf: app.o libXqArduino.a
	# note: -L -l must be after app.o
	avr-gcc -o $@ $< $(LDFLAGS) -L. -lXqArduino  

libXqArduino.a:
	cd src && make
app.o: app.c
	avr-gcc $(CFLAGS) -I./src -c -o $@ $<

