/*
 * BMP180.h
 *
 *  Created on: 28 lip 2015
 *      Author: Bartek
 */


/**
  ******************************************************************************
  * @ File    BMP180.h
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    28-July-2015
  * @ Brief   This file contains all the functions prototypes for the BMP180
  * 		  temperature and pressure sensor library.
  ******************************************************************************
  */


#ifndef BMP180_H_
#define BMP180_H_


/** @defgroup BMP180 slave address
  * @{
  */
#define BMP180_W ((uint8_t)0xEE)	//BMP180 Slave Address Write
#define BMP180_R ((uint8_t)0xEF)	//BMP180 Slave Address Read

/*
 *	@Brief this function used for read the calibration
 *	parameter from the register
 *
 *	Parameter  |  MSB    |  LSB    |  bit
 * ------------|---------|---------|-----------
 *		AC1    |  0xAA   | 0xAB    | 0 to 7
 *		AC2    |  0xAC   | 0xAD    | 0 to 7
 *		AC3    |  0xAE   | 0xAF    | 0 to 7
 *		AC4    |  0xB0   | 0xB1    | 0 to 7
 *		AC5    |  0xB2   | 0xB3    | 0 to 7
 *		AC6    |  0xB4   | 0xB5    | 0 to 7
 *		B1     |  0xB6   | 0xB7    | 0 to 7
 *		B2     |  0xB8   | 0xB9    | 0 to 7
 *		MB     |  0xBA   | 0xBB    | 0 to 7
 *		MC     |  0xBC   | 0xBD    | 0 to 7
 *		MD     |  0xBE   | 0xBF    | 0 to 7
 *
 *
 *	@return results of bus communication function
 *	@retval 0  -> Success
 *	@retval -1 -> Error
 *
 *
*/

/** @ Defgroup: BMP180 registers addresses
  * @{
  */
#define BMP180_ADC_XLSB_REG ((uint8_t)0xF8)
#define BMP180_ADC_LSB_REG	((uint8_t)0xF7)
#define BMP180_ADC_MSB_REG	((uint8_t)0xF6)

#define BMP180_CTRL_MEAS_REG ((uint8_t)0xF4)
//#define BMP180_SCO_PARAM
#define BMP180_SOFT_RST_REG ((uint8_t)0xE0)
#define BMP180_SOFT_RST_VAL ((uint8_t)0xB6)
/*BMP180 Calibration Parameters Addresses*/  //Poprawic nazwe



/** @ Defgroup: BMP180 slave address
  * @{
  */
#define BMP180_MEM_START 0xAA

#define BMP180_AC1_MSB	((uint8_t)0xAA)			/* AC1 parameter MSB address */
#define BMP180_AC1_LSB	((uint8_t)0xAB)			/* AC1 parameter LSB address */
#define BMP180_AC2_MSB	((uint8_t)0xAC)			/* AC2 parameter MSB address */
#define BMP180_AC2_LSB	((uint8_t)0xAD)			/* AC2 parameter LSB address */
#define BMP180_AC3_MSB	((uint8_t)0xAE)			/* AC3 parameter MSB address */
#define BMP180_AC3_LSB	((uint8_t)0xAF)			/* AC3 parameter LSB address */
#define BMP180_AC4_MSB	((uint8_t)0xB0)			/* AC4 parameter MSB address */
#define BMP180_AC4_LSB	((uint8_t)0xB1)			/* AC4 parameter LSB address */
#define BMP180_AC5_MSB	((uint8_t)0xB2)			/* AC5 parameter MSB address */
#define BMP180_AC5_LSB	((uint8_t)0xB3)			/* AC5 parameter LSB address */
#define BMP180_AC6_MSB	((uint8_t)0xB4)			/* AC6 parameter MSB address */
#define BMP180_AC6_LSB	((uint8_t)0xB5)			/* AC5 parameter LSB address */
#define BMP180_B1_MSB	((uint8_t)0xB6)			/*  B1 parameter MSB address */
#define BMP180_B1_LSB	((uint8_t)0xB7)			/*  B1 parameter LSB address */
#define BMP180_B2_MSB	((uint8_t)0xB8)			/*  B2 parameter MSB address */
#define BMP180_B2_LSB	((uint8_t)0xB9)			/*  B2 parameter LSB address */
#define BMP180_MB_MSB	((uint8_t)0xBA)			/*  MB parameter MSB address */
#define BMP180_MB_LSB	((uint8_t)0xBB)			/*  MB parameter LSB address */
#define BMP180_MC_MSB	((uint8_t)0xBC)			/*  MC parameter MSB address */
#define BMP180_MC_LSB	((uint8_t)0xBD)			/*  MC parameter LSB address */
#define BMP180_MD_MSB	((uint8_t)0xBE)			/*  MD parameter MSB address */
#define BMP180_MD_LSB	((uint8_t)0xBF)			/*  MD parameter LSB address */

