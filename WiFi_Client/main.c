/*
 * main.c
 *
 *  Created on: 28 sie 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "ESP8266_Cl.h"
#include <avr/interrupt.h>
int main()
{
	DDRB = 2;
	PORTB=2;

	sei();

	while(1){}
}
