/**
 *******************************************************************************
 * @ Plik    I2C.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    26 lipca 2015
 * @ Opis    Ten plik zawiera funkcje do obslugi inerfejsu TWI.
 *******************************************************************************
 */

/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <util/TWI.h>
#include "I2C.h"
/*-------------------------------------------------------------------*/

volatile uint8_t TWI_ErrorFlag; /* Flaga bledu */


inline void TWI_WaitForFlag()
{
	uint16_t cnt = 0;
	/* Czekaj az ustawiona zostanie flaga TWINT */
	while (!(TWCR & (1 << TWINT)))
	{
		if(cnt >= 4000) {
			TWI_ERROR(5);
			break;
		}
		cnt++;
	}
}


/**
 * @ Opis:				Inicjalizuje interfejs TWI.
 * @ Parametry:			speed: predkosc transmisji.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_Init(uint16_t speed) {
	TWCR = (1 << TWEA) | (1 << TWEN);

	speed = (4000000 / speed / 100 - 16) / 2;
	uint8_t prescaler = 0;
	while (speed > 255) {
		prescaler++;
		speed /= 4;
	}
	TWSR = (TWSR & ((1 << TWPS1) | (1 << TWPS0))) | prescaler;
	TWBR = speed;
}

/**
 * @ Opis:				Wysyla bit startu.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_Start() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Czekaj az ustawiona zostanie flaga TWINT. */
	TWI_WaitForFlag();
	if ((TWSR & 0xF8) != TW_START) {
		TWI_ERROR(I2C_START_ERROR);
	}
}

/**
 * @ Opis:				Wysyla bit powtorzonego startu.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_RStart() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Czekaj az ustawiona zostanie flaga TWINT. */
	TWI_WaitForFlag();
	if ((TWSR & 0xF8) != TW_REP_START) {
		TWI_ERROR(I2C_REP_START_ERROR);
	}
}

/**
 * @ Opis:				Wysyla bit stopu.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_Stop() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/**
 * @ Opis:				Wysyla adres ukladu slave.
 * @ Parametry:			address: adres ukladu.
 * @ Zwracana wartosc:	Brak.
 */
void TWI_Write_SLA(uint8_t address) {
	uint8_t status;
	if ((address & 0x01) == 0)
		status = TW_MT_SLA_ACK;
	else
		status = TW_MR_SLA_ACK;
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);
	TWI_WaitForFlag();
	if (TW_STATUS != status) {
		TWI_ERROR(I2C_ACK_ERROR); //NACK error
	}
}

/**
 * @ Opis:				Wysyla bajt danych.
 * @ Parametry:			byte: bajt danych.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_WriteByte(uint8_t byte) {
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	TWI_WaitForFlag();
	if (TW_STATUS != TW_MT_DATA_ACK)
		TWI_ERROR(I2C_NACK_ERROR);
}

/**
 * @ Opis:				Odbiera bajt danych i wysyla bit NACK.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc: 	Bajt danych.
 */
uint8_t TWI_ReadByte_NACK() {
	TWCR = (1 << TWINT) | (1 << TWEN);
	TWI_WaitForFlag();
	if (TW_STATUS != TW_MR_DATA_ACK) {
		TWI_ERROR(I2C_NACK_ERROR);
	}
	return TWDR;
}

/**
 * @ Opis:				Odbiera bajt danych i wysyla bit ACK.
 * @ Parametry:			Brak.
 * @ Zwracana wartosc: 	Bajt danych.
 */
uint8_t TWI_ReadByte_ACK() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	TWI_WaitForFlag();
	if (TW_STATUS != TW_MR_DATA_ACK)
		TWI_ERROR(I2C_NACK_ERROR);
	return TWDR;
}

/**
 * @ Opis:				Ustawia flage bledu
 * @ Parametry:			error: kod bledu.
 * @ Zwracana wartosc:  Brak.
 */
void TWI_ERROR(uint8_t error) {
	TWI_ErrorFlag = error;
	//if (error == I2C_START_ERROR)
		//PORTB = 1 << PB1;  //??????????????????????????????
}

/**
 * @ Opis:				Odczytuje ciag bajtow.
 * @ Parametry:			-SLA: adres slave ukladu.
 * 						-address: adres rejestru.
 * 						-size: liczba bajtow do odebrania.
 * 						-buffer: wskaznik na tablice zawierajaca dane.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_ReadBytes(uint8_t SLA, uint8_t address, uint8_t size, uint8_t* buffer) {
	TWI_Start();
	TWI_Write_SLA(SLA);
	TWI_WriteByte(address);
	TWI_RStart();
	TWI_Write_SLA(SLA + 1);

	while (size--) {
		*buffer++ = size ? TWI_ReadByte_ACK() : TWI_ReadByte_NACK();
	}
}

/**
 * @ Opis:				Wysyla ciag bajtow.
 * @ Parametry:			-SLA: adres slave ukladu.
 * 						-address: adres rejestru.
 * 						-size: liczba bajtow do wyslania.
 * 						-buffer: wskaznik na tablice zawierajaca dane.
 * @ Zwracana wartosc: 	Brak.
 */
void TWI_WriteBytes(uint8_t SLA, uint8_t address, uint8_t size, uint8_t* buffer) {
	TWI_Start();
	TWI_Write_SLA(SLA);
	TWI_WriteByte(address);
	while (size--)
		TWI_WriteByte(*buffer++);
	TWI_Stop();
}
