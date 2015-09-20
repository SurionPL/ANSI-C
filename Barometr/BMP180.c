/*
 * BMP180.c
 *
 *  Created on: 28 lip 2015
 *      Author: Bartek
 */

/**
  *******************************************************************************
  * @ File    BMP180.c
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    28-July-2015
  * @ Brief   This file contains all the BMP180 sensor firmware functions.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "BMP180.h"
//#include "USART.h"
#include "I2C_TWI/i2c_twi.h"


BMP180_TypeDef BMP180_Struct;


/**
  * @ Brief  	 Starts the BMP180 temperature measurement.
  * @ Parameter  None.
  * @ Retval 	 None.
  */
void BMP180_StartTemp()
{
	TWI_Start();
	TWI_Write_SLA(BMP180_W);
	TWI_WriteByte(BMP180_CTRL_MEAS_REG);
	TWI_WriteByte(BMP180_T_MEASURE);
	TWI_Stop();
}


/**
  * @ Brief  	 Starts the BMP180 pressure measurement.
  * 		 	 Needs a single temperature measurement.
  * @ Parameter  None.
  * @ Retval 	 None.
  */
void BMP180_StartPress()
{
	TWI_Start();
	TWI_Write_SLA(BMP180_W);
	TWI_WriteByte(BMP180_CTRL_MEAS_REG);
	TWI_WriteByte(BMP180_Struct.BMP180_Mode);
	TWI_Stop();
}


/**
  * @ Brief  	 Initializes the BMP180 sensor.
  * @ Parameter  BMP180Mode_TypeDef: sensor measurement mode.
  * @ Retval 	 None.
  */
void BMP180_Init(BMP180Mode_TypeDef BMP180_Mode)
{
	BMP180_Struct.BMP180_Mode = BMP180_Mode;

	uint8_t buffer[22];

	TWI_ReadBytes(BMP180_W, BMP180_MEM_START, 22, buffer);

	BMP180_Struct.AC1 = ((short)buffer[0]<<8			| ((short)buffer[1]));			/* AC1 Structeter */
	BMP180_Struct.AC2 = ((short)buffer[2]<<8			| ((short)buffer[3]));			/* AC2 Structeter */
	BMP180_Struct.AC3 = ((short)buffer[4]<<8 			| ((short)buffer[5]));			/* AC3 Structeter */
	BMP180_Struct.AC4 = ((unsigned int)buffer[6]<<8		| ((unsigned int)buffer[7]));	/* AC4 Structeter */
	BMP180_Struct.AC5 = ((unsigned int)buffer[8]<<8 	| ((unsigned int)buffer[9]));	/* AC5 Structeter */
	BMP180_Struct.AC6 = ((unsigned int)buffer[10]<<8 	| ((unsigned int)buffer[11]));	/* AC6 Structeter */
	BMP180_Struct.B1  = ((short)buffer[12]<<8 			| ((short)buffer[13]));			/* B1  Structeter */
	BMP180_Struct.B2  = ((short)buffer[14]<<8 			| ((short)buffer[15]));			/* B2  Structeter */
	BMP180_Struct.MB  = ((short)buffer[16]<<8			| ((short)buffer[17]));			/* MB  Structeter */
	BMP180_Struct.MC  = ((short)buffer[18]<<8 			| ((short)buffer[19]));			/* MC  Structeter */
	BMP180_Struct.MD  = ((short)buffer[20]<<8			| ((short)buffer[21]));			/* MD  Structeter */
}


/**
  * @ Brief  	 Gets the uncompensed temperature from sensor and calculate it to Celsius degrees.
  * @ Parameter  None.
  * @ Retval 	 Temperature in 0.1*C.
  */
long BMP180_GetTemp()
{
	BMP180_Struct.UT = BMP180_GetUT();

	//Algorithm
	BMP180_Struct.B5 = 0;

	long X1 = (((long)BMP180_Struct.UT-(long)(BMP180_Struct.AC6))*(long)(BMP180_Struct.AC5)) >> 15;
	long X2 = ((long)(BMP180_Struct.MC) << 11)/(X1+(long)(BMP180_Struct.MD));
	BMP180_Struct.B5 = X1 + X2;
	long T = (BMP180_Struct.B5 + 8L) >> 4;

	return T;

}


/**
  * @ Brief  	 Gets the uncompensed pressure from sensor and calculate it to Pa (Pascal) units.
  * @ Parameter  None.
  * @ Retval 	 Pressure in Pa.
  */
