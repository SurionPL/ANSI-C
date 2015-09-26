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

void RTC_Init(RTC_InitTypeDef* RTC_InitStruct) {
	uint8_t CR = 0;

	if(RTC_InitStruct->RTC_Oscillator == DISABLE) {
		CR |= EOSC;
	}
	else if(RTC_InitStruct->RTC_Oscillator == ENABLE)
	{

	}
}

void RTC_GetTemp(int8_t* integer, uint8_t* fract) {

	uint8_t temporary = 0;
	TWI_Start();
	TWI_Write_SLA(DS3231_SLA);
	TWI_WriteByte(DS3231_TEMP_MSB);
	TWI_RStart();
	TWI_Write_SLA(DS3231_SLA + 1);
	*integer = TWI_ReadByte_ACK();
	temporary = TWI_ReadByte_NACK();
	TWI_Stop();
	if (temporary != 0)
		*fract = (temporary >> 6) * 25;
	else
		*fract = 0;
}

uint8_t RTC_DecToBCD(uint8_t decimal) {
	return ((decimal / 10) << 4) | (decimal % 10);
}

uint8_t RTC_BCDToDec(uint8_t bcd) {
	return ((((bcd >> 4) & 0x0F) * 10) | (bcd & 0x0F));
}



void RTC_SetTime(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t time[3];
	time[0] = RTC_DecToBCD(DateTimeStruct->seconds);
	time[1] = RTC_DecToBCD(DateTimeStruct->minutes);
	time[2] = RTC_DecToBCD(DateTimeStruct->hours);
	TWI_WriteBytes(DS3231_SLA, DS3231_SEC, 3, time);
}

void RTC_SetDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t date[4];
	date[0] = RTC_DecToBCD(DateTimeStruct->day_of_week);
	date[1] = RTC_DecToBCD(DateTimeStruct->day);
	date[2] = RTC_DecToBCD(DateTimeStruct->month);
	date[2] = RTC_DecToBCD(DateTimeStruct->year);
	TWI_WriteBytes(DS3231_SLA, DS3231_DAY, 4, date);
}

void RTC_SetTimeDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	RTC_SetTime(DateTimeStruct);
	RTC_SetDate(DateTimeStruct);
}

void RTC_GetTime(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t time[3];
	TWI_ReadBytes(DS3231_SLA, DS3231_SEC, 3, time);
	DateTimeStruct->seconds = RTC_BCDToDec(time[0]);
	DateTimeStruct->minutes = RTC_BCDToDec(time[1]);
	DateTimeStruct->hours =   RTC_BCDToDec(time[2]);
}

void RTC_GetDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t date[4];
	TWI_ReadBytes(DS3231_SLA, DS3231_SEC, 4, date);
	DateTimeStruct->day_of_week = date[0];
	DateTimeStruct->day   		= RTC_BCDToDec(date[1]);
	DateTimeStruct->month 		= RTC_BCDToDec(date[2]);
	DateTimeStruct->year  		= RTC_BCDToDec(date[3]);
}

void RTC_GetTimeDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	RTC_GetTime(DateTimeStruct);
	RTC_GetDate(DateTimeStruct);
}
