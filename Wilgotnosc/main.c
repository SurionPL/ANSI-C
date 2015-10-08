/*
 * main.c
 *
 *  Created on: 2 wrz 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "HTU21D.h"
#include "I2C.h"
#include "MKUART/mkuart.h"
#include "avr/interrupt.h"


void SendTempUSART()
{
    uart_puts("Temperatura:  ");
    //uart_putint( temp1, 10 );
    uart_puts(".");
    //uart_putint( temp2, 10 );
    uart_puts("\r\n");
}


uint8_t min;
uint8_t sec;
uint8_t hour;


int main() {
	DDRB  = 1<<PB1;
	PORTB = 1<<PB1;
	TWI_Init(100000/100);
	USART_Init(__UBRR);
	sei();


	while(1)
	{

	}
}