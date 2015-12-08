/**
 *******************************************************************************
 * @ Plik    AuxiliaryLib.c
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    20 listopada 2015
 * @ Opis    Ten plik zawiera funkcje do inicjalziacji modulow, wyzwalania
 * 			 pomiarow, pobierania wynikow, inicjalizacji timerow i interfejsow
 * 			 komunikacyjnych oraz wysylania danych na serwer ThingSpeak.
 *******************************************************************************
 */

/*-------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "../AVG/AVG.h"
#include "../ThingSpeak/ThingSpeak.h"
#include "../MKUART/mkuart.h"
#include "../HTU21D/HTU21D.h"
#include "../BH1750/BH1750.h"
#include "../ESP8266_CL/ESP8266_Cl.h"
#include "../BMP180/BMP180.h"
#include "../I2C/I2C.h"
/*-------------------------------------------------------------------*/

void initializeModules() {
	ESP_Init();
	//PORTB = 2;
	HTU21D_Init(Humidity11b_Temperature11b);
	BMP180_Init(BMP180_Mode_ST);

}

void sendTemperature(int8_t temperature) {
	char value[7];
	sprintf(value, "%d", temperature);
	TS_UpdateField(value, 1);
}

void sendHumidity(uint8_t humidity) {
	char value[7];
	sprintf(value, "%d", humidity);
	TS_UpdateField(value, 2);
}

void sendIlluminance(uint16_t illuminance) {
	char value[7];
	sprintf(value, "%d", illuminance);
	TS_UpdateField(value, 3);
}

void sendPressure(int32_t pressure) {
	char value[7];
	sprintf(value, "%d", (int) pressure);
	TS_UpdateField(value, 4);
}

void initializeInterfaces() {
	I2C_Init(100000);
	USART_Init(__UBRR);
	//PORTB = 1 << PB1;
}

int8_t getTemperature() {
	int8_t temperature_int;
	uint8_t temperature_fract;

	HTU21D_StartTemperature();
	_delay_ms(20);
	HTU21D_GetTemperature(&temperature_int, &temperature_fract);

	return temperature_int;

}

uint8_t getHumidity() {
	uint8_t humidity;

	HTU21D_StartHumidity();
	_delay_ms(20);
	humidity = HTU21D_GetHumidity();

	return humidity;
}

uint16_t getIlluminance() {
	uint16_t illuminance;

	BH1750_Start(BH1750_OTHR_MODE);
	_delay_ms(150);
	illuminance = BH1750_Read();

	return illuminance;
}

int32_t getPressure() {
	int32_t pressure;

	BMP180_StartPressure();
	_delay_ms(30);
	pressure = BMP180_GetPressure();

	return pressure;
}

void initializeTimers() {
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); //Preskaler 1024
	OCR1A = 3600;
	TIMSK1 = 1 << OCIE1A;   //Aktywowanie przerwan CTC OCR1A
}

