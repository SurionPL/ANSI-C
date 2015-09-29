/*
 * BH1750.h

 *
 *  Created on: 11 wrz 2015
 *      Author: Bartek
 *
 *
 *
 *      Pin ADDR conected do GND
 */


/**
  *******************************************************************************
  * @ File    BH1750.h
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    11-September-2015
  * @ Brief   This file contains all the functions prototypes for the BH1750
  * 		  digital ambient light sensor library.
  *******************************************************************************
  */
#ifndef BH1750_H_
#define BH1750_H_


//#define BH1750_DVI_PIN	PB1
//#define BH1750_DVI_PORT	PORTB
//#define BH1750_ADD_PIN	PB2
//#define BH1750_ADD_PORT	PORTB



#define BH1750_SLA 	((uint8_t)0x46)				//Data write


#define BH1750_Power_OFF	((uint8_t)0x00)
#define BH1750_Power_ON		((uint8_t)0x01)
#define BH1750_RESET		((uint8_t)0x07)


/** @ Defgroup: BH1750 measurment modes definition
  */
#define BH1750_CHR_MODE    ((uint8_t)0x10)		// BH1750 Continuously H-Resolution Mode
#define BH1750_CHR_MODE2   ((uint8_t)0x11)		// Continuously H-Resolution Mode2	(0,5 lx)
#define BH1750_CLR_MODE    ((uint8_t)0x13)		// Continuously L-Resolution Mode
#define BH1750_OTHR_MODE   ((uint8_t)0x20)		// One Time H-Resolution Mode
#define BH1750_OTHR_MODE2  ((uint8_t)0x21)		// One Time H-Resolution Mode2
#define BH1750_OTLR_MODE   ((uint8_t)0x23)		// One Time L-Resolution Mode



/**
  * @Brief  BH1750 measurment mode enumeration
  */
/*typedef enum
{
	BH1750_Mode_CHR   = 0x10,		// BH1750 Continuously H-Resolution Mode
	BH1750_Mode2_CHR  = 0x11,		// BH1750 Continuously H-Resolution Mode2
	BH1750_Mode_CLR   = 0x13,		// BH1750 Continuously L-Resolution Mode
	BH1750_Mode_OTHR  = 0x20,		// BH1750 One Time H-Resolution Mode
	BH1750_Mode2_OTHR = 0x21,		// BH1750 One Time H-Resolution Mode2
	BH1750_Mode_OTLR  = 0x23		// BH1750 One Time L-Resolution Mode



}BH1750Mode_TypeDef;*/



//typedef struct
//{
	//BH1750Mode_TypeDef Mode;
//}BH1750_InitTypeDef;



/** @ Defgroup: BH1750 functions
  */
void BH1750_PowerOn();
void BH1750_PowerDown();
void BH1750_Start(uint8_t mode);
uint16_t BH1750_Read();
void BH1750_ResetDR();



#endif /* BH1750_H_ */
