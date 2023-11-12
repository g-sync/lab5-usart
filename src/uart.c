#include <avr/io.h>
#include "uart.h"


void Uart_Init( unsigned int baud_prescale )
{
    /* Set baud rate */
    //UBRR0H = (unsigned char)(baud>>8);
    //UBRR0L = (unsigned char)baud;
    UBRR0 = baud_prescale;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (3<<UCSZ00);
}


void Uart_Putc( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char Uart_Getc( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

void Uart_Puts(const char *s )
{
    while (*s) 
      Uart_Putc(*s++);

}


/* 
This is a modified Gets that will print back the inputed character 
while string is being saved.
The string is terminated with a carriage return and the MaxLen
*/
void Uart_Gets(char* Buffer, int MaxLen)
{
  char NextChar;
  char StringLen = 0;

  NextChar = Uart_Getc();              	// gets the first character of the string          
  Uart_Putc(NextChar);					// and prints it
  
  // check if the maximum length has been reached or if carriage return has been detected
  while((NextChar != '\r') && (StringLen < MaxLen - 1))    
  {
    *Buffer++ = NextChar;
    StringLen++;
    NextChar = Uart_Getc();
    Uart_Putc(NextChar);
  }
  Buffer = '\0';
}

