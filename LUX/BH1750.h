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
  ******************************************************************************
  * @file    BH1750.h
  * @author  Bartlomiej Kusmierczyk
  * @version V1.0
  * @date     11 september 2015
  * @brief   This file contains all the functions prototypes for the ADC firmware
  *          library.?????????????
  *******************************************************************************/
#ifndef BH1750_H_
#define BH1750_H_


#define BH1750_DVI_PIN	PB1
#define BH1750_DVI_PORT	PORTB
//#define BH1750_ADD_PIN	PB2
//#define BH1750_ADD_PORT	PORTB



#define BH1750_W 	((uint8_t)0x46)				//Data write
#define BH1750_R 	((uint8_t)0x47)

#define BH1750_Power_OFF	((uint8_t)0x00)
#define BH1750_Power_ON		((uint8_t)0x01)
#define BH1750_RESET		((uint8_t)0x07)


/** @defgroup ADC_interrupts_definition
  * @{
  */
/* Measurment modes */
#define BH1750_CHR_MODE    0x10		// BH1750 Continuously H-Resolution Mode
#define BH1750_CHR_MODE2   0x11		// Continuously H-Resolution Mode2	(0,5 lx)
#define BH1750_CLR_MODE    0x13		// Continuously L-Resolution Mode
#define BH1750_OTHR_MODE   0x20		// One Time H-Resolution Mode
#define BH1750_OTHR_MODE2  0x21		// One Time H-Resolution Mode2
#define BH1750_OTLR_MODE   0x23		// One Time L-Resolution Mode



/**
  * @Brief  BH1750 measurment mode enumeration
  */
typedef enum
{
	BH1750_Mode_CHR   = 0x10,		// BH1750 Continuously H-Resolution Mode
	BH1750_Mode2_CHR  = 0x11,		// BH1750 Continuously H-Resolution Mode2
	BH1750_Mode_CLR   = 0x13,		// BH1750 Continuously L-Resolution Mode
	BH1750_Mode_OTHR  = 0x20,		// BH1750 One Time H-Resolution Mode
	BH1750_Mode2_OTHR = 0x21,		// BH1750 One Time H-Resolution Mode2
	BH1750_Mode_OTLR  = 0x23		// BH1750 One Time L-Resolution Mode

	/*
	CHR_Mode   = 0x10,		// BH1750 Continuously H-Resolution Mode
	CHR_Mode2  = 0x11,		// BH1750 Continuously H-Resolution Mode2
	CLR_Mode   = 0x13,		// BH1750 Continuously L-Resolution Mode
	OTHR_Mode  = 0x20,		// BH1750 One Time H-Resolution Mode
	OTHR_Mode2 = 0x21,		// BH1750 One Time H-Resolution Mode2
	OTLR_Mode  = 0x23		// BH1750 One Time L-Resolution Mode
	*/

}BH1750Mode_TypeDef;



typedef struct
{
	BH1750Mode_TypeDef Mode;
}BH1750_InitTypeDef;

void BH1750_PowerOn();
void BH1750_PowerDown();
void BH1750_Start(BH1750_InitTypeDef* BH1750_Struct);
uint16_t BH1750_Read(uint8_t mode);
void BH1750_Reset();



#endif /* BH1750_H_ */