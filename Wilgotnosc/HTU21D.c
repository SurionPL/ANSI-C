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


/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "HTU21D.h"
#include "I2C.h"
#include "MKUART/mkuart.h"

HTU21D_RegistersTypeDef RegistersStruct;


/**
 * @ Brief  	Initializes the HTU21D sensor.
 * @ Parameter  HTU21D_ResolutionTypeDef: sensor measurement resolution.
 * @ Retval 	None.
 */
void HTU21D_Init(HTU21D_ResolutionTypeDef Resolution)
{
	/* Read user register (UR) */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_READ_UR);
	TWI_RStart();
	TWI_Write_SLA(HTU21D_SLA + 1);
	RegistersStruct.UR = TWI_ReadByte_NACK();
	TWI_Stop();
	RegistersStruct.UR &= 0x38;	// Save reserved bits


	if(Resolution == Humidity12b_Temperature14b)
	{
		RegistersStruct.UR |= 0x02;
	}
	else if(Resolution == Humidity8b_Temperature12b)
	{
		RegistersStruct.UR |= 0x03;			//?? dodac define
	}
	else if(Resolution == Humidity10b_Temperature13b)
	{
		RegistersStruct.UR |= 0x82;
	}
	else
	{
		RegistersStruct.UR |= HTU21D_UR_DEFAULT;
		//default value 11/11 bits
	}

	/* Send user register value */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_WRITE_UR);
	TWI_WriteByte(RegistersStruct.UR);
	TWI_Stop();
}


/**
 * @ Brief  	Starts the temperature measurement.
 * @ Parameter  None.
 * @ Retval 	None.
 */
void HTU21D_StartTemperature()
{
	/* Send temperature measurement command */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_TEMP_MEAS_NHM);
	TWI_Stop();
}


/**
 * @ Brief  	Starts the humidity measurement.
 * @ Parameter  None.
 * @ Retval 	None.
 */
void HTU21D_StartHumidity()
{
	/* Send humidity measurement command */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_HUM_MEAS_NHM);
	TWI_Stop();
}


/**
 * @ Brief  	Gets temperature value. Needs to use StartTemperature_NHM() function first.
 * @ Parameter  integer: pointer to value which keeps integer part of temperature.
 * 				fractional: pointer to value which keeps fractional part of temperature.
 * @ Retval 	None.
 */
void HTU21D_GetTemperature(int8_t* integer, uint8_t* fractional)
{
	//dodac checksum  ???????
	uint16_t result;
	int32_t temperature;

	/* Read result */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA + 1);
	result  = TWI_ReadByte_ACK() << 8;
	result |= TWI_ReadByte_NACK();
	//checksum = TWI_ReadByte_NACK();
	TWI_Stop();

	if((result & 0x02) == HTU21D_TYPE_TEMPERATURE)
	{
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
 * @ Brief  	Gets humidity value.
 * @ Parameter  None.
 * @ Retval 	Humidity value.
 */
int8_t HTU21D_GetHumidity()
{

	//dodac checksum  ???
	uint32_t result;
	int32_t humidity;

	/* Read data */
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA + 1);
	result = (TWI_ReadByte_ACK() << 8);
	result |=  TWI_ReadByte_NACK();
	//checksum = TWI_ReadByte_NACK();
	TWI_Stop();

	//uart_puts("\n-------\n");
	//uart_putc(msb);
	//uart_putc(lsb);
	//uart_puts("\n-------\n");
	//msb = 0x4E;
	//lsb = 0x85;
	//result = 0x4E85;

	if((result & 0x02) == HTU21D_TYPE_HUMIDITY)
	{
		//humidity = (((uint32_t)12500 * (((uint32_t)msb << 8) | (lsb & 0xFC))) / 65536 ) - 600;
		//humidity = (((uint32_t)12500 * (((((uint32_t)msb) << 8) | (lsb & 0xFC))) * 100) / 65536) - 600;
		//humidity = (((uint32_t)12500 * (uint32_t)(result & 0xFFFC)) / (uint32_t)65536) - (uint32_t)600;
		humidity = (((uint32_t)12500 * (uint32_t)(result & 0xFFFC)) >> 16) - (uint32_t)600;
		//humidity = (((uint32_t)12500 *  wynik) / 65536 ) - 600;
		//if(humidity < 0)
		//{
			//*integer = 0;
			//*fractional = 0;
		//}
		//else
		//{
		//}
		return  (uint8_t)(humidity / 100);
	}
	return (-1);
}



