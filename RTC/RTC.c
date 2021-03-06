/**
 *******************************************************************************
 * @ File    RTC.c
 * @ Author  Bartlomiej Kusmierczyk
 * @ Version V1.0
 * @ Date    02-September-2015
 * @ Brief   This file contains all the DS3231 real-time clock firmware
 * 			 functions. RTC works in 24-hours format.
 *******************************************************************************
 */



/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "RTC.h"


RTC_RegistersTypeDef RTC_RegistersStruct;


/**
 * @ Brief  	Initializes DS3231.
 * @ Parameter  RTC_InitStruct: pointer to a RTC_InitTypeDef which contains the
 * 				configuration informations.
 * @ Retval 	None.
 */
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct) {

	RTC_RegistersStruct.RTC_Alarm1 = RTC_InitStruct->RTC_Alarm1;
	RTC_RegistersStruct.RTC_Alarm2 = RTC_InitStruct->RTC_Alarm2;

	RTC_RegistersStruct.CR = 0;

	/* Disable oscillator 32 kHz */
	if(RTC_InitStruct->RTC_Oscillator == DISABLE) {
		RTC_RegistersStruct.CR = EOSC;
	}

	/* Set Square Wave Output or alarms*/
	if(RTC_InitStruct->RTC_SQW != SQW_Disable)
	{
		if(RTC_InitStruct->RTC_SQW == SQW_Freq_1024Hz)
		{
			RTC_RegistersStruct.CR |= RS1;
		}
		else if(RTC_InitStruct->RTC_SQW == SQW_Freq_4096Hz)
		{
			RTC_RegistersStruct.CR |= RS2;
		}
		else if(RTC_InitStruct->RTC_SQW == SQW_Freq_8192Hz)
		{
			RTC_RegistersStruct.CR |= RS2 | RS1;
		}
		//Default: 1Hz
	}
	else if(RTC_InitStruct->RTC_SQW == SQW_Disable)
	{
		//RTC_RegistersStruct.CR |= INTCN;
		if(RTC_InitStruct->RTC_Alarm1 != Alarm1_Disable)
		{
			RTC_RegistersStruct.CR |= A1IE;
		}
		if(RTC_InitStruct->RTC_Alarm2 != Alarm2_Disable)
		{
			RTC_RegistersStruct.CR |= A2IE;
		}
		RTC_RegistersStruct.CR |= INTCN;
	}
	else
	{
		RTC_RegistersStruct.CR |= INTCN;		//Default: Alarms and SQW disabled
	}

	/* Send configuration */
	TWI_Start();
	TWI_Write_SLA(DS3231_SLA);
	TWI_WriteByte(DS3231_CR);
	TWI_WriteByte(RTC_RegistersStruct.CR);
	TWI_Stop();


}


/**
 * @ Brief  	Sets the alarms.
 * @ Parameter  RTC_AlarmStruct: pointer to a RTC_AlarmTypedef which contains the
 * 				alarm configuration informations - time and date.
 * @ Retval 	None.
 */
