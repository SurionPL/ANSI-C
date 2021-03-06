/*
 * main.c
 *
 *  Created on: 2 wrz 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "MKUART/mkuart.h"
#include "BH1750.h"

int main()
{
	DDRB = 2;
	PORTB=2;
	uint16_t lux = 0;
	USART_Init(__UBRR);
	sei();
	TWI_Init(100000/100);
	BH1750_PowerOn();

	//BH1750_Read();
	while(1)
	{
		BH1750_Start(BH1750_OTLR_MODE);
		_delay_ms(300);
		lux = BH1750_Read();
		uart_puts("Natezenie: ");
		uart_putint(lux);
		uart_puts("\r\n");
		_delay_ms(5000);
	}
}
