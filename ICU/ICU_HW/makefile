SHELL = cmd

FCPU = 16000000
srcs = $(wildcard *.c)

all: application.hex

application.hex: $(srcs)
	avr-gcc -Wall -Os -std=c99 -D F_CPU=$(FCPU) -mmcu=atmega32 $(srcs) -o application.bin -Xlinker -Map=application.map
	avr-objcopy -j .text -j .data -O ihex application.bin application.hex
	avr-size -B application.bin

flash: application.hex
	avrdude -p m32 -c arduino -P com3 -b 115200 -U flash:w:application.hex:i -F
	
	
	
clean:
	del application.*