
#include "usart.h"
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART0Init(void)
{
  // Set baud rate
  UBRR0H = (unsigned char)(UBRR_VALUE>>8);
  UBRR0L = (unsigned char)UBRR_VALUE;
  // Set frame format to 8 data bits, no parity, 1 stop bit
  UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
  //enable transmission and reception
  // UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
  UCSR0B |= (1<<TXEN0);
}

void USART0SendByte(unsigned char u8Data) {
  //wait while previous byte is completed
  while(!(UCSR0A&(1<<UDRE0))){};
  // Transmit data
  UDR0 = u8Data;
  // Wait while the justsent byte is done
 //while(!(UCSR0A&(1<<UDRE0))){};
}

uint8_t USART0ReceiveByte() {
  // Wait for byte to be received
  while(!(UCSR0A&(1<<RXC0))){};
  // Return received data
  return UDR0;
}

void USART0SendString(char* str) {
  // Clean screen
  USART0SendByte(0xFE);
  USART0SendByte(0x01);

  // Display data
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == '\n') {
      USART0SendByte(0xFE);
      USART0SendByte(192); // Go to row 2, column 1
    } else {
      USART0SendByte(str[i]);
    }
  }
}

void USART0SendInt(int str) {
  // Clean screen
  USART0SendByte(0xFE);
  USART0SendByte(0x01);

  USART0SendByte(str);
}
