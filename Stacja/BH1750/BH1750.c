/**
 *******************************************************************************
 * @ Plik    BH1750.c
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    11 wrzesnia 2015
 * @ Opis    Ten plik zawiera funkcje do obslugi sensora natezenia oswietlenia
 * 			 BH1750.
 *******************************************************************************
 */

/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "BH1750.h"
#include "../I2C/I2C.h"
/*-------------------------------------------------------------------*/

uint8_t state_;			/* Stan aktywnosci modulu */
uint8_t mode_;			/* Wybrany tryb pomiaru */


/**
 * @ Opis:				Wyprowadza modul ze stanu uspienia.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void BH1750_PowerOn()
{
	_delay_us(5);

	state_ = BH1750_Power_ON;

	/* Wyslanie komendy wybudzenia */
	I2C_Start();
	I2C_Write_SLA(BH1750_SLA);
	I2C_WriteByte(BH1750_Power_ON);
	I2C_Stop();
}


/**
 * @ Opis:				Wprowadza uklad w stan uspienia.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void BH1750_PowerDown()
{
	state_ = BH1750_Power_OFF;

	/* Wyslanie komendy wprowadzenia w stan uspienia */
	I2C_Start();
	I2C_Write_SLA(BH1750_SLA);
	I2C_WriteByte(BH1750_Power_OFF);
	I2C_Stop();
}


/**
 * @ Opis:				Inicjalizuje modul HTU21D.
 * @ Parametry:  		mode: tryb pomiaru.
 * @ Zwracana wartosc: 	Brak.
 */
void BH1750_Start(uint8_t mode)
{
	mode_ = mode;

	/* Wyslanie komendy rozpoczecia pomiaru */
	I2C_Start();
	I2C_Write_SLA(BH1750_SLA);
	I2C_WriteByte(mode_);
	I2C_Stop();
}


/**
 * @ Opis:				Odczytuje wynik pomiaru.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Natezenie oswietlenia w luksach.
 */
uint16_t BH1750_Read()
{
	uint32_t result;
	uint8_t msb, lsb;
	uint16_t illuminance = 0;

	/* Odczyt wyniku z rejestru */
	I2C_Start();
	I2C_Write_SLA(BH1750_SLA + 1);
	msb = I2C_ReadByte_ACK();
	lsb = I2C_ReadByte_NACK();
	I2C_Stop();

	/* Konwersja na fizyczne jednostki */
	result = ((msb << 8) | lsb) * 10;
	illuminance = (uint16_t)(result / 12);

	/* Zaokraglenie wyniku */
	if(((mode_ == BH1750_CHR_MODE2) || (mode_ == BH1750_OTHR_MODE2)) && ((result % 12 ) >= 6))
	{
		illuminance++;
	}

	return illuminance;
}

/**
 * @ Opis:				Resetuje rejest danych. Na koncu wprowadza modul w stan uspienia.
 * @ Parametry:  		Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void BH1750_ResetDR()
{
	/* Wybudzenie, gdy uklad uspiony */
	if(state_ == BH1750_Power_OFF) BH1750_PowerOn();

	/* Wyslanie komendy */
	I2C_Start();
	I2C_Write_SLA(BH1750_SLA);
	I2C_WriteByte(BH1750_RESET);
	I2C_Stop();

	/* Wprowadzenie w tryb uspienia */
	BH1750_PowerDown();
}

