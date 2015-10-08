/*
 * HTU21D.h
 *
 *  Created on: 1 pa� 2015
 *      Author: Bartek
 */

#ifndef HTU21D_H_
#define HTU21D_H_

#define HTU21D_SLA ((uint8_t)0x80)


#define HTU21D_TEMP_MEAS_HM		((uint8_t)0xE3)	/* Trigger Temperature Measurement (Hold Master)  */
#define HTU21D_HUM_MEAS_HM		((uint8_t)0xE5)	/* Trigger Humidity Measurement (Hold Master) */
#define HTU21D_TEMP_MEAS_NHM	((uint8_t)0xF3) /* Trigger Temperature Measurement (No Hold Master) */
#define HTU21D_HUM_MEAS_NHM		((uint8_t)0xF5) /* Trigger Humidity Measurement (No Hold Master) */
#define HTU21D_WRITE_UR			((uint8_t)0xE6) /* Write User Register */
#define HTU21D_READ_UR			((uint8_t)0xE7) /* Read User Register */
#define HTU21D_SOFT_RESET		((uint8_t)0xFE) /* Soft Reset */

typdef enum
{
	Hum12b_Temp14b,
	Hum8b_T12b,
	Hum

};



void HTU21D_Init();
void HTU21D_StartTemperature_NHM();
void HTU21D_StartHumidity_NHM();
void HTU21D_GetTemperature_HM();
void HTU21D_GetHumidity_HM();
//void HTU21D_

#endif /* HTU21D_H_ */
