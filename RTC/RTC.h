/*
 * RTC.h
 *
 *  Created on: 2 wrz 2015
 *      Author: Bartek
 */

#ifndef RTC_H_
#define RTC_H_

#define DS3231_SLA ((uint8_t)0xD0)				//Data write
#define DS3231_R 0xD1

#define SQW_PIN  PB1
#define SQW_PORT PORTB

/* Timekeeping Registers */						/*  		Function			*/
#define DS3231_SEC			((uint8_t)0x00)		/*	Seconds						*/
#define DS3231_MIN			((uint8_t)0x01)		/*	Minutes						*/
#define DS3231_HRS			((uint8_t)0x02)		/*	Hours						*/
#define DS3231_DAY			((uint8_t)0x03)		/*	Day							*/
#define DS3231_DATE			((uint8_t)0x04)		/*	Date						*/
#define DS3231_MC			((uint8_t)0x05)		/*	Month / Century				*/
#define DS3231_YEAR			((uint8_t)0x06)		/*	Year						*/
#define DS3231_ALARM1_SEC	((uint8_t)0x07)	 	/*	Alarm 1 Seconds				*/
#define DS3231_ALARM1_MIN	((uint8_t)0x08) 	/*	Alarm 1 Minutes				*/
#define DS3231_ALARM1_HRS	((uint8_t)0x09)		/*	Alarm 1 Hours 				*/
#define DS3231_ALARM1_DD	((uint8_t)0x0A)		/*	Alarm 1 Day / Date			*/
#define DS3231_ALARM2_MIN	((uint8_t)0x0B)		/*	Alarm 1 Minutes  			*/
#define DS3231_ALARM2_HRS	((uint8_t)0x0C) 	/*	Alarm 2 Hours				*/
#define DS3231_ALARM2_DD	((uint8_t)0x0D) 	/*	Alarm 2 Day / Date			*/
#define DS3231_CR			((uint8_t)0x0E)		/*	Control Register		 	*/
#define DS3231_CSR			((uint8_t)0x0F)		/*	Control / Status Register	*/
#define DS3231_AO			((uint8_t)0x10)		/*	Aging Offset				*/
#define DS3231_TEMP_MSB		((uint8_t)0x11)		/*	MSB of Temp					*/
#define DS3231_TEMP_LSB		((uint8_t)0x12)		/*	LSB of Temp					*/

#define EOSC 7//0x80
#define BBSQW 6
#define CONV 5
#define RS2 4
#define RS1 3


typedef enum
{
	DISABLE = 0,
	ENABLE = !DISABLE

}NewState;

typedef struct {
	uint8_t RTCCR;

} RTC_TypeDef;


typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t day_of_week;
	uint8_t month;
	uint16_t year;
	uint8_t century;
} RTC_DateTimeTypedef;

//frequency of the square-wave outpu
typedef enum
{
	Freq_1Hz = 0,
	Freq_1024Hz,
	Freq_4096Hz,
	Freq_8192Hz
}RTC_OutFreq_TypeDef;



typedef struct
{
	NewState RTC_Oscillator;
	RTC_OutFreq_TypeDef RTC_OutFreq;
	NewState RTC_Alarm1Int;
	NewState RTC_Alarm2Int;


} RTC_InitTypeDef;





void RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_SetDate(RTC_DateTimeTypedef*);
void RTC_SetTime(RTC_DateTimeTypedef*);
void RTC_SetDateTime(RTC_DateTimeTypedef*);
void RTC_GetTemp(int8_t* integer, uint8_t* fract);
uint8_t RTC_DecToBCD(uint8_t decimal);
uint8_t RTC_BCDToDec(uint8_t bcd);

#endif /* RTC_H_ */
