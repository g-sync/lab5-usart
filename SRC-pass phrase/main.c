#include <avr/io.h>
#include <string.h>
#include "uart.h"

#define F_CPU       16000000UL
#define BAUD_RATE   9600
#define MY_UBRR0    (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#define MaxLenGets  8 // 8 chars needed (including '\0')

#define LED1 PB0
#define LED2 PB1
#define LED3 PB2
#define LED4 PB3
#define LED5 PB4
#define LED6 PB5

#define STX 2
#define ETX 3

void parserecCommand(const char* recCommand) {
    if (recCommand[1]== '2' && recCommand[7] == '3') {
        if (recCommand[5] == '1') {
            if (recCommand[3] == '1') {
                PORTB |= (1 << LED1);  // Turn on LED1
            } 
            else if (recCommand[3] == '2') {
                PORTB |= (1 << LED2);  // Turn on LED2
            } 
            else if (recCommand[3] == '3') {
                PORTB |= (1 << LED3);  // Turn on LED3
            } 
            else if (recCommand[3] == '4') {
                PORTB |= (1 << LED4);  // Turn on LED4
            } 
            else if (recCommand[3] == '5') {
                PORTB |= (1 << LED5);  // Turn on LED5
            } 
            else if (recCommand[3] == '6') {
                PORTB |= (1 << LED6);  // Turn on LED6
            } 
            else { 
                return;
            }
        }
        else if (recCommand[5] == '0') {
            if (recCommand[3] == '1') {
                PORTB &= ~(1 << LED1);  // Turn off LED1
            } 
            else if (recCommand[3] == '2') {
                PORTB &= ~(1 << LED2);  // Turn off LED2
            } 
            else if (recCommand[3] == '3') {
                PORTB &= ~(1 << LED3);  // Turn off LED3
            } 
            else if (recCommand[3] == '4') {
                PORTB &= ~(1 << LED4);  // Turn off LED4
            } 
            else if (recCommand[3] == '5') {
                PORTB &= ~(1 << LED5);  // Turn off LED5
            } 
            else if (recCommand[3] == '6') {
                PORTB &= ~(1 << LED6);  // Turn off LED6
            } 
            else { 
                return;
            }
        }
        else {
            return;
        }
    }
}


int main() {
    DDRB = 0xFF;  // Set all PORTB pins as outputs

    const char str1[] = "\n\r USART 6 LED String Switch \n\r";
    const char str2[] = "\n\r Type input and hit Enter: ";
    const char str4[] = "\n\r Wrong input!! Try Again ";
   
    Uart_Init(MY_UBRR0);
    Uart_Puts(str1);  

    char recCommand[MaxLenGets];

    while (1) {

        Uart_Puts(str2);
        Uart_Gets(recCommand, MaxLenGets);
        
        // Wait for data to be 
        while (!(UCSR0A & (1 << RXC0)))
            ;
        // Receive the character
    
        // Check for proper encapsulation
        if (recCommand[1] ==  '2' && recCommand[7] == '3') {
            parserecCommand(recCommand);
        } else {
            Uart_Puts(str4);
        }
    }

    return 0;
}