void RTC_SetAlarm(RTC_AlarmTypedef* RTC_AlarmStruct)
{
	if((RTC_RegistersStruct.RTC_Alarm1 != Alarm1_Disable) | (RTC_RegistersStruct.RTC_Alarm2 != Alarm2_Disable))
	{
		if((RTC_AlarmStruct->seconds 	 >= 60) | (RTC_AlarmStruct->seconds 	< 0)) RTC_AlarmStruct->seconds = 0;
		if((RTC_AlarmStruct->minutes 	 >= 60) | (RTC_AlarmStruct->minutes 	< 0)) RTC_AlarmStruct->minutes = 0;
		if((RTC_AlarmStruct->hours   	 >  24) | (RTC_AlarmStruct->hours   	< 0)) RTC_AlarmStruct->hours = 0;
		if((RTC_AlarmStruct->day     	 >  31) | (RTC_AlarmStruct->day     	< 0)) RTC_AlarmStruct->day = 0;
		if((RTC_AlarmStruct->day_of_week >   7) | (RTC_AlarmStruct->day_of_week < 1)) RTC_AlarmStruct->day_of_week = 0;

		if(RTC_RegistersStruct.RTC_Alarm1 != Alarm1_Disable)
		{
			uint8_t alarm[4];

			if(RTC_RegistersStruct.RTC_Alarm1 == Alarm1_OncePerSec)
			{
				alarm[0] = A1M1;
				alarm[1] = A1M2;
				alarm[2] = A1M3;
				alarm[3] = A1M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm1 == Alarm1_Sec)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->seconds);
				alarm[1] = A1M2;
				alarm[2] = A1M3;
				alarm[3] = A1M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm1 == Alarm1_MinSec)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->seconds);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[2] = A1M3;
				alarm[3] = A1M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm1 == Alarm1_HoursMinSec)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->seconds);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[2] = RTC_DecToBCD(RTC_AlarmStruct->hours);
				alarm[3] = A1M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm1 == Alarm1_DateHoursMinSec)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->seconds);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[2] = RTC_DecToBCD(RTC_AlarmStruct->hours);
				alarm[3] = RTC_DecToBCD(RTC_AlarmStruct->day);
			}
			else if(RTC_RegistersStruct.RTC_Alarm1 == Alarm1_DayHoursMinSec)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->seconds);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[2] = RTC_DecToBCD(RTC_AlarmStruct->hours);
				alarm[3] = DY_DT | RTC_DecToBCD(RTC_AlarmStruct->day_of_week);
			}
			else
			{
				alarm[0] = A1M1;
				alarm[1] = A1M2;
				alarm[2] = A1M3;
				alarm[3] = A1M4;
			}
			TWI_WriteBytes(DS3231_SLA, DS3231_ALARM1_SEC, 4, alarm);
		}

		if(RTC_RegistersStruct.RTC_Alarm2 != Alarm2_Disable)
		{

			uint8_t alarm[3];
			if(RTC_RegistersStruct.RTC_Alarm2 == Alarm2_OncePerMin)
			{
				alarm[0] = A2M2;
				alarm[1] = A2M3;
				alarm[2] = A2M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm2 == Alarm2_Min)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[1] = A2M3;
				alarm[2] = A2M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm2 == Alarm2_HoursMin)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->hours);
				alarm[2] = A2M4;
			}
			else if(RTC_RegistersStruct.RTC_Alarm2 == Alarm2_DateHoursMin)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->hours);
				alarm[2] = RTC_DecToBCD(RTC_AlarmStruct->day);
			}
			else if(RTC_RegistersStruct.RTC_Alarm2 == Alarm2_DayHoursMin)
			{
				alarm[0] = RTC_DecToBCD(RTC_AlarmStruct->minutes);
				alarm[1] = RTC_DecToBCD(RTC_AlarmStruct->hours);
				alarm[2] = DY_DT | RTC_DecToBCD(RTC_AlarmStruct->day_of_week);
			}
			else
			{
				alarm[0] = A2M2;
				alarm[1] = A2M3;
				alarm[2] = A2M4;
			}
			TWI_WriteBytes(DS3231_SLA, DS3231_ALARM2_MIN, 3, alarm);
		}

		RTC_RegistersStruct.CR |= INTCN;

		TWI_Start();
		TWI_Write_SLA(DS3231_SLA);
		TWI_WriteByte(DS3231_CR);
		TWI_WriteByte(RTC_RegistersStruct.CR);
		TWI_Stop();
	}
}


/**
 * @ Brief  	Reads the temperature.
 * @ Parameter  integer: pointer to variable which contains the integer part
 * 				of temperature value.
 * 				fract: pointer to variable which contains the fractional part
 * 				of the temperature.
 * @ Retval 	None.
 */
void RTC_GetTemp(int8_t* integer, uint8_t* fract) {

	uint8_t temporary = 0;

	/* Read register value */
	TWI_Start();
	TWI_Write_SLA(DS3231_SLA);
	TWI_WriteByte(DS3231_TEMP_MSB);
	TWI_RStart();
	TWI_Write_SLA(DS3231_SLA + 1);
	*integer = TWI_ReadByte_ACK();
	temporary = TWI_ReadByte_NACK();
	TWI_Stop();

	if (temporary != 0)
	{
		*fract = (temporary >> 6) * 25;
	}
	else
	{
		*fract = 0;
	}
}


