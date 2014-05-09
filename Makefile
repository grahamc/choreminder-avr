CFLAGS += -DF_CPU=8000000UL

all: flash

clean:
	rm -f firmware.elf firmware.hex

firmware.elf:
	avr-gcc \
		${CFLAGS} \
		-mmcu=atmega328p \
		-Wall -Werror \
		-Os -o firmware.elf \
		main.c \
		buttons.c \
		ocr_calc.c \
		sleep.c \
		usart.c \
		chores.c \

firmware.hex: firmware.elf
	avr-objcopy -j .text -j .data -O ihex firmware.elf firmware.hex

flash: firmware.hex
	avrdude -p m328p -c stk500v2 -B 50 -P /dev/cu.usbmodem* -v -e \
		-U flash:w:firmware.hex \
		-U lfuse:w:0xE2:m \
		-U hfuse:w:0xD9:m \
		-U efuse:w:0x07:m


