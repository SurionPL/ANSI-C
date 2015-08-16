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
uint8_t temperature[2] = {0,0};				// Temperature
uint16_t pressure[2] = {0,0};					// Pressure
long UT=0, UP=0, B5=0;

static BMP180_ParamTypDef BMP180_Parameters;			//Parameter structure


/*struct Coefficients {
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2;
	short MB,MC,MD;
}*BMP180_param;*/

void bmp180_start(uint8_t mode) {    //Zmienic nazwe mode
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_CTRL_MEAS_REG);
	TWI_Write(mode);
	TWI_Stop();
}

/*void bmp180_addr_select(uint8_t address){

}*/

void bmp180_FillStruct(BMP180_ParamTypDef* Bmp180_Param, uint8_t buffer[]) {
	Bmp180_Param->AC1 = (short)((buffer[0]<<8) | buffer[1]);
	Bmp180_Param->AC2 = (short)((buffer[2]<<8) | buffer[3]);
	Bmp180_Param->AC3 = (short)((buffer[4]<<8) | buffer[5]);
	Bmp180_Param->AC4 = (unsigned short)((buffer[6]<<8) | buffer[7]);
	Bmp180_Param->AC5 = (unsigned short)((buffer[8]<<8) | buffer[9]);
	Bmp180_Param->AC6 = (unsigned short)((buffer[10]<<8) | buffer[11]);
	Bmp180_Param->B1  = (short)((buffer[12]<<8) | buffer[13]);
	Bmp180_Param->B2  = (short)((buffer[14]<<8) | buffer[15]);
	Bmp180_Param->MB  = (short)((buffer[16]<<8) | buffer[17]);
	Bmp180_Param->MC  = (short)((buffer[18]<<8) | buffer[19]);
	Bmp180_Param->MD  = (short)((buffer[20]<<8) | buffer[21]);

}


void bmp180_read_param()
{
	uint8_t buffer[22];
	for(uint8_t i = 0; i<22; i++) {
		buffer[i]=0;
	}
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_AC1_MSB);
	TWI_RStart();
	TWI_Read(buffer,22);
	TWI_Stop();
	bmp180_FillStruct(&BMP180_Parameters, buffer);
}



void bmp180_get_temp(BMP180_InitTypeDef* BMP180_Init, unsigned char temperature[])
{
	uint8_t UT_MSB = 0, UT_LSB = 0;
	UT = 0;
	TWI_Start();
	TWI_Write(BMP180_W);
	TWI_Write(BMP180_ADC_MSB_REG);
	TWI_RStart();
	TWI_Write(BMP180_R);
	UT_MSB = TWI_Read_ACK();
	UT_LSB = TWI_Read_NACK();
	TWI_Stop();

	//Algorithm
	B5=0;
	UT = (UT_MSB<<8) | UT_LSB;
	long X1 = ((UT-BMP180_Parameters.AC6)*BMP180_Parameters.AC5)>>15;
	long X2 = (BMP180_Parameters.MC << 11) / (X1 + BMP180_Parameters.MD);
	B5 = X1 + X2;
	long T= (B5 + 8) >> 4;
	temperature[0] = T/10;
	temperature[1] = T%10;
}

void bmp180_get_press(BMP180_InitTypeDef* BMP180_Init, unsigned char pressure[])
{
	//Dodac XLSB w if
	uint8_t UP_MSB = 0, UP_LSB = 0;
	UP = 0;
	TWI_Start();
	TWI_Write(BMP180_W);
	TWI_Write(BMP180_ADC_MSB_REG);
	TWI_RStart();
	TWI_Write(BMP180_R);
	UP_MSB = TWI_Read_ACK();
	UP_LSB = TWI_Read_NACK();
	TWI_Stop();


	/*Pressure algorithm*/
	long P = 0;
	uint8_t OSS = (BMP180_Init->BMP180_Mode) & 0xC0;
	long B6 = B5-400;
	long X1 = ((BMP180_Parameters.B2)*((B6*B6)>>12))>>11;
	long X2 = (BMP180_Parameters.AC2*B6)>>11;
	long X3 = X1+X2;
	long B3 = ((((BMP180_Parameters.AC1<<2)+X3)<<OSS)+2)>>2;
	X1 = (BMP180_Parameters.AC3*B6) >> 13;
	X2 = (BMP180_Parameters.B1*((B6*B6) >> 12))>>16;
	X3 = ((X1+X2)+2) >>2;
	unsigned long B4 = (BMP180_Parameters.AC4 * (unsigned long)(X3+32768)) >> 15;
	unsigned long B7 = ((unsigned long)UP-B3)*(50000>>OSS);
	if(B7<0x80000000)
	{
		P = (B7*2)/B4;
	}
	else
	{
		P = (B7/B4)<<1;  // <<1   == *2
	}
	X1 = (((P>>8)*(P>>8))*3038)>>16;
	X2 = (-7357*P)>>16;
	P = (P+X1+X2+3791)>>4;
	pressure[0] = P/100;
	pressure[1] = P%100;
}



void bmp180_init()
{
	bmp180_read_param();
}



/*void bmp180_press2alt(unsigned short* pressure) {
	uint16_t = 101325; //In Pa

}*/
