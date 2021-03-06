/**
  *******************************************************************************
  * @ File    RTC.h
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    02-September-2015
  * @ Brief   This file contains all the functions prototypes for the DS3231
  * 		  real-time clock firmware library. RTC works in 24-hours format.
  *******************************************************************************
  */


#ifndef RTC_H_
#define RTC_H_


/** @ Defgroup: DS3231 slave address
  */
#define DS3231_SLA ((uint8_t)0xD0)

/* Adresy rejestrow */
#define DS3231_SEC			((uint8_t)0x00)		/*	Sekundy								*/
#define DS3231_MIN			((uint8_t)0x01)		/*	Minuty								*/
#define DS3231_HRS			((uint8_t)0x02)		/*	Godziny								*/
#define DS3231_DAY			((uint8_t)0x03)		/*	Dzien tygodnia						*/
#define DS3231_DATE			((uint8_t)0x04)		/*	Dzien miesiaca						*/
#define DS3231_MC			((uint8_t)0x05)		/*	Miesiac / Wiek						*/
#define DS3231_YEAR			((uint8_t)0x06)		/*	Rok									*/
#define DS3231_ALARM1_SEC	((uint8_t)0x07)	 	/*	Alarm 1 Sekundy						*/
#define DS3231_ALARM1_MIN	((uint8_t)0x08) 	/*	Alarm 1 Minuty						*/
#define DS3231_ALARM1_HRS	((uint8_t)0x09)		/*	Alarm 1 Godziny						*/
#define DS3231_ALARM1_DD	((uint8_t)0x0A)		/*	Alarm 1 Dzien tyg. / Dzien mies.	*/
#define DS3231_ALARM2_MIN	((uint8_t)0x0B)		/*	Alarm 1 Minuty  					*/
#define DS3231_ALARM2_HRS	((uint8_t)0x0C) 	/*	Alarm 2 Godziny						*/
#define DS3231_ALARM2_DD	((uint8_t)0x0D) 	/*	Alarm 2 Dzien tyg. / Dzien mies.	*/
#define DS3231_CR			((uint8_t)0x0E)		/*	Control Register		 			*/
#define DS3231_CSR			((uint8_t)0x0F)		/*	Rejestr kontrolny / statusowy		*/
#define DS3231_AO			((uint8_t)0x10)		/*	Rejestr starzenia					*/
#define DS3231_TEMP_MSB		((uint8_t)0x11)		/*	Czesc MSB temperatury				*/
#define DS3231_TEMP_LSB		((uint8_t)0x12)		/*	Czesc LSB temperatury				*/


/* Bity konfiguracyjne alarmow */
#define A1M1  ((uint8_t)0x80)
#define A1M2  ((uint8_t)0x80)
#define A1M3  ((uint8_t)0x80)
#define A1M4  ((uint8_t)0x80)
#define A2M2  ((uint8_t)0x80)
#define A2M3  ((uint8_t)0x80)
#define A2M4  ((uint8_t)0x80)
#define DY_DT ((uint8_t)0x40)

/* Bity konfiguracyjne DS3231 */
#define EOSC	((uint8_t)0x80)		/* Wlaczanie oscylatora  */
#define BBSQW	((uint8_t)0x40)		/* Battery-Backed Square-Wave Enable*/
#define CONV	((uint8_t)0x20)		/* Pomiar temperatury				 */
#define RS2		((uint8_t)0x10)		/* Rate Select 2 (Freq of SQW) */
#define RS1		((uint8_t)0x08)		/* Rate Select 1 (Freq of SQW) */
#define INTCN	((uint8_t)0x04)     /* Interrupt Control */
#define A2IE	((uint8_t)0x02)		/* Alarm 2 Interrupt Enable */
#define A1IE	((uint8_t)0x01)		/* Alarm 1 Interrupt Enable */

/** @ Defgroup: Days of week
  */
#define MONDAY	  ((uint8_t)0x01)
#define TUESDAY   ((uint8_t)0x02)
#define WEDNESDAY ((uint8_t)0x03)
#define THURSDAY  ((uint8_t)0x04)
#define FRIDAY 	  ((uint8_t)0x05)
#define SATURDAY  ((uint8_t)0x06)
#define SUNDAY    ((uint8_t)0x07)