long BMP180_GetPress()
{
	uint8_t OSS = ((BMP180_Struct.BMP180_Mode) & 0xC0) >> 6;  // ? czy uint8_t
	BMP180_Struct.UP = BMP180_GetUP();
	long P = 0;

	/* Pressure algorithm */

	long B6 = BMP180_Struct.B5 - 4000L;
	long X1 = (((long)BMP180_Struct.B2)*((B6*B6) >> 12)) >> 11;
	long X2 = (((long)BMP180_Struct.AC2)*B6) >> 11;
	long X3 = X1 + X2;
	long B3 = ((((((long)BMP180_Struct.AC1) << 2) + X3) << OSS) + 2L) >> 2;
	X1 = ((long)(BMP180_Struct.AC3)*B6) >> 13;
	X2 = (((long)BMP180_Struct.B1)*((B6*B6) >> 12)) >> 16;
	X3 = ((X1 + X2) + 2L) >> 2;
	unsigned long B4 = (((long)BMP180_Struct.AC4) * ((unsigned long)(X3 + 32768UL))) >> 15;
	unsigned long B7 = (((unsigned long)BMP180_Struct.UP) - B3) * (50000UL >> OSS);

	if (B7 < 0x80000000)
	{
		P = ((B7 << 1) / B4);
	}
	else
	{
		P = ((B7 / B4) << 1);  // <<1   == *2
	}

	X1 = (((P >> 8) * (P >> 8)) * 3038) >> 16;

	X2 = (-7357 * P) >> 16;
	P = P + ((X1 + X2 + 3791) >> 4);

	return P;
}

void BMP180_SendParam()
{
	/*USART_Transmit_Int(BMP180_Struct->BMP180_Struct.AC1);
	unsigned char sp[] = " ";
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.AC2);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.AC3);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.AC4);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.AC5);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.AC6);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.B1);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.B2);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.MB);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.MC);
	USART_Send_String(sp,1);
	USART_Transmit_Int(BMP180_Struct->BMP180_Struct.MD);
	USART_Send_String(sp,1);*/
	/*USART_TransmitInt(BMP180_Struct.AC1);
	char sp[] = " ";
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.AC2);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.AC3);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.AC4);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.AC5);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.AC6);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.B1);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.B2);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.MB);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.MC);
	USART_TransmitString(sp,1);
	USART_TransmitInt(BMP180_Struct.MD);
	USART_TransmitString(sp,1);*/
}


/**
  * @ Brief  	 Gets the uncompensed temperature value (UT) from sensor.
  * @ Parameter  None.
  * @ Retval 	 Uncompensated temperature value (UP).
  */
long BMP180_GetUT()
{
	long UT = 0;
	uint8_t buffer[2];
	TWI_ReadBytes(BMP180_W, BMP180_ADC_MSB_REG, 2, buffer);
	BMP180_Struct.UT = 0;
	BMP180_Struct.UT = (((long)buffer[0]) << 8) | ((long)buffer[1]);
	return UT;
}



/**
  * @ Brief  	 Gets the uncompensed pressure value (UP) from sensor.
  * @ Parameter  None.
  * @ Retval 	 None
  */
long BMP180_GetUP()
{
	long UP = 0;
	//uint8_t UP_MSB  = 0;
	//uint8_t UP_LSB  = 0;
	//uint8_t UP_XLSB = 0;
	uint8_t OSS = ((BMP180_Struct.BMP180_Mode) & 0xC0) >> 6;  // ? czy uint8_t
	uint8_t buffer[3];
	TWI_ReadBytes(BMP180_W, BMP180_ADC_MSB_REG, 3, buffer);
	//TWI_Start();
	//TWI_Write_SLA(BMP180_W);
	//TWI_WriteByte(BMP180_ADC_MSB_REG);
	//TWI_RStart();
	//TWI_Write_SLA(BMP180_R);
	//UP_MSB = TWI_ReadByte_ACK();
	//UP_LSB = TWI_ReadByte_ACK();
	//UP_XLSB = TWI_ReadByte_NACK();
	//TWI_Stop();				/// +++++++++
	//UP = ((((long)UP_MSB) << 16) | (((long)UP_LSB) << 8) | (((long)UP_XLSB))) >> (8U - OSS);
	UP = ((((long)buffer[0]) << 16) | (((long)buffer[1]) << 8) | (((long)buffer[2]))) >> (8 - OSS);
	return UP;
}


void BMP180_SendUPUT()
{
	//char buffer[10] = {0,0,0,0,0,0,0,0,0,0};
	//sprintf(buffer,"UT %d\n",BMP180_Struct.UT);
	//char tab[1]= "\n";
	//USART_TransmitString(buffer, 10);
	//USART_TransmitString(tab, 1);
	//sprintf(buffer,"UP %d\n",BMP180_Struct.UP);
	//USART_TransmitString(buffer, 10);


}
