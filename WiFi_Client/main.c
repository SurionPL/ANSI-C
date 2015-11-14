/*
 * main.c
 *
 *  Created on: 28 sie 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "ESP8266_Cl.h"
#include <avr/interrupt.h>
#include "MKUART/mkuart.h"
#include <string.h>

int main()
{

	char ssid[]= "PENTAGON";
	char pwd[] = "BarT2014DST";
	//char ip_add[] = "144.212.80.11";
	//char dane[] = "GET /update?key=K7D0ZR1M32BLIV5B&field2=25\r\n";
	//char port[] = "80";


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
	DDRB = 2;
	PORTB = 2;

	while(1) {
		ESP_Connect(ssid, pwd);
		//uart_puts("AT+CWMODE=1\r\n");		/* Client mode */
		ESP_ConnectServer(ip_add, port);
//		_delay_ms(3000);
		ESP_SendData(dane, 44);
		_delay_ms(3000);
		ESP_DisconnectServer();
		_delay_ms(3000);
		ESP_Disconnect();
		_delay_ms(2000);
		uart_puts("\nkoniec\n");



	}
}
