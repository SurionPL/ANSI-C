/**
 *******************************************************************************
 * @ Plik    ThingSpeak.c
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    10 listopada 2015
 * @ Opis    Plik zawiera funkcje potrzebne do wyslania wynikow pomiarow na
 * 			 serwer ThingSpeak.
 *******************************************************************************
 */

/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "../ESP8266_CL/ESP8266_Cl.h"
#include "ThingSpeak.h"
#include "avr/pgmspace.h"
#include "../MKUART/mkuart.h"
/*-------------------------------------------------------------------*/

char ts_ip[] = "144.212.80.11"; 	/* ThingSpeak IP */
char APIKey[] = "K7D0ZR1M32BLIV5B"; /* ThingSpeak API Key */


/**
 * @ Opis:				Uaktualnia pole kanalu na ThingSpeak.com.
 * @ Parametry:			-value - wskaŸnik na ci¹g znaków przewchowujacy wartosc
 * 						 pomiaru
 * 						-field - numer pola.
 * @ Zwracana wartosc:  Brak.
 */
void TS_UpdateField(char* value, uint8_t field) {

	if (field <= 8 && field >= 1) {
		char get[60] = "GET /update?key=";
		char s_field[9];
		/* Konwersja wyniku pomiaru na ciag tekstowy */
		sprintf(s_field, "&field%d=", field);

		/* Sklejanie zapytania */
		strcat(get, APIKey);		// Api Key
		strcat(get, s_field);		// Nr pola
		strcat(get, value);			// Wynik pomiaru
		strcat(get, "\r\n");

		ESP_ConnectServer(ts_ip, "80");		// Polaczenie z serwerem na porcie 80
		_delay_ms(5000);
		ESP_SendData(get, strlen(get));		// Wyslanie danych
		_delay_ms(5000);
		ESP_DisconnectServer();				// Rozlaczenie z serwerem
		//_delay_ms(1000);
	}
}