#define BMP180_CHIP_ID_REG	((uint8_t)0xD0)		/*  Chip ID register address */
#define BMP180_CHIP_ID		((uint8_t)0x55)


/* Temperature measurement */
#define BMP180_T_MEASURE	((uint8_t)0x2E)
#define BMP180_P_MEASURE	((uint8_t)0x34)

/*Presure Measurement Modes*/
//#define BMP180_P_MEASURE_ULP	(0x34)	// Ultra Low Power mode
//#define BMP180_P_MEASURE_ST		(0x74)	// Standard mode
//#define BMP180_P_MEASURE_HR		(0xB4)	// High Resolution mode
//#define BMP180_P_MEASURE_UHR 	(0xF4)	// Ultra High Resolution mode

/*
 * struct bmp180_t {
	struct bmp180_calib_param_t calib_param;    //<calibration data
	u8 mode;<power mode
	u8 chip_id; <chip id
	u8 ml_version;<ml version
	u8 al_version;<al version
	u8 dev_addr;<device address
	u8 sensortype;< sensor type

	s32 param_b5;<pram
	s32 number_of_samples;<sample calculation
	s16 oversamp_setting;<oversampling setting
	s16 sw_oversamp;<software oversampling

	BMP180_WR_FUNC_PTR;< bus write function pointer
	BMP180_RD_FUNC_PTR;< bus read function pointer
	void (*delay_msec)(BMP180_MDELAY_DATA_TYPE);< delay function pointer
};


*/


typedef enum
{
  BMP180_Mode_ULP = 0x34,	/* Ultra Low Power mode */
  BMP180_Mode_ST = 	0x74,	/* Standard mode */
  BMP180_Mode_HR = 	0xB4,	/* High Resolution mode */
  BMP180_Mode_UHR = 0xF4	/* Ultra High Resolution mode */
}BMP180Mode_TypeDef;


/**
  * @ Brief:  BMP180 Parameters structure definition
  */
typedef struct
{
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2;
	short MB,MC,MD;
}BMP180_ParamTypDef;


/**
  * @ Brief:  BMP180 Init structure definition
  */
typedef struct
{
	BMP180Mode_TypeDef BMP180_Mode;
}BMP180_InitTypeDef;


/**
  * @ Brief:  BMP180 structure definition
  */
typedef struct
{
	BMP180_ParamTypDef BMP180_Parameters;
	//BMP180_InitTypeDef BMP180_Init;
	BMP180Mode_TypeDef BMP180_Mode;
	long UT;
	long UP;
	long B5;
}BMP180_TypeDef;


void BMP180_Init(BMP180_TypeDef* BMP180_Struct);
void BMP180_StartTemp(BMP180_TypeDef* BMP180_Struct);
void BMP180_StartPress(BMP180_TypeDef* BMP180_Struct);
void BMP180_FillStruct(BMP180_TypeDef* BMP180_Struct, uint8_t buffer[]);
//void bmp180_addr_select(uint8_t address);
void BMP180_ReadPram(BMP180_TypeDef* BMP180_Struct);
void BMP180_GetTemp(BMP180_TypeDef* BMP180_Struct, uint8_t temperature[]);
void BMP180_GetPress(BMP180_TypeDef* BMP180_Struct, int pressure[]);
void BMP180_SendParam(BMP180_TypeDef* BMP180_Struct);
uint16_t BMP180_ReadRegister(uint8_t address);


#endif /* BMP180_H_ */
