/*
 * main.c
 *
 *  Created on: 28 sie 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "MKUART/mkuart.h"
#include "ThingSpeak.h"
#include "ESP8266_Cl.h"


int main()
{
	USART_Init(__UBRR);
	sei();
	char ssid[]= "PENTAGON";
	char pwd[] = "BarT2014DST";


	ESP_Init();
	//uart_puts("AT+CWMODE=1\r\n");		/* Client mode */
	//_delay_ms(6000);
	//uart_puts("AT+CIPMUX=0\r\n");		/* Multi channel connection */
	//_delay_ms(4000);

	//_delay_ms(4000);
	//uart_puts("AT+CIPMUX=0\r\n");		/* Multi channel connection */
	//_delay_ms(4000);

	//TS_UpdateField(char* value, uint8_t field);



	//_delay_ms(10000);
	//DDRB = 2;
	//PORTB ^= 2;

	while(1) {
		ESP_Connect(ssid, pwd);
		_delay_ms(3000);
		TS_UpdateField("16", 1);
		//ESP_DisconnectServer();
		_delay_ms(3000);
		ESP_Disconnect();
		_delay_ms(3000);
		//uart_puts("\nkoniec\n");



	}
}
