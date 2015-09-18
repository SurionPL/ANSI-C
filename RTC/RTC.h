/*
 * RTC.h
 *
 *  Created on: 2 wrz 2015
 *      Author: Bartek
 */

#ifndef RTC_H_
#define RTC_H_

#define DS1307_W 0xD0				//Data write
#define DS1307_R 0xD1

#define SQW_PIN  PB1
#define SQW_PORT PORTB

#define DS1307_SEC	0x00	//DS1307 Control Register address
#define DS1307_MIN	0x01	//DS1307 Control Register address
#define DS1307_HRS	0x02	//DS1307 Control Register address
#define DS1307_DAY	0x03	//DS1307 Control Register address
#define DS1307_DATE	0x04	//DS1307 Control Register address
#define DS1307_MTH	0x04	//DS1307 Control Register address
#define DS1307_YEAR	0x04	//DS1307 Control Register address
#define DS1307_CR	0x07	//DS1307 Control Register address

typedef struct
{

}RTC_TypeDef;


typedef struct
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}RTC_DataTimeTypedef;


void RTC_Init();
void RTC_SetDate(uint16_t year, uint8_t month, uint8_t day);
void RTC_SetTime(uint8_t hour, uint8_t minute, uint8_t second);
void RTC_SetDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
#endif /* RTC_H_ */