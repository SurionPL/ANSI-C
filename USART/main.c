/*
 * main.c
 *
 *  Created on: 4 lut 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

#define MYUBRR FOSC/16/BAUD-1
unsigned int dane=5;
char data[7]={'B','A','R','T','E','K',' '};
uint8_t byte = 0;
int main()
{
	DDRB |=(1<<PB1);
	PORTB|=(1<<PB1);

	USART_Init(MYUBRR);
	while(1) {
		USART_TransmitString(data);
		//USART_Transmit_Int(5);
		//byte = USART_Receive();
		//if(byte == 'T') PORTB^=(1<<PB1);
		_delay_ms(1000);
	}
}
