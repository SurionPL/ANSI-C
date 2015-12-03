/**
 *******************************************************************************
 * @ File    ESP8266_CL.c
 * @ Author  Bartlomiej Kusmierczyk
 * @ Version V1.0
 * @ Date    28-August-2015
 * @ Brief   This file contains all the ESP8266 wi-fi module firmware functions.
 *******************************************************************************
 */

/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdio.h>
#include "../MKUART/mkuart.h"
#include "ESP8266_Cl.h"
/*-------------------------------------------------------------------*/


char ssid[] = "PENTAGON";
char password[] = "BarT2014DST";


void ESP_Init()
{
	ESP_PowerOn();
	uart_puts(PSTR("AT+CWMODE=1\r\n"));		/* Client mode */
	_delay_ms(4000);
	uart_puts(PSTR("AT+CIPMUX=0\r\n"));		/* Single channel connection */
	_delay_ms(4000);
}


void ESP_Connect()
{
	PORTB = 1 << PB1;
	char command[50] = "AT+CWJAP=\"";
	strcat(command, ssid);
	strcat(command, "\",\"");
	strcat(command, password);
	strcat(command,"\"\r\n");
	uart_puts(command);
	_delay_ms(3000);
}


void ESP_PowerOn()
{
	ESP_CHIP_PORT |= (1<<ESP_CHIP_PIN);
}


void ESP_PowerOff()
{
	ESP_CHIP_PORT &= ~(1<<ESP_CHIP_PIN);
}


void ESP_Disconnect()
{
	uart_puts(PSTR("AT+CWQAP\r\n"));
}


void ESP_Restart()
{
	uart_puts(PSTR("AT+RST\r\n"));
	_delay_ms(1000);
}


ESP_ErrorFlag ESP_ConnectServer(char* ip_address, char* port)
{
	//Jeden kanal i jeden protokol
		char command[50] = "AT+CIPSTART=\"TCP\",\"";
		strcat(command, ip_address);
		strcat(command ,"\",");
		strcat(command, port);
		strcat(command, "\r\n");

		uart_puts(command);

		return ESP_OK;
}


void ESP_SendData(char* data, uint8_t length)
{
	char s_length[4];
	char command[25] = "AT+CIPSEND=";

	sprintf(s_length, "%d", length);
	strcat(command, s_length);
	strcat(command, "\r\n");

	uart_puts(command);
	_delay_ms(1000);
	uart_puts(data);

}


void ESP_DisconnectServer()
{
	uart_puts(PSTR("AT+CIPCLOSE\r\n"));
}
