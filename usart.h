#ifndef USART_H
#define USART_H
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

void USART0Init(void);
void USART0SendByte(unsigned char u8Data);
void USART0BacklightOff();
void USART0BacklightOn();
uint8_t USART0ReceiveByte();
void USART0SendString(char* str);
void USART0SendInt(int str);
#endif

