/*
 * USART.c
 *
 *  Created on: 4 lut 2015
 *      Author: Bartek
 */
#include <avr/io.h>
#include "USART.h"



volatile char UART_RxBuf[UART_RX_BUF_SIZE];
volatile uint8_t UART_RxStart;
volatile uint8_t UART_RxEnd;

volatile char UART_TxBuf[UART_TX_BUF_SIZE];
volatile uint8_t UART_TxStart;
volatile uint8_t UART_TxEnd;

//Przerwanie gdy zwolnilo sie miejsce w buforze nadawczym (wyslano znak)
ISR(USART_UDRE_vect)
{
	if(UART_TxStart != UART_TxEnd)
	{
		UART_TxEnd = (UART_TxEnd + 1) & UART_TX_MASK;

	}
}

ISR(USART_RX_vect)
{
	char data;
	uint8_t tmpRxStart;

	data = UDR0;
	tmpRxStart = (UART_RxStart + 1) & UART_RX_MASK;

	if(tmpRxStart != UART_RxEnd)
	{
		UART_RxStart = tmpRxStart;
		UART_RxBuf[UART_RxStart] = data;
	}
	//return 0;
}



void UART_Init(uint16_t ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}


void UART_Transmit(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void UART_Flush(void)
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}


uint8_t UART_ReceiveByte()
{
	/* Wait for data to be received */
	//while (!(UCSR0A & (1<<RXC0)))	;
	/* Get and return received data from buffer */
	//return UDR0;
	if( UART_RxStart != UART_RxEnd)
	{
		UART_RxEnd = (UART_RxEnd + 1) & UART_RX_MASK;
		return UART_RxBuf[UART_RxEnd];
	}
	else
	{
		return 0;
	}
}


void UART_TransmitString(char data[], uint16_t size) {
	int i;
	for(i = 0; i < size; i++)
		UART_Transmit(data[i]);
}


void UART_TransmitData(uint8_t data[], uint16_t size) {
	int i;
	for(i = 0; i < size; i++)
		UART_Transmit(data[i]);
}

/*void uart_puts(char *s)		// wysy�a �a�cuch z pami�ci RAM na UART
{
  register char c;
  while ((c = *s++)) uart_putc(c);			// dop�ki nie napotkasz 0 wysy�aj znak
}*/