/**
 * @ Brief  	Sets the time.
 * @ Parameter  DateTimeStruct: pointer to a RTC_DateTimeTypedef which contains the
 * 				configuration informations - time and date.
 * @ Retval 	None.
 */
void RTC_SetTime(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t time[3];

	/* Convert values to BCD and save in structure */
	time[0] = RTC_DecToBCD(DateTimeStruct->seconds);
	time[1] = RTC_DecToBCD(DateTimeStruct->minutes);
	time[2] = RTC_DecToBCD(DateTimeStruct->hours);

	/* Send time */
	TWI_WriteBytes(DS3231_SLA, DS3231_SEC, 3, time);
}


/**
 * @ Brief  	Sets the date.
 * @ Parameter  DateTimeStruct: pointer to a RTC_DateTimeTypedef which contains the
 * 				configuration informations - time and date.
 * @ Retval 	None.
 */
void RTC_SetDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t date[4];

	/* Convert value do BCD and save in array */
	date[0] = DateTimeStruct->day_of_week;
	date[1] = RTC_DecToBCD(DateTimeStruct->day);
	date[2] = RTC_DecToBCD(DateTimeStruct->month);
	date[2] = RTC_DecToBCD(DateTimeStruct->year);

	/* Send date */
	TWI_WriteBytes(DS3231_SLA, DS3231_DAY, 4, date);
}


/**
 * @ Brief  	Sets time and date.
 * @ Parameter  DateTimeStruct: pointer to a RTC_DateTimeTypedef which contains the
 * 				configuration informations - time and date.
 * @ Retval 	None.
 */
void RTC_SetTimeDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	RTC_SetTime(DateTimeStruct);
	RTC_SetDate(DateTimeStruct);
}


/**
 * @ Brief  	Gets the time from DS3231.
 * @ Parameter  DateTimeStruct: pointer to a RTC_DateTimeTypedef.
 * @ Retval 	None.
 */
void RTC_GetTime(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t time[3];

	/* Read time */
	TWI_ReadBytes(DS3231_SLA, DS3231_SEC, 3, time);

	/* Convert values to decimal and save in structure */
	DateTimeStruct->seconds = RTC_BCDToDec(time[0]);
	DateTimeStruct->minutes = RTC_BCDToDec(time[1]);
	DateTimeStruct->hours   = RTC_BCDToDec(time[2]);
}


/**
 * @ Brief  	Gets the date from DS3231.
 * @ Parameter  DateTimeStruct: pointer to a RTC_DateTimeTypedef.
 * @ Retval 	None.
 */
void RTC_GetDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	uint8_t date[4];

	/* Read date */
	TWI_ReadBytes(DS3231_SLA, DS3231_SEC, 4, date);

	/* Convert values do decimal and save in structure */
	DateTimeStruct->day_of_week = date[0];
	DateTimeStruct->day   		= RTC_BCDToDec(date[1]);
	DateTimeStruct->month 		= RTC_BCDToDec(date[2]);
	DateTimeStruct->year  		= RTC_BCDToDec(date[3]);
}


/**
 * @ Brief  	Gets time and date from DS3231.
 * @ Parameter  DateTimeStruct: pointer to a RTC_DateTimeTypedef.
 * @ Retval 	None.
 */
void RTC_GetTimeDate(RTC_DateTimeTypedef* DateTimeStruct)
{
	RTC_GetTime(DateTimeStruct);
	RTC_GetDate(DateTimeStruct);
}


/**
 * @ Brief  	Converts decimal value to BCD code.
 * @ Parameter  decimal: decimal value.
 * @ Retval 	Value in BCD code.
 */
uint8_t RTC_DecToBCD(uint8_t decimal) {
	return ((decimal / 10) << 4) | (decimal % 10);
}


/**
 * @ Brief  	Converts BCD code to decimal value.
 * @ Parameter  bcd: value in BCD code.
 * @ Retval 	Decimal value.
 */
uint8_t RTC_BCDToDec(uint8_t bcd) {
	return ((((bcd >> 4) & 0x0F) * 10) + (bcd & 0x0F));
}
