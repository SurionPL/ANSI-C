/*
 * AuxiliaryLib.c
 *
 *  Created on: 28 lis 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>

#include "../AVG/AVG.h"
#include "../ThingSpeak/ThingSpeak.h"
#include "../MKUART/mkuart.h"
#include "../HTU21D/HTU21D.h"
#include "../BH1750/BH1750.h"
#include "../ESP8266_CL/ESP8266_Cl.h"
#include "../BMP180/BMP180.h"
#include <stdio.h>


void initializeModules()
{
	//ESP_Init();
	//HTU21D_Init(Humidity10b_Temperature13b);
	//BMP180_Init(BMP180_Mode_ULP);
}


void sendTemperature(int8_t temperature)
{
	char value[7];
	sprintf(value, "%d", temperature);
	TS_UpdateField(value, 1);
}

void sendHumidity(uint8_t humidity)
{
	char value[7];
	sprintf(value, "%d", humidity);
	TS_UpdateField(value, 2);
}

void sendPressure(int32_t pressure)
{
	char value[7];
	sprintf(value, "%d", (int)(pressure/100));
	TS_UpdateField(value, 4);
}

void sendIlluminance(uint16_t illuminance)
{
	char value[7];
	sprintf(value, "%d", illuminance);
	TS_UpdateField(value, 4);
}

void initializeInterfaces()
{
	//TWI_Init(100000/100);
	USART_Init(__UBRR);
}



uint8_t getHumidity()
{
	uint8_t humidity;

	HTU21D_StartHumidity();
	_delay_ms(15);
	humidity = HTU21D_GetHumidity();

	return humidity;
}


int8_t getTemperature()
{
	int8_t temperature_int;
	uint8_t temperature_fract;

	HTU21D_StartTemperature();
	_delay_ms(15);
	HTU21D_GetTemperature(&temperature_int, &temperature_fract);

	return temperature_int;

}

uint16_t getIlluminance()
{
	uint16_t illuminance;

	BH1750_Start(BH1750_OTHR_MODE2);
	_delay_ms(150);
	illuminance = BH1750_Read();

	return illuminance;
}






void configInterrupt()
{

	//Dla 328P
	//EICRA = (1 << ISC01) | (1 << ISC00);	//Zbocze rosnace
	//EIMSK = 1 << INT0;
}


void initializeTimers()
{
	//Dla 8A
	TCCR1B = 1<< WGM12 |			// Tryb CTC
			 1<<CS12   | 1<<CS10;	// Preskaler: 1024


	OCR1A = 7200;
	TIMSK = 1<<OCIE1A;  //Timer/Counter1, Output Compare A Match Interrupt Enable



	//Dla 328P
//	TCCR1B = (1<<WGM12) |
//			 (1<<CS12);  //Preskaler 1024    7372800/1024=7200
//	OCR1A = 7200;
//	TIMSK1 = 1 << OCIE1A;   //Aktywowanie przerwan CTC OCR1A
}



