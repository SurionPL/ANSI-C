/**
  *******************************************************************************
  * @ File    HTU21D.h
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    01-October-2015
  * @ Brief   This file contains all the functions prototypes for the HTU21D
  * 		  digital relative humidity sensor library.
  *******************************************************************************
  */

#ifndef HTU21D_H_
#define HTU21D_H_


/* Adres slave urzadzenia */
#define HTU21D_SLA ((uint8_t)0x80)


/* Komendy */
#define HTU21D_TEMP_MEAS_NHM	((uint8_t)0xF3) /* Wyzwalanie pomiaru temperatury (No Hold Master) */
#define HTU21D_HUM_MEAS_NHM		((uint8_t)0xF5) /* Wyzwalanie pomiaru wilgotnosci (No Hold Master) */
#define HTU21D_WRITE_UR			((uint8_t)0xE6) /* Zapis do rejestru uzytkownika (UR) */
#define HTU21D_READ_UR			((uint8_t)0xE7) /* Odczyt rejestru uzytkownika (UR) */
#define HTU21D_SOFT_RESET		((uint8_t)0xFE) /* Soft Reset */


/* Wartosc domyslna rejestru uzytkownika (UR)*/
#define HTU21D_UR_DEFAULT ((uint8_t)0x83)


/* Wartosci bitow statusowych pomiaru */
#define HTU21D_TYPE_TEMPERATURE ((uint8_t)0x00)
#define HTU21D_TYPE_HUMIDITY	((uint8_t)0x02)


/* Struktura rejestrow HTU21D */
typedef struct {
	uint8_t UR;
}HTU21D_RegistersTypeDef;


/* Rozdzielczosci pomiarow */
typedef enum {
	Humidity12b_Temperature14b = 0,
	Humidity8b_Temperature12b,
	Humidity10b_Temperature13b,
	Humidity11b_Temperature11b,
}HTU21D_ResolutionTypeDef;


/* Funkcje HTU21D */
void HTU21D_Init(HTU21D_ResolutionTypeDef Resolution);
void HTU21D_StartTemperature();
void HTU21D_StartHumidity();
void HTU21D_GetTemperature(int8_t* integer, uint8_t* fractional);
uint8_t HTU21D_GetHumidity();

#endif /* HTU21D_H_ */