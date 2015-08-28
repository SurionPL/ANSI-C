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
#include "USART.h"

/*Results
 * [0] - decimal part
 * [1] - fractional part
*/


//long UT;
//long UP;
//long B5;


//BMP180_TypeDef BMP180_Struct;

//static BMP180_ParametersTypDef BMP180_Parameterseters;			//Parameterseter structure


void bmp180_start_temp(BMP180_TypeDef* BMP180_Struct)				//Zmienic nazwe mode
{
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_CTRL_MEAS_REG);
	TWI_Write(BMP180_T_MEASURE);
	TWI_Stop();
}

void bmp180_start_press(BMP180_TypeDef* BMP180_Struct)
{
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_CTRL_MEAS_REG);
	TWI_Write(BMP180_Struct->BMP180_Mode);
	TWI_Stop();
}

void bmp180_FillStruct(BMP180_TypeDef* BMP180_Struct, uint8_t buffer[])
{
	BMP180_Struct->BMP180_Parameters.AC1 = (short)((buffer[0]<<8) 			| buffer[1]);			/*AC1 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.AC2 = (short)((buffer[2]<<8) 			| buffer[3]);			/*AC2 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.AC3 = (short)((buffer[4]<<8) 			| buffer[5]);			/*AC3 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.AC4 = (unsigned short)((buffer[6]<<8) 	| buffer[7]);			/*AC4 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.AC5 = (unsigned short)((buffer[8]<<8) 	| buffer[9]);			/*AC5 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.AC6 = (unsigned short)((buffer[10]<<8) | buffer[11]);			/*AC6 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.B1  = (short)((buffer[12]<<8) 			| buffer[13]);			/* B1 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.B2  = (short)((buffer[14]<<8) 			| buffer[15]);			/* B2 Parameterseter*/
	BMP180_Struct->BMP180_Parameters.MB  = (short)((buffer[16]<<8)			| buffer[17]);			/* MB Parameterseter*/
	BMP180_Struct->BMP180_Parameters.MC  = (short)((buffer[18]<<8) 			| buffer[19]);			/* MC Parameterseter*/
	BMP180_Struct->BMP180_Parameters.MD  = (short)((buffer[20]<<8) 			| buffer[21]);			/* MD Parameterseter*/
}


void bmp180_read_param(BMP180_TypeDef* BMP180_Struct)
{
	uint8_t buffer[22];
	for(uint8_t i = 0; i<22; i++) {
		buffer[i] = 0;
	}
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_AC1_MSB);
	TWI_RStart();
	TWI_Send_SLA(BMP180_R);
	TWI_Read(buffer,22);
	//TWI_Stop();
	bmp180_FillStruct(BMP180_Struct, buffer);
}



void bmp180_get_temp(BMP180_TypeDef* BMP180_Struct, uint8_t temperature[])
{
	uint8_t UT_MSB = 0, UT_LSB = 0;
	BMP180_Struct->UT = 0;
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_ADC_MSB_REG);
	TWI_RStart();
	TWI_Send_SLA(BMP180_R);
	UT_MSB = TWI_Read_ACK();
	UT_LSB = TWI_Read_NACK();
	TWI_Stop();

	//Algorithm
	BMP180_Struct->B5 = 0;
	BMP180_Struct->UT = (((long)UT_MSB)<<8) | ((long)UT_LSB);
	long X1 = (((long)(BMP180_Struct->UT)-(long)(BMP180_Struct->BMP180_Parameters.AC6))*(long)(BMP180_Struct->BMP180_Parameters.AC5))>>15;
	long X2 = ((long)(BMP180_Struct->BMP180_Parameters.MC) << 11)/(X1+(long)(BMP180_Struct->BMP180_Parameters.MD));
	BMP180_Struct->B5 = X1 + X2;
	long T = ((BMP180_Struct->B5) + 8) >> 4;
	temperature[0] = (uint8_t)(T/10);
	temperature[1] = (uint8_t)(T%10);
}

void bmp180_get_press(BMP180_TypeDef* BMP180_Struct, int pressure[])
{
	uint8_t UP_MSB  = 0;
	uint8_t UP_LSB  = 0;
	uint8_t UP_XLSB = 0;
	uint8_t OSS = (BMP180_Struct->BMP180_Mode) & 0xC0;
	long P = 0;
	BMP180_Struct->UP = 0;
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(BMP180_ADC_MSB_REG);
	TWI_RStart();
	TWI_Send_SLA(BMP180_R);
	UP_MSB = TWI_Read_ACK();
	UP_LSB = TWI_Read_ACK();
	UP_XLSB = TWI_Read_NACK();
	TWI_Stop();
	(BMP180_Struct->UP) = ((((long)UP_MSB)<<16) | (((long)UP_LSB)<<8) | (((long)UP_XLSB))) >> (8-OSS);

	/*Pressure algorithm*/

	long B6 = (BMP180_Struct->B5)-400;
	long X1 = (((long)(BMP180_Struct->BMP180_Parameters.B2))*((B6*B6)>>12))>>11;
	long X2 = ((long)(BMP180_Struct->BMP180_Parameters.AC2)*B6)>>11;
	long X3 = X1 + X2;
	long B3 = ((((((long)(BMP180_Struct->BMP180_Parameters.AC1))<<2)+X3)<<OSS)+2)>>2;
	X1 = ((long)(BMP180_Struct->BMP180_Parameters.AC3)*B6) >> 13;
	X2 = (((long)(BMP180_Struct->BMP180_Parameters.B1))*((B6*B6) >> 12))>>16;
	X3 = ((X1 + X2) + 2) >> 2;
	unsigned long B4 = ((long)(BMP180_Struct->BMP180_Parameters.AC4) * (unsigned long)(X3 + 32768)) >> 15;
	unsigned long B7 = ((unsigned long)(BMP180_Struct->UP)-B3)*(50000 >> OSS);

	if (B7 < 0x80000000)
	{
		P = (B7 << 1) / B4;
	}
	else
	{
		P = (B7 / B4) << 1;  // <<1   == *2
	}
	X1 = (((P >> 8)*(P >> 8))*3038) >> 16;
	X2 = (-7357L * P) >> 16;
	P = (P + X1 + X2 + 3791) >> 4;

	pressure[0] = (int)P;
	//pressure[1] = (uint16_t)(P % 100);
}



void bmp180_init(BMP180_TypeDef* BMP180_Struct)
{
	TWI_Init();
	bmp180_read_param(BMP180_Struct);
}


void bmp180_send_param(BMP180_TypeDef* BMP180_Struct)
{
	USART_Transmit_Int(BMP180_Struct->BMP180_Parameters.AC1);
	unsigned char sp[] = " ";
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Parameters.AC2);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Parameters.AC3);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Parameters.AC4);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Parameters.AC5);
		USART_Send_String(sp,1);

}

uint16_t bmp180_read_register(uint8_t address)
{
	TWI_Start();
	TWI_Send_SLA(BMP180_W);
	TWI_Write(address);
	TWI_RStart();
	TWI_Send_SLA(BMP180_R);
	return 0;
}
