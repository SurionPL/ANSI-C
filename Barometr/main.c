/*
 * main.c
 *
 *  Created on: 24 lip 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "BMP180.h"
#include "I2C.h"
char tab[2] = {'O','K'};

#define MYUBRR FOSC/16/BAUD-1

int main() {
	//BMP180_CalibrationParam bmp ={1,2,3,4,5,6,7,8,9,10,11};
	//uint16_t a=bmp.AC1;

	DDRB = 1<<PB1;
	PORTB = 1<<PB1;
	USART_Init(MYUBRR);
	//twi_Init();
	//twi_Start();
	//twi_Send_SLA(BMP_W);
	while(1){
	}
}
