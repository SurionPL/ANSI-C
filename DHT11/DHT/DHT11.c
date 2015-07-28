/*=================================================
 * Obs³uga czujnika DHT11
 *
 *  Pliki: 				DHT11.h, DHT11.c
 *  Mikrokontrolery: 	Atmel AVR
 *  Data: 				czerwiec 2015
 *  Autor: 				Bartlomiej Kusmierczyk
 *  ================================================
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DHT11.h"
#include "../LCD/lcd44780.h"
#include <stdio.h>
#include <string.h>


uint8_t Measure(uint8_t* temp, uint8_t* hum) {
		uint8_t data[5] = {0,0,0,0,0};

		//reset port
		WIRE1;
		_delay_ms(100);

		//send request
		WIRE0;
		_delay_ms(18);
		WIRE_IN;
		_delay_us(40);

		//check start condition 1

		if (bit_is_set(DHT_IN,DHT_PIN))
			return DHT_TIMEOUT_ERROR;

		_delay_us(80);
		//check start condition 2
		if (bit_is_clear(DHT_IN,DHT_PIN))
			return DHT_TIMEOUT_ERROR;

		_delay_us(80);
		uint8_t result;

		//read the data
		for (uint8_t i=0; i<5; i++) {
			result = 0;
			for (uint8_t j=7; j>=0 && j<8; j--) {
				while (bit_is_clear(DHT_IN,DHT_PIN));
				_delay_us(30);
				if (bit_is_set(DHT_IN,DHT_PIN))
					result |= (1<<j);
				while (bit_is_set(DHT_IN,DHT_PIN));
			}
			data[i] = result;
		}

		//reset port
		WIRE1;
		//DHT_DDR |= (1<<DHT_PIN); //output
		//DHT_OUT |= (1<<DHT_PIN); //low
		//_delay_ms(100);

		//check checksum
		if (data[0] + data[1] + data[2] + data[3] == data[4]) {

				*temp=(data[2]);
				*hum=(data[0]);
				return DHT_OK;
		}


		return DHT_SUM_ERROR;
}


uint8_t Reset() {
    //char tab[]="Dziala";
    //char tab2[]="Nie dziala";

    WIRE0;
    _delay_ms(20);
    WIRE_IN;
    _delay_us(50);

    uint8_t i;

    for (i = 0; i < 5; i++) {
        if (bit_is_clear(DHT_IN,DHT_PIN))
            break;
        _delay_us(10);
    }

    if (i < 5) {
        return DHT_OK;
    }
    else {
        return DHT_TIMEOUT_ERROR;
    }
}









