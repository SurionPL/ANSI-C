/**
 *******************************************************************************
 * @ Plik    HTU21D.c
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    1 pazdziernika 2015
 * @ Opis    Ten plik zawiera wszystkie funkcje do obslugi czujnika wilgotnosci
 * 			 i temperatury HTU21D.
 *******************************************************************************
 */

/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "HTU21D.h"
#include "../I2C/I2C.h"
#include "../MKUART/mkuart.h"
/*-------------------------------------------------------------------*/

//HTU21D_RegistersTypeDef RegistersStruct; /* Struktura rejestrow HTU21D */
uint8_t UR;
/**
 * @ Opis:				Inicjalizuje modul HTU21D.
 * @ Parametry:  		HTU21D_ResolutionTypeDef: wartosc powiazana z trybem pomiaru.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_Init(HTU21D_ResolutionTypeDef Resolution) {
	/* Odczyt zawartosc rejestru uzytkownika */
	I2C_Start();
	I2C_Write_SLA(HTU21D_SLA);
	I2C_WriteByte(HTU21D_READ_UR);
	I2C_RStart();
	I2C_Write_SLA(HTU21D_SLA + 1);
	UR = I2C_ReadByte_NACK();
	I2C_Stop();

	UR &= 0x38;	// Save reserved bits

	/* Wybor rozdzielczosci pomiarow */
	if (Resolution == Humidity12b_Temperature14b) {
		UR |= 0x02;
	} else if (Resolution == Humidity8b_Temperature12b) {
		UR |= 0x03;
	} else if (Resolution == Humidity10b_Temperature13b) {
		UR |= 0x82;
	} else {
		UR |= HTU21D_UR_DEFAULT;
		//Domyslna wartosc - 11/11 bitow
	}

	/* Wyslanie zmienionej wartosci rejestru uzytkownika */
	I2C_Start();
	I2C_Write_SLA(HTU21D_SLA);
	I2C_WriteByte(HTU21D_WRITE_UR);
	I2C_WriteByte(UR);
	I2C_Stop();
}

/**
 * @ Opis:				Rozpoczyna pomiar wilgotnosci.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_StartTemperature() {
	/* Wyslanie komendy rozpoczecia pomiaru temperatury */
	I2C_Start();
	I2C_Write_SLA(HTU21D_SLA);
	I2C_WriteByte(HTU21D_TEMP_MEAS_NHM);
	I2C_Stop();
}

/**
 * @ Opis:				Rozpoczyna pomiar temperatury.
 * @ Parametry:  		HTU21D_ResolutionTypeDef: wartosc powiazana z trybem pomiaru.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_StartHumidity() {
	/* Wyslanie komendy rozpoczecia pomiaru wilgotnosci */
	I2C_Start();
	I2C_Write_SLA(HTU21D_SLA);
	I2C_WriteByte(HTU21D_HUM_MEAS_NHM);
	I2C_Stop();
}

/**
 * @ Opis:				Odczytuje wynik pomiaru temperatury.
 * @ Parametry:  		-integer: wskaznik na komorke w ktorej przechowywana bedzie czesc calkowita
 * 						 temperatury.
 * 						-fractional: wskaznik na komorke w ktorej przechowywana bedzie czesc ulamkowa
 * 						 temperatury.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_GetTemperature(int8_t* integer, uint8_t* fractional) {
	uint16_t result;
	int32_t temperature;

	/* Odczyt wyniku pomiaru z rejestru sensora */
	I2C_Start();
	I2C_Write_SLA(HTU21D_SLA + 1);
	result = I2C_ReadByte_ACK() << 8;
	result |= I2C_ReadByte_NACK();
	I2C_Stop();

	if ((result & 0x02) == HTU21D_TYPE_TEMPERATURE) {
		/* Konwersja wartosci z rejestru na stopnie Celsjusza */
		temperature =
				((int32_t) -4685
						+ ((((uint32_t) 17572) * ((uint32_t) result & 0xFFFC))
								/ 65536));
		*integer = temperature / 100;
		*fractional = temperature % 100;

		if (*fractional > 75) {
			*integer += 1;
			*fractional = 0;
		} else if (*fractional < 25) {
			*fractional = 0;
		} else {
			*fractional = 5;
		}
	}
}

/**
 * @ Opis:				Odczytuje wynik pomiaru wilgotnosci.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Wynik pomiaru wilgotnosci w %. Gdy nieprawidłowy pomiar - zwraca zero.
 */
uint8_t HTU21D_GetHumidity() {

	uint32_t result = 0;
	uint8_t msb, lsb;
	uint32_t humidity;

	/* Odczyt danych z rejestru */
	I2C_Start();
	I2C_Write_SLA(HTU21D_SLA + 1);
	msb = I2C_ReadByte_ACK();
	lsb = I2C_ReadByte_NACK();
	I2C_Stop();

	result = (msb << 8) | lsb;

	if (((result & 0x00000002) == HTU21D_TYPE_HUMIDITY) && (result >= 600)) {
		/* Konwersja wartosci z rejestru na % */
		humidity = ((((uint32_t) 12500 * (result & 0xFFFFFFFC)) >> 16)
				- (uint32_t) 600);
		humidity/=100;
		//if (humidity > 100) humidity = 0;
		return ((uint8_t)humidity) ;
	}
	return (0);
}

