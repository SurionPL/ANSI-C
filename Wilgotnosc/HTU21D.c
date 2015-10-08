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
