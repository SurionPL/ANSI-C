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





void RTC_Init()
{
	TWI_Init();
}
