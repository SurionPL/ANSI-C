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

#define DISABLE 0x00	/* Aktywacja   */
#define ENABLE  0x01	/* Deaktywacja */

#define LED_ON 	DDRB = (1<<PB1); PORTB = (1<<PB1)	/* Zapalanie diody */

#define SIZE 4								/* Rozmiar buforow przechowujacych wyniki */
#define MASK (SIZE-1)						/* Maska bufora cyrkulacyjnego */

volatile uint8_t seconds; 					/* Licznik sekund */
volatile uint8_t minutes; 					/* Licznik minut */

volatile uint8_t trigger_flag; 				/* Flaga zezwolenia na wyzwolenie pomiarow */
volatile uint8_t reset_connection_flag; 	/* Flaga zezwolenia na restart polaczenia z siecia */
volatile uint8_t selector; 					/* Selektor */

/* Bufory wynikow pomiarow do sredniej kroczacej */
int8_t temperature[SIZE];
uint16_t illuminance[SIZE];
uint8_t humidity[SIZE];
int32_t pressure[SIZE];

/* Usrednione wartosci pomiarow*/
int8_t temperature_avg;
int32_t pressure_avg;
uint16_t illuminance_avg;
uint8_t humidity_avg;

uint8_t cnt; /* Licznik */
uint8_t idx; /* Indeks */

/*============= Program glowny =============*/
int main() {
	LED_ON
	;
	cnt = 0;
	idx = 0;
	seconds = 0;
	minutes = 1;
	trigger_flag = ENABLE;
	reset_connection_flag = DISABLE;

	/* Inicjalizacja interfejsow komunikacyjnych i modulow */
	initializeInterfaces();
	initializeModules();

	sei();
	/* Konfiguracja timera 1. w trybie CTC */
	initializeTimers();

	/* Poczatkowa seria pomiarow */
	for (uint8_t i = 1; i < SIZE; i++) {
		temperature[i] = getTemperature();
		humidity[i] = getHumidity();
		illuminance[i] = getIlluminance();
		pressure[i] = getPressure();
	}

	/* Nawiazanie lacznosci z siecia */
	ESP_Connect();
	_delay_ms(3000);

	/* Nieskonczona petla */
	while (1) {
		if (trigger_flag == ENABLE) {
			selector = cnt & 0x03;

			/* Wybor parametru do zmierzenia i wyslania na ThingSpeak*/
			if (selector == 0) {
				temperature[idx & MASK] = getTemperature();
				temperature_avg = calcAVG_INT8(temperature, SIZE);
				sendTemperature(temperature_avg);
			} else if (selector == 1) {
				humidity[idx & MASK] = getHumidity();
				humidity_avg = calcAVG_UINT8(humidity, SIZE);			// Wilgotnosc w %
				sendHumidity(humidity_avg);
			} else if (selector == 2) {
				illuminance[idx & MASK] = getIlluminance();
				illuminance_avg = calcAVG_UINT16(illuminance, SIZE);	// Natezenie osw. w luksach
				sendIlluminance(illuminance_avg);
			} else if (selector == 3) {
				pressure[idx & MASK] = getPressure();
				pressure_avg = calcAVG_INT32(pressure, SIZE) / 100;		// Cisnienie w hPa
				sendPressure(pressure_avg);
				idx++;
			}

			trigger_flag = DISABLE; 	/* Wyzerowanie flagi */
			cnt++; 						/* Inkrementacja licznika cnt */
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

/* Procedura obslugi przerwania CTC od Timera 1. */
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
