#include <avr/io.h>
#include <string.h>
#include "uart.h"

#define F_CPU       16000000UL
#define BAUD_RATE   9600
#define MY_UBRR0    (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#define MaxLenGets  2  // 2 chars needed (including '\0')

#define LED1 PB0
#define LED2 PB1
#define LED3 PB2
#define LED4 PB3
#define LED5 PB4
#define LED6 PB5

int main() {

    DDRB = 0xFF;  // Set all PORTB pins as outputs

    const char str1[] = "\n\r USART 6 LED Character Switch \n\r";
    const char str2[] = "\n\r Choose A-F and hit Enter: ";
    const char str3[] = "\n\r Your input is: ";
    const char str4[] = "\n\r Wrong input!! Try Again ";

    Uart_Init(MY_UBRR0);
    Uart_Puts(str1); 

    char receivedChar[MaxLenGets];

    while (1) {

        Uart_Puts(str2);
        Uart_Gets(receivedChar, MaxLenGets);
        		
        // Wait for data to be received
        while (!(UCSR0A & (1 << RXC0)));
        // Receive the character
        
        if (receivedChar[0] == 'A') {
            PORTB = 0x00;  // Turn off all LEDs
            PORTB |= (1 << LED1);  // Turn on LED1

        } else if (receivedChar[0] == 'B') {
            PORTB = 0x00;  // Turn off all LEDs
            PORTB |= (1 << LED2);  // Turn on LED2

        } else if (receivedChar[0] == 'C') {
            PORTB = 0x00;  // Turn off all LEDs
            PORTB |= (1 << LED3);  // Turn on LED3

        } else if (receivedChar[0] == 'D') {
            PORTB = 0x00;  // Turn off all LEDs
            PORTB |= (1 << LED4);  // Turn on LED4

        } else if (receivedChar[0] == 'E') {
            PORTB = 0x00;  // Turn off all LEDs
            PORTB |= (1 << LED5);  // Turn on LED5

        } else if (receivedChar[0] == 'F') {
            PORTB = 0x00;  // Turn off all LEDs
            PORTB |= (1 << LED6);  // Turn on LED6

        } else {
            Uart_Puts(str4);
        }
    }

    return 0;
}