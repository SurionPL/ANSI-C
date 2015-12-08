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

char ssid[] = "PENTAGON";				/* SSID sieci*/
char password[] = "BarT2014DST";		/* Haslo do sieci */


void ESP_PowerOn() {
	ESP_CHPD_PORT |= (1 << ESP_CHPD_PIN);
}

void ESP_PowerOff() {
	ESP_CHPD_PORT &= ~(1 << ESP_CHPD_PIN);
}

void ESP_Init() {
	ESP_PowerOn();
	uart_puts("AT+CWMODE=1\r\n"); /* Client mode */
	_delay_ms(4000);
	uart_puts("AT+CIPMUX=0\r\n"); /* Single channel connection */
	_delay_ms(4000);
}

void ESP_Connect() {
	char command[50] = "AT+CWJAP=\"";
	strcat(command, ssid);
	strcat(command, "\",\"");
	strcat(command, password);
	strcat(command, "\"\r\n");
	uart_puts(command);
	_delay_ms(3000);
}

void ESP_Disconnect() {
	uart_puts("AT+CWQAP\r\n");
}

void ESP_ConnectServer(char* ip_address, char* port) {
	//Jeden kanal i jeden protokol
	char command[50] = "AT+CIPSTART=\"TCP\",\"";
	strcat(command, ip_address);
	strcat(command, "\",");
	strcat(command, port);
	strcat(command, "\r\n");

	uart_puts(command);
}

void ESP_DisconnectServer() {
	uart_puts("AT+CIPCLOSE\r\n");
}

void ESP_SendData(char* data, uint8_t length) {
	char s_length[4];
	char command[25] = "AT+CIPSEND=";

	sprintf(s_length, "%d", length);
	strcat(command, s_length);
	strcat(command, "\r\n");

	uart_puts(command);
	_delay_ms(1000);
	uart_puts(data);

}

void ESP_Restart() {
	uart_puts("AT+RST\r\n");
	_delay_ms(1000);
}

