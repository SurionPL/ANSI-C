/*
 * TWI.c
 *
 *  Created on: 26 lip 2015
 *      Author: Bartek
 */

/**
  *******************************************************************************
  * @ File    I2C.h
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    26-July-2015
  * @ Brief   This file contains all the TWI interface firmware functions.
  *******************************************************************************
  */



/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <util/TWI.h>
#include "I2C.h"
//#include "USART.h"

//Dodac jakas error flag!
uint8_t TWI_ErrorFlag = 0;

char table[2] = {'O','K'};			//?????????
char table2[2] = {'N','O'};

//void TWI_Init(TWI_InitTypeDef* TWI_InitStruct)

void TWI_Init(uint16_t speed)
{
	TWCR = (1<<TWEA) | (1<<TWEN);


	speed=(4000000/speed/100-16)/2;
	uint8_t prescaler = 0;
	while(speed>255) {
		prescaler++;
		speed/=4;
	}
	TWSR = (TWSR & ((1<<TWPS1) | (1<<TWPS0))) | prescaler;
	TWBR = speed;
}

void TWI_Start()  //Dodac zwracanie statusu wszedzie!
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	//Wait for TWINT Flag set. This	indicates that the START condition
	//has been transmitted
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_START) {
		TWI_ERROR(I2C_START_ERROR);
		//return I2C_START_ERROR;
	}
	//return 0;
}


void TWI_RStart() {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	//Wait for TWINT Flag set. This	indicates that the START condition
	//has been transmitted
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_REP_START) {
		TWI_ERROR(I2C_REP_START_ERROR);
		//return I2C_START_ERROR;
	}
	//return 0;
}

void TWI_Stop()
{
	//Send Stop bit
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void TWI_Write_SLA(uint8_t address)
{
	uint8_t status;
	if((address & 0x01) == 0) status = TW_MT_SLA_ACK;
	else status = TW_MR_SLA_ACK;
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT))); //Czekaj na zakonczenie
	if (TW_STATUS != status)
	{
		TWI_ERROR(I2C_ACK_ERROR); //NACK error
		//return I2C_ACK_ERROR;
		//Send_String(table2,2);
	}
	//return 0;
}


void TWI_WriteByte(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if(TW_STATUS != TW_MT_DATA_ACK)
		TWI_ERROR(I2C_NACK_ERROR);
}

uint8_t TWI_ReadByte_NACK()
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if(TW_STATUS != TW_MR_DATA_ACK) {
		TWI_ERROR(I2C_NACK_ERROR);
	}
	return TWDR;
}

uint8_t TWI_ReadByte_ACK()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	if (TW_STATUS != TW_MR_DATA_ACK) TWI_ERROR(I2C_NACK_ERROR);
	return TWDR;
}





void TWI_ERROR(uint8_t error)
{
	TWI_ErrorFlag = error;
	if(error == I2C_START_ERROR)
	{DDRB = 2;
	PORTB = 2;}
	//Wypelnic czyms do interfejsu z uzytkownikiem
}


void TWI_ReadBytes(uint8_t SLA, uint8_t address ,uint8_t size, uint8_t* buffer)
{
	TWI_Start();
	TWI_Write_SLA(SLA);
	TWI_WriteByte(address);
	TWI_RStart();
	TWI_Write_SLA(SLA+1);
	//while (size--) *buffer++ = size ? TWI_ReadByte_ACK() : ( len ? ACK : NACK );
	while(size--)
	{
		*buffer++ = size ? TWI_ReadByte_ACK() : TWI_ReadByte_NACK();
	}


	/*
	for (uint8_t i=0; i<size-1; i++) {
		buffer[i] = TWI_ReadByte_ACK();
	}
	buffer[size-1]=TWI_ReadByte_NACK();
	*/
}

void TWI_WriteBytes(uint8_t SLA, uint8_t address ,uint8_t size, uint8_t* buffer)
{
	TWI_Start();
	TWI_Write_SLA(SLA);
	TWI_WriteByte(address);
	while (size--) TWI_WriteByte(*buffer++);
	TWI_Stop();
}
