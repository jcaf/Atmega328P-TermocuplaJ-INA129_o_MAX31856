/*
 * usart.c
 *
 * Created: 12/30/2016 11:21:41 PM
 *  Author: jcaf
 */
#include "../system.h"
#include "usart.h"

void USART_Init( unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /*Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0) | (1<<RXCIE0);//Enable interrupt;
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (0<<USBS0)|(3<<UCSZ00);
    //UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);
}
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}
unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
        ;
    /* Get and return received data from buffer */
    return UDR0;
}
//void USART_Flush( void )
//{
//    unsigned char dummy;
//    while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
//}

ISR(USART_RX_vect)
{
    uint8_t _udr_rx = UDR0;
    //uint8_t u = UDR;
}
//////////////////////////////////////////////

void usart_print_string(const char *p)
{
    while (*p)
    {
        USART_Transmit(*p);
        p++;
    }
}

void usart_println_string(const char *p)
{
    usart_print_string(p);
    USART_Transmit('\n');
}

#if defined(__GNUC__) && defined(__AVR__)
    #include <avr/pgmspace.h>

    void usart_print_PSTRstring(const char *p)
    {
        char c;

        while (1)
        {
            c = pgm_read_byte_near(p);
            if (c == '\0')
                break;
            else
                USART_Transmit(c);
            p++;
        }
    }

    void usart_println_PSTRstring(const char *p)
    {
        usart_print_PSTRstring(p);
        USART_Transmit('\n');
    }

#endif

