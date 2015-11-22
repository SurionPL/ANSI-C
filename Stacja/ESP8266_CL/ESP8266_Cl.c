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
/**
  * @ Opis:				Inicjalizacja modulu ESP8266 - tryb klienta i obs�uga jednego kanalu.
  * @ Parametry:		Brak.
  * @ Wartosc zwracana: Brak.
  */
void ESP_Init()
{

  //Send
	//ESP_PowerOn();
	uart_puts(PSTR("AT+CWMODE=1\r\n"));		/* Client mode */
	_delay_ms(4000);
	uart_puts(PSTR("AT+CIPMUX=0\r\n"));		/* Single channel connection */
	_delay_ms(4000);
	DDRB = 2;
	PORTB = 2; //??????????
}


/**
  * @ Opis:				��czy modu� z istniej�c� sieci�.
  * @ Parametry:		-ssid: wska�nik na tablic� zawieraj�c� nazw� sieci.
  * 					-password: wska�nik na tablic� zawieraj�c� has�o.
  * @ Wartosc zwracana: Brak.
  */
void ESP_Connect(char* ssid, char* password)
{
	char command[50] = "AT+CWJAP=\"";
	strcat(command, ssid);
	strcat(command, "\",\"");
	strcat(command, password);
	strcat(command,"\"\r\n");
//Send USART AT+ CWJAP =<ssid>,<pwd>
	uart_puts(command);
	_delay_ms(3000);

}


/**
  * @ Opis:				Wybudza uk�ad ze stanu u�pienia.
  * @ Parametry:		Brak.
  * @ Wartosc zwracana: Brak.
  */
void ESP_PowerOn()
{
	ESP_CHIP_PORT |= (1<<ESP_CHIP_PIN);
}


/**
  * @ Opis:				Wprowadza uk�ad w stan u�pienia.
  * @ Parametry:		Brak.
  * @ Wartosc zwracana: Brak.
  */
void ESP_PowerOff()
{
	ESP_CHIP_PORT &= ~(1<<ESP_CHIP_PIN);
}


/**
  * @ Opis:				Roz��cza modu� z sieci�.
  * @ Parametry:		Brak.
  * @ Wartosc zwracana: Brak.
  */
void ESP_Disconnect()
{
	uart_puts(PSTR("AT+CWQAP\r\n"));
}


/**
  * @ Opis:				Restartuje programowo modu�.
  * @ Parametry:		Brak.
  * @ Wartosc zwracana: Brak.
  */
void ESP_Restart()
{
	uart_puts(PSTR("AT+RST\r\n"));
	_delay_ms(1000);
}


/**
  * @ Opis:				��czy modu� z serwerem.
  * @ Parametry:		-ip_address: wska�nik na tablic� zawieraj�c� adres
  * 					 IP w postaci ci�gu tekstowego.
  * 					-port: wska�nik na tablic� zawieraj�c� numer portu.
  * @ Wartosc zwracana: ??????????.
  */
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


/**
  * @ Opis:				Wysy�a dane na serwer.
  * @ Parametry:		-data: wska�nik na tablic� zawieraj�c� dane w postaci ci�gu tekstowego.
  * 					-length  ????????????
  * @ Wartosc zwracana: Brak.
  */
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


/**
  * @ Opis:				Roz��cza modu� z serwerem.
  * @ Parametry:		Brak.
  * @ Wartosc zwracana: Brak.
  */
void ESP_DisconnectServer()
{
	uart_puts(PSTR("AT+CIPCLOSE\r\n"));
}
