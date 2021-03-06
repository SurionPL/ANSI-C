/**
  *******************************************************************************
  * @ File    BMP180.h
  * @ Author  Bartlomiej Kusmierczyk
  * @ Version V1.0
  * @ Date    28-July-2015
  * @ Brief   This file contains all the functions prototypes for the BMP180
  * 		  temperature and pressure sensor library.
  *******************************************************************************
  */


#ifndef BMP180_H_
#define BMP180_H_


/** @ Defgroup: BMP180 slave address
  */
#define BMP180_SLA ((uint8_t)0xEE)


/** @ Defgroup: BMP180 registers addresses
  */
#define BMP180_ADC_XLSB_REG ((uint8_t)0xF8)
#define BMP180_ADC_LSB_REG	((uint8_t)0xF7)
#define BMP180_ADC_MSB_REG	((uint8_t)0xF6)

#define BMP180_CTRL_MEAS_REG ((uint8_t)0xF4)
//#define BMP180_SCO_PARAM
#define BMP180_SOFT_RST_REG ((uint8_t)0xE0)
#define BMP180_SOFT_RST_VAL ((uint8_t)0xB6)


/** @ Defgroup: BMP180 slave address
  */
#define BMP180_MEM_START 0xAA


/** @ Defgroup: BMP180 calibration parameters adresses
  */
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


/** @ Defgroup: BMP180 chip ID adresses
  */
#define BMP180_CHIP_ID_REG	((uint8_t)0xD0)		/*  Chip ID register address */
#define BMP180_CHIP_ID		((uint8_t)0x55)


/** @ Defgroup: BMP180 measurement functions
  */
#define BMP180_T_MEASURE	((uint8_t)0x2E)
#define BMP180_P_MEASURE	((uint8_t)0x34)


/** @ Defgroup: BMP180 pressure measurement modes
  * @{
  */
#define BMP180_P_MEASURE_ULP	((uint8_t)0x34)	/* Ultra Low Power mode */
#define BMP180_P_MEASURE_ST		((uint8_t)0x74)	/* Standard mode */
#define BMP180_P_MEASURE_HR		((uint8_t)0xB4)	/* High Resolution mode */
#define BMP180_P_MEASURE_UHR 	((uint8_t)0xF4)	/* Ultra High Resolution mode */


/** @ Defgroup: BMP180 pressure measurement modes enumeration
  * @{
  */
typedef enum
{
  BMP180_Mode_ULP = 0x34,	/* Ultra Low Power mode */
  BMP180_Mode_ST = 	0x74,	/* Standard mode */
  BMP180_Mode_HR = 	0xB4,	/* High Resolution mode */
  BMP180_Mode_UHR = 0xF4	/* Ultra High Resolution mode */
}BMP180Mode_TypeDef;

/**
  * @ Brief:  BMP180 structure definition
  */
typedef struct
{
	BMP180Mode_TypeDef BMP180_Mode;
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2;
	short MB,MC,MD;
	long B5;
	long UT;
	long UP;
}BMP180_TypeDef;


/** @ Defgroup: BMP180 functions
  */
//void BMP180_Init(BMP180_InitTypeDef* BMP180_Struct);
void BMP180_Init(BMP180Mode_TypeDef BMP180_Mode);
void BMP180_StartTemp();
void BMP180_StartPress();
long BMP180_GetTemp();
long BMP180_GetPress();
void BMP180_SendParam();
long BMP180_GetUT();
long BMP180_GetUP();
void BMP180_SendUPUT();


#endif /* BMP180_H_ */
