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

/*Results
 * [0] - decimal part
 * [1] - fractional part
*/
unsigned char temperature[2] = {0,0};				// Temperature
unsigned short pressure[2] = {0,0};					// Pressure

static struct BMP180_t BMP180_Parameters;


/*struct Coefficients {
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2;
	short MB,MC,MD;
}*BMP180_param;*/






void bmp180_start(uint8_t mode){    //Zmienic nazwe mode
	twi_Start();
	twi_Send_SLA(BMP180_W);
	twi_Write(BMP180_CTRL_MEAS_REG);
	twi_Write(mode);
	twi_Stop();
}

/*void bmp180_addr_select(uint8_t address){

}*/

void bmp180_read_param(){
	twi_Start();
	twi_Send_SLA(BMP180_W);

}



void bmp180_get_temp(unsigned char temperature[]) {
	uint8_t UT_MSB = 0, UT_LSB = 0;
	uint16_t UT = 0;
	twi_Start();
	twi_Write(BMP180_W);
	twi_Write(BMP180_ADC_MSB_REG);
	twi_RStart();
	twi_Write(BMP180_R);
	UT_MSB = twi_Read_ACK();
	UT_LSB = twi_Read_NACK();
	twi_Stop();

	//Algorithm
	UT = (UT_MSB<<8) | UT_LSB;
	long X1 = ((UT-BMP180_Parameters.AC6)*BMP180_Parameters.AC5)>>15;
	long X2 = (BMP180_Parameters.MC << 11) / (X1 + BMP180_Parameters.MD);
	long B5 = X1 + X2;
	long T= (B5 + 8) >> 4;
	temperature[0] = T/10;
	temperature[1] = T%10;
}
