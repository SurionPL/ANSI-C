/*
 * main.c
 *
 *  Created on: 2 wrz 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "RTC.h"
#include "I2C.h"
#include "MKUART/mkuart.h"
#include "avr/interrupt.h"
int8_t temp1;
uint8_t temp2;
RTC_DateTimeTypedef DataCzas;
void SendTempUSART()
{
    uart_puts("Temperatura:  ");
    uart_putint( temp1, 10 );
    uart_puts(".");
    uart_putint( temp2, 10 );
    uart_puts("\r\n");
}


uint8_t min;
uint8_t sec;
uint8_t hour;
void SendTimeUsart()
{

    uart_puts("Czas:  ");
    if(DataCzas.hours < 10) uart_puts("0");
    uart_putint( DataCzas.hours, 10 );
    uart_puts(":");
    if(DataCzas.minutes < 10) uart_puts("0");
    uart_putint( DataCzas.minutes, 10 );
    uart_puts(":");
    if(DataCzas.seconds < 10) uart_puts("0");
    uart_putint( DataCzas.seconds, 10 );
    uart_puts("\r\n");
}

int main() {
	DDRB  = 1<<PB1;
	PORTB = 1<<PB1;
	TWI_Init(100000/100);
	USART_Init(__UBRR);
	sei();
	RTC_InitTypeDef RTC_Initialize;
	RTC_Initialize.BB_SQW = DISABLE;
	RTC_Initialize.RTC_Alarm1=Alarm1_Disable;
	RTC_Initialize.RTC_Alarm2=Alarm2_Disable;
	RTC_Initialize.RTC_Oscillator = DISABLE;
	RTC_Initialize.RTC_SQW = SQW_Disable;

	RTC_Init(&RTC_Initialize);
	RTC_Init(&RTC_Initialize);

	uart_puts("Dziala!\n");




	DataCzas.seconds = 30;
	DataCzas.minutes = 5;
	DataCzas.hours = 0;
	RTC_SetTime(&DataCzas);
	DataCzas.seconds = 0;
	DataCzas.minutes = 0;
	DataCzas.hours = 0;

	RTC_GetTemp(&temp1, &temp2);
	_delay_ms(500);
	SendTempUSART();

while(1){
	RTC_GetTime(&DataCzas);
	SendTimeUsart();
	_delay_ms(5000);
}
}