/** @ Defgroup: Months
  */
#define JANUARY	  ((uint8_t)0x01)
#define FEBRUARY  ((uint8_t)0x02)
#define MARCH 	  ((uint8_t)0x03)
#define APRIL  	  ((uint8_t)0x04)
#define MAY 	  ((uint8_t)0x05)
#define JUNE      ((uint8_t)0x06)
#define JULY      ((uint8_t)0x07)
#define AUGUST    ((uint8_t)0x08)
#define SEPTEMBER ((uint8_t)0x09)
#define OCTOBER   ((uint8_t)0x0A)
#define NOVEMBER  ((uint8_t)0x0B)
#define DECEMBER  ((uint8_t)0x0C)


/** @ Defgroup: New state enumeration
  */
typedef enum {
	DISABLE = 0, ENABLE = !DISABLE

} NewState;


/** @ Defgroup: DS3231 DateTime_Struct which contains
 *  			time and date values.
  */
typedef struct {
	uint8_t  seconds;
	uint8_t  minutes;
	uint8_t  hours;
	uint8_t  day;
	uint8_t  day_of_week;
	uint8_t  month;
	uint8_t year;
} RTC_DateTimeTypedef;


/** @ Defgroup: DS3231 frequencies of the square-wave output enumeration
  */
typedef enum {
	SQW_Disable = 0,
	SQW_Freq_1Hz,
	SQW_Freq_1024Hz,
	SQW_Freq_4096Hz,
	SQW_Freq_8192Hz
} RTC_SQWFreqTypeDef;


/** @ Defgroup: DS3231 Alarm1 modes configuration enumeration
  */
typedef enum {
	Alarm1_Disable = 0,
	Alarm1_OncePerSec,
	Alarm1_Sec,
	Alarm1_MinSec,
	Alarm1_HoursMinSec,
	Alarm1_DateHoursMinSec,
	Alarm1_DayHoursMinSec,
} RTC_Alarm1TypeDef;


/** @ Defgroup: DS3231 Alarm2 modes configuration enumeration
  */
typedef enum {
	Alarm2_Disable = 0,
	Alarm2_OncePerMin,
	Alarm2_Min,
	Alarm2_HoursMin,
	Alarm2_DateHoursMin,
	Alarm2_DayHoursMin,
} RTC_Alarm2TypeDef;


/** @ Defgroup: DS3231 registers structure which contains alarm
 * 				modes and control register value.
  */
typedef struct
{
	uint8_t CR;
	RTC_Alarm1TypeDef RTC_Alarm1;
	RTC_Alarm2TypeDef RTC_Alarm2;
}RTC_RegistersTypeDef;


/** @ Defgroup: DS3231 Init structure definition.
  */
typedef struct {
	NewState RTC_Oscillator;
	RTC_SQWFreqTypeDef RTC_SQW;
	NewState BB_SQW;
	RTC_Alarm1TypeDef RTC_Alarm1;
	RTC_Alarm2TypeDef RTC_Alarm2;

} RTC_InitTypeDef;


/** @ Defgroup: DS3231 Alarm structure definition.
  */
typedef struct
{
	volatile uint8_t  seconds;
	volatile uint8_t  minutes;
	volatile uint8_t  hours;
	volatile uint8_t  day;
	volatile uint8_t  day_of_week;
}RTC_AlarmTypedef;


/** @ Defgroup: DS3231 functions
  */
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_SetAlarm(RTC_AlarmTypedef* RTC_AlarmStruct);
void RTC_SetTime(RTC_DateTimeTypedef* DateTimeStruct);
void RTC_SetDate(RTC_DateTimeTypedef* DateTimeStruct);
void RTC_SetTimeDate(RTC_DateTimeTypedef* DateTimeStruct);
void RTC_GetTime(RTC_DateTimeTypedef* DateTimeStruct);
void RTC_GetDate(RTC_DateTimeTypedef* DateTimeStruct);
void RTC_GetTimeDate(RTC_DateTimeTypedef* DateTimeStruct);
void RTC_GetTemp(int8_t* integer, uint8_t* fract);
uint8_t RTC_DecToBCD(uint8_t decimal);
uint8_t RTC_BCDToDec(uint8_t bcd);

#endif /* RTC_H_ */
