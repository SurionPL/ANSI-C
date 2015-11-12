/*
 * ThingSpeak.h
 *
 *  Created on: 23 pa� 2015
 *      Author: Bartek
 */

#ifndef THINGSPEAK_H_
#define THINGSPEAK_H_


char TS_IP[] = "144.212.80.11";
char TS_GET = "GET /update?key=";
char TS_APIKey[]="K7D0ZR1M32BLIV5B";

//        GET += "&field1=";
     //   https://api.thingspeak.com/update?key=K7D0ZR1M32BLIV5B&field1=0
void TS_UpdateTemperature();
void TS_UpdateHumidity();
void TS_UpdatePressure();
void TS_UpdateData();
#endif /* THINGSPEAK_H_ */
