/**
 *******************************************************************************
 * @ File    HTU21D.c
 * @ Author  Bartlomiej Kusmierczyk
 * @ Version V1.0
 * @ Date    01-October-2015
 * @ Brief   This file contains all the HTU21D digital relative humidity sensor
 * 			 firmware functions.
 *******************************************************************************
 */


/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "HTU21D.h"
#include "../I2C/I2C.h"
#include "../MKUART/mkuart.h"
/*-------------------------------------------------------------------*/


HTU21D_RegistersTypeDef RegistersStruct;


/**
 * @ Opis:				Inicjalizuje modul HTU21D.
 * @ Parametry:  		HTU21D_ResolutionTypeDef: wartosc powiazana z trybem pomiaru.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_Init(HTU21D_ResolutionTypeDef Resolution)
{
	/* Odczyt zawartosc rejestru uzytkownika */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_READ_UR);
	TWI_RStart();
	TWI_Write_SLA(HTU21D_SLA + 1);
	RegistersStruct.UR = TWI_ReadByte_NACK();
	TWI_Stop();

	RegistersStruct.UR &= 0x38;	// Save reserved bits

	/* Wybor rozdzielczosci pomiarow */
	if(Resolution == Humidity12b_Temperature14b)
	{
		RegistersStruct.UR |= 0x02;
	}
	else if(Resolution == Humidity8b_Temperature12b)
	{
		RegistersStruct.UR |= 0x03;
	}
	else if(Resolution == Humidity10b_Temperature13b)
	{
		RegistersStruct.UR |= 0x82;
	}
	else
	{
		RegistersStruct.UR |= HTU21D_UR_DEFAULT;
		//Domyslna wartosc - 11/11 bitow
	}

	/* Wyslanie zmienionej wartosci rejestru uzytkownika */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_WRITE_UR);
	TWI_WriteByte(RegistersStruct.UR);
	TWI_Stop();
}


/**
 * @ Opis:				Rozpoczyna pomiar wilgotnosci.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_StartTemperature()
{
	/* Wyslanie komendy rozpoczecia pomiaru temperatury */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_TEMP_MEAS_NHM);
	TWI_Stop();
}


/**
 * @ Opis:				Rozpoczyna pomiar temperatury.
 * @ Parametry:  		HTU21D_ResolutionTypeDef: wartosc powiazana z trybem pomiaru.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_StartHumidity()
{
	/* Wyslanie komendy rozpoczecia pomiaru wilgotnosci */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_HUM_MEAS_NHM);
	TWI_Stop();
}


/**
 * @ Opis:				Odczytuje wynik pomiaru temperatury.
 * @ Parametry:  		-integer: wskaznik na komorke w ktorej przechowywana bedzie czesc calkowita
 * 						 temperatury.
 * 						-fractional: wskaznik na komorke w ktorej przechowywana bedzie czesc ulamkowa
 * 						 temperatury.
 * @ Zwracana wartosc: 	Brak.
 */
void HTU21D_GetTemperature(int8_t* integer, uint8_t* fractional)
{
	uint16_t result;
	int32_t temperature;

	/* Odczyt wyniku pomiaru z rejestru sensora */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA + 1);
	result  = TWI_ReadByte_ACK() << 8;
	result |= TWI_ReadByte_NACK();
	TWI_Stop();

	if((result & 0x02) == HTU21D_TYPE_TEMPERATURE)
	{
		/* Konwersja wartosci z rejestru na stopnie Celsjusza */
		temperature = ((int32_t)-4685 + ((((uint32_t)17572) * ((uint32_t)result & 0xFFFC)) / 65536));
		*integer = temperature / 100;
		*fractional = temperature % 100;

		if( *fractional > 75 )
		{
			*integer += 1;
			*fractional = 0;
		}
		else if( *fractional < 25 )
		{
			*fractional = 0;
		}
		else
		{
			*fractional = 5;
		}
	}
}


/**
 * @ Opis:				Odczytuje wynik pomiaru wilgotnosci.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Wynik pomiaru wilgotnosci w %. Gdy nieprawid�owy pomiar - zwraca zero.
 */
uint8_t HTU21D_GetHumidity()
{

	uint32_t result;
	uint8_t msb, lsb;
	uint32_t humidity;

	/* Odczyt danych z rejestru */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA + 1);
	msb = TWI_ReadByte_ACK();
	lsb = TWI_ReadByte_NACK();
	TWI_Stop();

	result = (msb << 8) | lsb;

	if(((result & 0x00000002) == HTU21D_TYPE_HUMIDITY) && (result >= 600))
	{
		/* Konwersja wartosci z rejestru na % */
		humidity = ((((uint32_t)12500 * (result & 0xFFFFFFFC)) >> 16) - (uint32_t)600);

		return ((uint8_t)(humidity / 100));
	}
	return (0);
}


