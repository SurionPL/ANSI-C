/**
 *******************************************************************************
 * @ Plik    HTU21D.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Date    1 pazdziernika 2015
 * @ Brief   Ten plik zawiera wszystkie prototypy funkcji potrzebne do obslugi
 * 		     czujnika wilgotnosci i temperatury HTU21D.
 *******************************************************************************
 */

#ifndef HTU21D_H_
#define HTU21D_H_

#define HTU21D_SLA ((uint8_t)0x80)				/* Adres slave urzadzenia */

/* Komendy */
#define HTU21D_TEMP_MEAS_NHM	((uint8_t)0xF3) /* Wyzwalanie pomiaru temperatury (No Hold Master) */
#define HTU21D_HUM_MEAS_NHM		((uint8_t)0xF5) /* Wyzwalanie pomiaru wilgotnosci (No Hold Master) */
#define HTU21D_WRITE_UR			((uint8_t)0xE6) /* Zapis do rejestru uzytkownika (UR) */
#define HTU21D_READ_UR			((uint8_t)0xE7) /* Odczyt rejestru uzytkownika (UR) */
#define HTU21D_SOFT_RESET		((uint8_t)0xFE) /* Soft Reset */

#define HTU21D_UR_DEFAULT ((uint8_t)0x83)	/* Wartosc domyslna rejestru uzytkownika (UR)*/

/* Wartosci bitow statusowych pomiaru */
#define HTU21D_TYPE_TEMPERATURE ((uint8_t)0x00)		/* Temperatura */
#define HTU21D_TYPE_HUMIDITY	((uint8_t)0x02)		/* Wilgotnosc */

/* Rozdzielczosci pomiarow */
typedef enum {
	Humidity12b_Temperature14b = 0,
	Humidity8b_Temperature12b,
	Humidity10b_Temperature13b,
	Humidity11b_Temperature11b,
} HTU21D_ResolutionTypeDef;

/* Funkcje HTU21D */
void HTU21D_Init(HTU21D_ResolutionTypeDef Resolution);
void HTU21D_StartTemperature();
void HTU21D_StartHumidity();
void HTU21D_GetTemperature(int8_t* integer, uint8_t* fractional);
uint8_t HTU21D_GetHumidity();

#endif /* HTU21D_H_ */
