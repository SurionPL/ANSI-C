/*
 * AuxiliaryLib.h
 *
 *  Created on: 28 lis 2015
 *      Author: Bartek
 */

#ifndef AUXILIARYLIB_AUXILIARYLIB_H_
#define AUXILIARYLIB_AUXILIARYLIB_H_

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
void configInterrupt();
void initializeTimers();

#endif /* AUXILIARYLIB_AUXILIARYLIB_H_ */
