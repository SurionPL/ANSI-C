/**
 *******************************************************************************
 * @ Plik    AuxiliaryLib.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    20 listopada 2015
 * @ Opis    Ten plik zawiera prototypy funkcji do inicjalziacji modulow,
 * 			 wyzwalania pomiarow, pobierania wynikow, inicjalizacji timerow
 * 			 i interfejsow komunikacyjnych oraz wysylania danych na serwer
 * 			 ThingSpeak.
 *******************************************************************************
 */

#ifndef AUXILIARYLIB_AUXILIARYLIB_H_
#define AUXILIARYLIB_AUXILIARYLIB_H_

/* Funkcje */
void initializeModules();
void sendTemperature(int8_t temperature);
void sendHumidity(uint8_t humidity);
void sendPressure(int32_t pressure);
void sendIlluminance(uint16_t illuminance);
void initializeInterfaces();
uint8_t getHumidity();
int8_t getTemperature();
uint16_t getIlluminance();
int32_t getPressure();
void initializeTimers();

#endif /* AUXILIARYLIB_AUXILIARYLIB_H_ */
