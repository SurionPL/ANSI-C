/*
 * ThingSpeak.h
 *
 *  Created on: 23 pa� 2015
 *      Author: Bartek
 */

#ifndef THINGSPEAK_H_
#define THINGSPEAK_H_





//        GET += "&field1=";
     //   https://api.thingspeak.com/update?key=K7D0ZR1M32BLIV5B&field1=0

void TS_UpdateField(char* value, uint8_t field);

#endif /* THINGSPEAK_H_ */
