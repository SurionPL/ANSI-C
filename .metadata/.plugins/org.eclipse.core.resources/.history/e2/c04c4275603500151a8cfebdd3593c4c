/*
 * main.c
 *
 *  Created on: 26 cze 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD/lcd44780.h"
#include "DHT/DHT11.h"

uint8_t temp = 0;
uint8_t hum = 0;

void DisplayResult(uint8_t temp, uint8_t hum) {
	lcd_cls();
	lcd_str(" T:");
	lcd_int(temp);
	lcd_str(" H:");
	lcd_int(hum);
}



int main()
{
lcd_init();
	while(1)
	{

		if (Measure(&temp,&hum) == 0)
			DisplayResult(temp, hum);
			_delay_ms(2000);

	}
}
