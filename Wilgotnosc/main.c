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

int8_t t_integer;
uint8_t t_fractional;
int8_t hum;
void SendTempUSART()
{
    uart_puts("Temperatura:  ");
    uart_putint( t_integer);
    uart_puts(".");
    uart_putint( t_fractional);
    uart_puts("\r\n");
}

void SendHumUSART()
{
    uart_puts("Wilgotnosc: ");
    uart_putint(hum);
    uart_puts("%\r\n");
}

void InterfaceInit()
{
	//TWI_Init(100000/100);
	//USART_Init(__UBRR);
}

int main() {
	DDRB  = 1<<PB1;

	USART_Init(__UBRR);
	TWI_Init(100000/100);
	//InterfaceInit();
	sei();
	HTU21D_Init(Humidity11b_Temperature11b);

	PORTB=2;
	while(1)
	{
		HTU21D_StartHumidity();
		//PORTB^=2;
		uart_puts("Pomiar:\r\n");

		//HTU21D_StartTemperature();
		_delay_ms(400);
		hum = HTU21D_GetHumidity();
		if( hum != -1){
		SendHumUSART();}
		else
			uart_puts(" error ");
		//HTU21D_GetTemperature(&t_integer, &t_fractional);
		//SendTempUSART();
		_delay_ms(2000);

	}
}

ISR(TIMER1_COMPA_vect)
{

//	if (seconds % 60 == 0)
//	{
//		seconds = 0;
//		minutes++;
//		trigger_flag = MEASUREMENTS_TRIGGER_ENABLE;
//	}
//	if (minutes % 5 == 0)
//	{
//		minutes = 0;
//		reset_connection_flag = RESET_CONNECTION_ENABLE;
//
//	}
	PORTB ^= 1<<PB1;
	//seconds++;
}
