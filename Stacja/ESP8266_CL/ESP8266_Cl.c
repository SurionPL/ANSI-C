/**
 *******************************************************************************
 * @ Plik   ESP8266_CL.c
 * @ Autor	Bartlomiej Kusmierczyk
 * @ Wersja V1.0
 * @ Data   28 pazdziernika 2015
 * @ Opis   Plik zawiera wszystkie funkcje do obslugi modulu ESP8266 w trybie
 * 			klienta, obsluge jednego kanalu wykorzystujac protokol TCP.
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

char ssid[] = "SIEC_DOMOWA";			/* SSID sieci*/
char password[] = "HASLO123";		/* Haslo do sieci */

/**
 * @ Opis:				Aktywuje modul (jesli pin CH_PD podlaczony).
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_PowerOn() {
	ESP_CHPD_PORT |= (1 << ESP_CHPD_PIN);
}

/**
 * @ Opis:				Deaktywuje modul (jesli pin CH_PD podlaczony).
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_PowerOff() {
	ESP_CHPD_PORT &= ~(1 << ESP_CHPD_PIN);
}

/**
 * @ Opis:				Inicjalizuje modul wlaczajac tryb klienta i obsluge jednego kanalu.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_Init() {
	ESP_PowerOn();
	uart_puts("AT+CWMODE=1\r\n"); /* Client mode */
	_delay_ms(4000);
	uart_puts("AT+CIPMUX=0\r\n"); /* Single channel connection */
	_delay_ms(4000);
}

/**
 * @ Opis:				Laczy modul z siecia Wi-Fi.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_Connect() {
	char command[50] = "AT+CWJAP=\"";
	strcat(command, ssid);
	strcat(command, "\",\"");
	strcat(command, password);
	strcat(command, "\"\r\n");
	uart_puts(command);
	_delay_ms(3000);
}

/**
 * @ Opis:				Rozlacza modul z siecia.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_Disconnect() {
	uart_puts("AT+CWQAP\r\n");
}

/**
 * @ Opis:				Laczy sie z serwerem na okreslonym porcie korzystajac
 * 						z protokolu TCP.
 * @ Parametry:			-ip_address: wskaznik na tablice przechowujaca adres IP w
 * 						 postaci ciagu znakow.
 * 						-port: wskaznik na tablice przechowujaca numer portu w postaci ciagu znakow.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_ConnectServer(char* ip_address, char* port) {
	//Jeden kanal i jeden protokol
	char command[50] = "AT+CIPSTART=\"TCP\",\"";
	strcat(command, ip_address);
	strcat(command, "\",");
	strcat(command, port);
	strcat(command, "\r\n");

	uart_puts(command);
}

/**
 * @ Opis:				Rozlacza modul z serwerem.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_DisconnectServer() {
	uart_puts("AT+CIPCLOSE\r\n");
}

/**
 * @ Opis:				Wysyla dane na serwer.
 * @ Parametry:			-data: wskaznik na tablice przewchowujaca dane do wyslania
 * 						 w postaci ciagu znakow.
 * 						-length: liczba bajtow do wyslania.
 * @ Zwracana wartosc:  Brak.
 */
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

/**
 * @ Opis:				Restartuje modul.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc:  Brak.
 */
void ESP_Restart() {
	uart_puts("AT+RST\r\n");
	_delay_ms(1000);
}

