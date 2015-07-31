/*
 * BMP180.c
 *
 *  Created on: 28 lip 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "BMP180.h"

struct Coefficients {
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2;
	short MB,MC,MD;
}*BMP180_param;



void bmp180_start(){
	twi_start();
	twi_send_SLA(BMP180_W);


}
void bmp180_addr_select(uint8_t address){

}

void bmp180_read_param(){
	twi_start();
	twi_send_SLA(BMP180_W);

}
