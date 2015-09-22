/*
 * RTC.c

 *
 *  Created on: 2 wrz 2015
 *      Author: Bartlomiej Kusmierczyk
 *      Library for DS1307
 */

#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "RTC.h"




void RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{

}


void RTC_GetTemp(int8_t* integer, uint8_t* fract)
{

	uint8_t temporary = 0;
	TWI_Start();
	TWI_Write_SLA(DS3231_SLA);
	TWI_WriteByte(DS3231_TEMP_MSB);
	TWI_RStart();
	TWI_Write_SLA(DS3231_SLA + 1);
	*integer = TWI_ReadByte_ACK();
	temporary = TWI_ReadByte_NACK();
	TWI_Stop();
	if(temporary != 0)
		*fract = (temporary >> 6) * 25;
	else
		*fract = 0;
}
