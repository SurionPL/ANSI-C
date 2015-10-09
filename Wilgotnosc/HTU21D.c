/*
 * HTU21D.c
 *
 *  Created on: 1 pa� 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "HTU21D.h"
#include "I2C.h"

HTU21D_RegistersTypeDef RegistersStruct;

void HTU21D_StartTemperature_NHM()
{
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_TEMP_MEAS_NHM);
	TWI_Stop();
}

void HTU21D_StartHumidity_NHM()
{
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_HUM_MEAS_NHM);
	TWI_Stop();
}


void HTU21D_GetTemperature_NHM(int8_t* integer, uint8_t* fractional)
{
	//dodac checksum
	uint8_t msb, lsb, checksum;
	int16_t temperature;
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA + 1);
	msb = TWI_ReadByte_ACK();
	lsb = TWI_ReadByte_ACK();
	checksum = TWI_ReadByte_NACK();
	TWI_Stop();
	if((lsb & 0x02) == HTU21D_TYPE_TEMPERATURE)
	{
		temperature = -4685 + ((((uint32_t)17572) * (((uint16_t)msb) | (lsb & 0xFC))) >> 16);
		//*integer = temperature / 100;
		//*fractional = temperature % 100;
	}
}


uint8_t HTU21D_GetHumidity_NHM()
{
	//dodac checksum
	uint8_t msb, lsb, checksum;
	int8_t humidity;
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA + 1);
	msb = TWI_ReadByte_ACK();
	lsb = TWI_ReadByte_ACK();
	checksum = TWI_ReadByte_NACK();
	TWI_Stop();
	if((lsb & 0x02) == HTU21D_TYPE_HUMIDITY)
	{
		humidity = -6 + (((uint32_t)125 * ((uint16_t)msb | (lsb & 0xFC))) >> 16 );

		if(humidity < 0) return (0);

		return ((uint8_t)humidity);
	}
	else
	{
		return (0);
	}

}

void HTU21D_GetTemperature_HM()
{
	//dodac checksum
	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_HUM_MEAS_HM);
	TWI_RStart();
	TWI_Write_SLA(HTU21D_SLA + 1);

}


void HTU21D_GetHumidity_HM()
{
	//dodac checksum
}


void HTU21D_Init(HTU21D_ResolutionTypeDef Resolution)
{

	//moze zmienic default value????????????????????????????????
	if(Resolution == Humidity8b_Temperature12b)
	{
		RegistersStruct.UR = 0x03;			//?? dodac define
	}
	else if(Resolution == Humidity10b_Temperature13b)
	{
		RegistersStruct.UR = 0x82;
	}
	else if(Resolution == Humidity11b_Temperature11b)
	{
		RegistersStruct.UR = 0x83;
	}
	else
	{
		RegistersStruct.UR = HTU21D_UR_DEFAULT;


	}

	TWI_Start();
	TWI_Write_SLA(HTU21D_SLA);
	TWI_WriteByte(HTU21D_WRITE_UR);
	TWI_WriteByte(RegistersStruct.UR);
	TWI_Stop();
}
