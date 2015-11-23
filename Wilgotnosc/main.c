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
    uart_putint( t_integer, 10 );
    uart_puts(".");
    uart_putint( t_fractional, 10 );
    uart_puts("\r\n");
}

void SendHumUSART()
{
    uart_puts("Wilgotnosc: ");
    uart_putint(hum, 4 );
    uart_puts("%\r\n");
}

void InterfaceInit()
{
	//TWI_InitTypeDef TWI_InitStruct;
	//TWI_InitStruct.TWI_Speed = 100000/100;
	TWI_Init(100000/100);
	USART_Init(__UBRR);
}

int main() {
	DDRB  = 1<<PB1;

	InterfaceInit();
	sei();
	HTU21D_Init(Humidity11b_Temperature11b);
	//TWI_Start(HTU21D_SLA);
	//TWI_Stop();


	while(1)
	{

		//HTU21D_StartTemperature();
		HTU21D_StartHumidity();
		_delay_ms(200);
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
