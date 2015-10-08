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
