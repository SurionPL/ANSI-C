/*
 * USART.c
 *
 *  Created on: 4 lut 2015
 *      Author: Bartek
 */
#include <avr/io.h>
#include "USART.h"


void USART_Init(uint16_t ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	/* Set frame format: 8data, 2stop bit */
		//UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}



void USART_Transmit(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

void USART_Flush(void)
{
		unsigned char dummy;
		while ( UCSRA & (1<<RXC)) dummy = UDR;
}



void USART_TransmitInt(uint16_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Copy ninth bit to TXB8 */
	UCSRB &= ~(1<<TXB8);
	if ( data & 0x0100 )
		UCSRB |= (1<<TXB8);
	/* Put data into buffer, sends the data */
	UDR = data;
}


uint8_t USART_Receive()
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}


void USART_TransmitString(char* string) {
	register char s;
	while((s = *string++)) USART_Transmit(s);
}

void USART_TransmitData(uint8_t data[], uint16_t size) {
	int i;
	for(i=0;i<size;i++) {
		USART_Transmit(data[i]);
	}
}
