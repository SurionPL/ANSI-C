/**
 *******************************************************************************
 * @ File    BH1750.c
 * @ Author  Bartlomiej Kusmierczyk
 * @ Version V1.0
 * @ Date    11-September-2015
 * @ Brief   This file contains all the BH1750 digital ambient light sensor
 * 			 firmware functions.
 *******************************************************************************
 */


/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "BH1750.h"
#include "I2C.h"

uint8_t state_;
uint8_t mode_;


/**
 * @ Brief  	Switches the sensor to power on mode.
 * @ Parameter  None.
 * @ Retval 	None
 */
void BH1750_PowerOn()
{
	_delay_us(5);
	//BH1750_DVI_PORT |= BH1750_Power_ON << BH1750_DVI_PIN;
	state_ = BH1750_Power_ON;
	TWI_Start();
	TWI_Write_SLA(BH1750_SLA);
	TWI_WriteByte(BH1750_Power_ON);
	TWI_Stop();
}


/**
 * @ Brief  	Switches the sensor to power down mode.
 * @ Parameter  None.
 * @ Retval 	None
 */
void BH1750_PowerDown()
{
	//BH1750_DVI_PORT &= ~(BH1750_Power_OFF << BH1750_DVI_PIN);
	state_ = BH1750_Power_OFF;
	TWI_Start();
	TWI_Write_SLA(BH1750_SLA);
	TWI_WriteByte(BH1750_Power_OFF);
	TWI_Stop();
}


/**
 * @ Brief  	Starts illuminance measurement.
 * @ Parameter  mode: measurement mode.
 * @ Retval 	None
 */
void BH1750_Start(uint8_t mode)
{
	mode_ = mode;
	TWI_Start();
	TWI_Write_SLA(BH1750_SLA);
	TWI_WriteByte(mode_);
	TWI_Stop();
}


/**
 * @ Brief  	Reads measurement result (illuminance).
 * @ Parameter  None.
 * @ Retval 	Illuminance in lux (lx) units. The highest resolution is 1lx.
 */
uint16_t BH1750_Read()
{
	uint32_t result;
	uint8_t msb, lsb;
	uint16_t lux = 0;

	TWI_Start();
	TWI_Write_SLA(BH1750_SLA + 1);
	msb = TWI_ReadByte_ACK();
	lsb = TWI_ReadByte_NACK();
	TWI_Stop();

	result = ((msb << 8) | lsb) * 10;		//Lux = Register / 1,2 == reg*10 / 12

	lux = (uint16_t)(result / 12);

	if(((mode_ == BH1750_CHR_MODE2) || (mode_ == BH1750_OTHR_MODE2)) && ((result % 12 ) >= 6))
	{
		lux++;
	}

	return lux;
}

/**
 * @ Brief  	Resets the BH1750 data register. After that, switches
 * 				sensor to power down mode.
 * @ Parameter  None.
 * @ Retval 	None.
 */
void BH1750_ResetDR()
{
	if(state_ == BH1750_Power_OFF) BH1750_PowerOn();

	TWI_Start();
	TWI_Write_SLA(BH1750_SLA);
	TWI_WriteByte(BH1750_RESET);
	TWI_Stop();

	BH1750_PowerDown();
}

