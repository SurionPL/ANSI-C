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
#include "AVG/AVG.h"
#include "ESP8266_CL/ESP8266_Cl.h"
#include "AuxiliaryLib/AuxiliaryLib.h"
#include "BH1750/BH1750.h"
#include "MKUART/mkuart.h"

#define DISABLE 0x00
#define ENABLE  0x01

#define SIZE 8
#define MASK (SIZE-1)

//volatile uint8_t seconds;
volatile uint8_t minutes;
volatile uint8_t seconds;

volatile uint8_t trigger_flag; /* Flaga zezwolenia na wyzwolenie pomiarow */
volatile uint8_t reset_connection_flag; /* Flaga zezwolenia na restart polaczenia z siecia */
volatile uint8_t selector;

/* Tablice wynikow pomiarow do sredniej kroczacej */
int8_t temperature[SIZE];
uint16_t illuminance[SIZE];
uint8_t humidity[SIZE];
int32_t pressure[SIZE];

/* Usrednione wartosci */
int8_t temperature_avg;
int32_t pressure_avg;
uint16_t illuminance_avg;
uint8_t humidity_avg;

uint8_t cnt;
uint8_t idx;

/*============= Program glowny =============*/
int main() {
	DDRB = 1 << PB1;
	//PORTB = 1 << PB1;
	cnt = 0;
	idx = 0;
	seconds = 0;
	minutes = 1;
	trigger_flag = DISABLE;
	reset_connection_flag = DISABLE;
	initializeInterfaces();
	initializeModules();

	sei();
	initializeTimers();
	//PORTB = 2;
	//uart_puts("Siema to uklad! \r\n");

	/* Poczatkowa seria pomiarow */
	for (uint8_t i = 1; i < SIZE; i++) {
		temperature[i] = getTemperature();
		humidity[i] = getHumidity();
		illuminance[i] = getIlluminance();
		pressure[i] = getPressure();
	}
	//PORTB ^= 1<<PB1;

	//humidity_avg = calcAVG_UINT8(humidity, SIZE);
	//sendHumidity(humidity_avg);

	//temperature_avg = calcAVG_INT8(temperature, SIZE);
	//sendTemperature(temperature_avg);

	//illuminance_avg = calcAVG_UINT16(illuminance, SIZE);
	//sendIlluminance(illuminance_avg);

	//pressure_avg = calcAVG_INT32(pressure, SIZE);
	//sendPressure(pressure_avg);

	/* Nawiazanie lacznosci z siecia */
	ESP_Connect();
	_delay_ms(3000);

	/* Wyslanie wynikow na ThingSpeak */

	/* Nieskonczona petla */
	while (1) {
		if (trigger_flag == ENABLE) {
			selector = cnt & 0x03;
			if (selector == 0) {
				temperature[idx & MASK] = getTemperature();
				temperature_avg = calcAVG_INT8(temperature, SIZE);
				sendTemperature(temperature_avg);
			} else if (selector == 1) {
				humidity[idx & MASK] = getHumidity();
				humidity_avg = calcAVG_UINT8(humidity, SIZE);
				sendHumidity(humidity_avg);
			} else if (selector == 2) {
				illuminance[idx & MASK] = getIlluminance();
				illuminance_avg = calcAVG_UINT16(illuminance, SIZE);
				sendIlluminance(illuminance_avg);
			} else if (selector == 3) {
				pressure[idx & MASK] = getPressure()/100;
				pressure_avg = calcAVG_INT32(pressure, SIZE);
				sendPressure(pressure_avg);
				idx++;
			}

			/* Wykonywanie pomiarow i odczyt wynikow */

			trigger_flag = DISABLE;
			cnt++;
		}

		if (reset_connection_flag == ENABLE) {
			ESP_Disconnect();
			_delay_ms(2000);
			ESP_Connect();
			_delay_ms(3000);
			reset_connection_flag = DISABLE;
		}
	}
}

/* Procedura obslugi przerwanie CTC od Timera 1. */
ISR(TIMER1_COMPA_vect) {
	seconds++;

	if (seconds % 60 == 0) {
		seconds = 0;
		minutes++;
		trigger_flag = ENABLE;
	}
	if (minutes % 10 == 0) {
		minutes = 0;
		reset_connection_flag = ENABLE;
	}
	PORTB ^= 1 << PB1;
}
