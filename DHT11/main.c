/*
 * main.c
 *
 *  Created on: 26 cze 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD/lcd44780.h"
#include "DHT/DHT11.h"
#include "MKUART/mkuart.h"

uint8_t temp = 0;
uint8_t hum = 0;

void DisplayResult() {

    uart_puts("Temperatura:  ");
    uart_putint( temp, 10 );
    uart_puts("\nWilgotnosc: ");
    uart_putint( hum, 10 );
    uart_puts("%\r\n");
}



int main()
{
	DDRB = 2;
	PORTB = 2;
	USART_Init(__UBRR);
	sei();
	//lcd_init();
	uart_puts("BLABLA");

	while(1)
	{
		uart_puts("BLABLA");
		uint8_t error = Measure(&temp,&hum);
		//if (error == 0)
			DisplayResult();
		_delay_ms(2000);
		//uart_putint(error,10);

	}
}
