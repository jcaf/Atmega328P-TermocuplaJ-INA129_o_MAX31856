/*
 * usart.h
 *
 * Created: 12/30/2016 11:22:12 PM
 *  Author: jcaf
 */


#ifndef USART_H_
#define USART_H_

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_Flush( void );

#define FOSC F_CPU // Clock Speed
#define BAUD 9600//38400//
//#define BAUD 115200
#define MYUBRR FOSC/16/BAUD-1

void usart_print_string(const char *p);
void usart_print_PSTRstring(const char *p);
void usart_println_string(const char *p);
void usart_println_PSTRstring(const char *p);


#endif /* USART_H_ */
