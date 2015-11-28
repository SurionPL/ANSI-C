/*
 * main.c
 *
 *  Created on: 12 lis 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "I2C/I2C.h"
#include "main.h"
#include "AVG/AVG.h"
#include "ESP8266_CL/ESP8266_Cl.h"
#include "AuxiliaryLib/AuxiliaryLib.h"

#define SIZE 8
#define MASK (SIZE-1)

volatile uint8_t seconds;
volatile uint8_t minutes;

volatile uint8_t trigger_flag;				/* Flaga zezwolenia na wyzwolenie pomiarow */
volatile uint8_t reset_connection_flag;		/* Flaga zezwolenia na restart polaczenia z siecia */

/* Tablice wynikow pomiarow do sredniej kroczacej */
int8_t   temperature[SIZE];
uint16_t illuminance[SIZE];
uint8_t  humidity[SIZE];
int32_t  pressure[SIZE];

/* Usrednione wartosci */
int8_t  temperature_avg;
int32_t pressure_avg;
uint16_t illuminance_avg;
uint8_t humidity_avg;

uint8_t index;

int main() {
	DDRB  = 1 << PB1;
	PORTB = 1 << PB1;
	index = 0;
	seconds = 0;

	initializeInterfaces();
	initializeModules();
	configInterrupt();
	initializeTimers();

	/* Poczatkowa seria pomiarow */
	for (uint8_t i = 0; i < SIZE; i++)
	{
		illuminance[i] = getIlluminance();
		temperature[i] = getTemperature();
		humidity[i]    = getHumidity();
	}

	/* Obliczanie sredniej */
	humidity_avg = calcAVG_UINT8(humidity, SIZE);
	temperature_avg = calcAVG_INT8(temperature, SIZE);
	illuminance_avg = calcAVG_UINT16(illuminance, SIZE);

    sei();  // globalne odblokowanie przerwa�

    /* Nawiazanie lacznosci z siecia */
	ESP_Connect();
	_delay_ms(3000);

	/* Wyslanie wynikow na ThingSpeak */
	sendTemperature(temperature_avg);
	sendHumidity(humidity_avg);
	sendIlluminance(illuminance_avg);

	/* Nieskonczona petla */
	while (1) {
		PORTB ^= 1<<PB1;
		//_delay_ms(2000);

		if (trigger_flag == MEASUREMENTS_TRIGGER_ENABLE)
		{
			/* Wykonywanie pomiarow i odczyt wynikow*/
			illuminance[index & MASK] = getIlluminance();
			temperature[index & MASK] = getTemperature();
			humidity[index & MASK]    = getHumidity();

			/* Obliczanie sredniej */
			humidity_avg = calcAVG_UINT8(humidity, SIZE);
			temperature_avg = calcAVG_INT8(temperature, SIZE);
			illuminance_avg = calcAVG_UINT16(illuminance, SIZE);


			trigger_flag = MEASUREMENTS_TRIGGER_DISABLE;
			index++;
		}

		if (minutes % 5 == 0)
		{
			ESP_Disconnect();
			_delay_ms(2000);
			ESP_Connect();
			_delay_ms(3000);
		}
	}
}


/* Procedura obslugi przerwanie CTC od Timera 1. */
ISR(TIMER1_COMPA_vect)
{

	if (seconds % 60 == 0)
	{
		seconds = 0;
		minutes++;
		trigger_flag = MEASUREMENTS_TRIGGER_ENABLE;
	}
	if (minutes % 5 == 0)
	{
		minutes = 0;
		reset_connection_flag = RESET_CONNECTION_ENABLE;

	}
	PORTB ^= 1<<PB1;
	seconds++;
}
