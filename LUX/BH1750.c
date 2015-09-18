/*
 * BH1750.c
 *
 *  Created on: 11 wrz 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "BH1750.h"
#include "I2C.h"

void BH1750_PowerOn()
{
	_delay_us(5);
	BH1750_DVI_PORT |= BH1750_Power_ON << BH1750_DVI_PIN;


}

void BH1750_PowerDown()
{
	BH1750_DVI_PORT &= ~(BH1750_Power_OFF << BH1750_DVI_PIN);
}

void BH1750_Start(BH1750_InitTypeDef* BH1750_Struct)
{
	//void TWI_Init();
	TWI_Start();
	TWI_Send_SLA(BH1750_W);
	TWI_Write(BH1750_Struct->Mode);
	TWI_Stop();

}


uint16_t BH1750_Read(uint8_t mode)
{
#if mode == 1
  Serial.print("Light level: ");
  Serial.println(level);
#endif
	uint16_t result = 0;
	uint16_t lux = 0;
	TWI_Start();
	TWI_Send_SLA(BH1750_R);
	result = TWI_Read_ACK();
	result <<= 8;
	result |= TWI_Read_NACK();
	TWI_Stop();

	if(mode == BH1750_CHR_MODE2 || mode == BH1750_OTHR_MODE2)
	{
		lux = (result >> 1) * 10 / 12;
		if((result & 0x01) == 1)
		{
			lux++;
		}
	}
	else
	{
		lux = result * 10 / 12;
	}

	return lux;
}

