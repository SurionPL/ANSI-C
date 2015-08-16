/*
 * main.c
 *
 *  Created on: 24 lip 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "USART.h"
#include "BMP180.h"
#include "I2C.h"
char tab[2] = {'O','K'};
uint8_t temperature[2];
int pressure[2];


char buffer[5];
#define MYUBRR FOSC/16/BAUD-1
BMP180_TypeDef bmp180_Struct;

int main() {
	DDRB  = 1<<PB1;
	PORTB = 1<<PB1;

	bmp180_Struct.BMP180_Mode=BMP180_Mode_ST;

	uint8_t temperature[2] = {0,0};
	bmp180_init(&bmp180_Struct);
	USART_Init(MYUBRR);

	//temperature[0] = 0;
	pressure[0] = 0;
	bmp180_start_temp(&bmp180_Struct);
	_delay_ms(20);
	bmp180_get_temp(&bmp180_Struct, temperature);

	//unsigned char ciag[] = " TEMP: ";
	//USART_Send_String(ciag, 6);
	while(1){
		bmp180_start_press(&bmp180_Struct);
		_delay_ms(20);

		bmp180_get_press(&bmp180_Struct, pressure);
		sprintf(buffer,"%u",pressure[0]);
		//USART_Transmit_Int(pressure[0]);

		USART_Send_String(buffer, 5);
		//bmp180_send_param(&bmp180_Struct);
		//USART_Transmit_Int();
		_delay_ms(5000);
	}
}
