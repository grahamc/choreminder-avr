CFLAGS += -DF_CPU=8000000UL

all: flash

clean:
	rm -f blink.elf blink.hex

blink.elf:
	avr-gcc \
		${CFLAGS} \
		-mmcu=atmega328p \
		-Wall -Werror \
		-Os -o blink.elf \
		main.c usart.c buttons.c

blink.hex: blink.elf
	avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

flash: blink.hex
	avrdude -p m328p -c stk500v2 -B 50 -P /dev/cu.usbmodem1451 -v -e \
		-U flash:w:blink.hex \
		-U lfuse:w:0xE2:m \
		-U hfuse:w:0xD9:m \
		-U efuse:w:0x07:m


