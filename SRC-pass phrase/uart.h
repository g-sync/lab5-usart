#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include <avr/io.h>


#define F_CPU       16000000UL
#define BAUD_RATE   9600                
#define MY_UBRR0 	((( F_CPU / ( BAUD_RATE * 16UL))) - 1)

void Uart_Init( unsigned int baud_prescale );
void Uart_Putc( unsigned char data );
unsigned char Uart_Getc( void );
void Uart_Puts(const char *s );
void Uart_Gets(char* Buffer, int MaxLen);



#endif // UART_H_INCLUDED
