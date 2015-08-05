/*
 * BMP180.h
 *
 *  Created on: 28 lip 2015
 *      Author: Bartek
 */

#ifndef BMP180_H_
#define BMP180_H_

#define BMP180_W (0xEE)	//BMP180 Slave Address Write
#define BMP180_R (0xEF)	//BMP180 Slave Address Read






/*!
 *	@brief this function used for read the calibration
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

#define BMP180_ADC_XLSB_REG 0xF8
#define BMP180_ADC_LSB_REG	0xF7
#define BMP180_ADC_MSB_REG	0xF6

#define BMP180_CTRL_MEAS_REG 0xF4
//#define BMP180_SCO_PARAM
#define BMP180_SOFT_RST_REG 0xE0
#define BMP180_SOFT_RST_VAL 0xB6
/*BMP180 Calibration Parameters Addresses*/  //Poprawic nazwe

#define BMP180_MEM_START 0xAA

#define BMP180_AC1_MSB	0xAA
#define BMP180_AC1_LSB	0xAB
#define BMP180_AC2_MSB	0xAC
#define BMP180_AC2_LSB	0xAD
#define BMP180_AC3_MSB	0xAE
#define BMP180_AC3_LSB	0xAF
#define BMP180_AC4_MSB	0xB0
#define BMP180_AC4_LSB	0xB1
#define BMP180_AC5_MSB	0xB2
#define BMP180_AC5_LSB	0xB3
#define BMP180_AC6_MSB	0xB4
#define BMP180_AC6_LSB	0xB5
#define BMP180_B1_MSB	0xB6
#define BMP180_B1_LSB	0xB7
#define BMP180_B2_MSB	0xB8
#define BMP180_B2_LSB	0xB9
#define BMP180_MB_MSB	0xBA
#define BMP180_MB_LSB	0xBB
#define BMP180_MC_MSB	0xBC
#define BMP180_MC_LB	0xBD
#define BMP180_MD_MSB	0xBE
#define BMP180_MD_LSB	0xBF

#define BMP180_CHIP_ID_REG	0xD0
#define BMP180_CHIP_ID		0x55


/* Temperature measurement */
#define BMP180_T_MEASURE	(0x2E)

/*Presure Measurement Modes*/
#define BMP180_P_MEASURE_ULP	(0x34)	// Ultra Low Power mode
#define BMP180_P_MEASURE_ST		(0x74)	// Standard mode
#define BMP180_P_MEASURE_HR		(0xB4)	// High Resolution mode
#define BMP180_P_MEASURE_UHR 	(0xF4)	// Ultra High Resolution mode

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

typedef struct BMP180_t
{
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2;
	short MB,MC,MD;
};




void bmp180_start(uint8_t mode);
//void bmp180_addr_select(uint8_t address);
void bmp180_read_param();
void bmp180_get_temp(unsigned char* T);


#endif /* BMP180_H_ */
