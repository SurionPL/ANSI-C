/**
 *******************************************************************************
 * @ Plik    BMP180.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    28 lipca 2015
 * @ Opis    Ten plik zawiera wszystkie prototypy funkcji do obslugi czujnika
 * 		     cisnienia BMP180.
 *******************************************************************************
 */

#ifndef BMP180_H_
#define BMP180_H_

#define BMP180_SLA ((uint8_t)0xEE) 				/* Adres slave ukladu */

/* Adresy rejestrow czujnika */
#define BMP180_ADC_XLSB_REG  ((uint8_t)0xF8)
#define BMP180_ADC_LSB_REG	 ((uint8_t)0xF7)
#define BMP180_ADC_MSB_REG	 ((uint8_t)0xF6)
#define BMP180_CTRL_MEAS_REG ((uint8_t)0xF4)
#define BMP180_SOFT_RST_REG  ((uint8_t)0xE0)
#define BMP180_SOFT_RST_VAL  ((uint8_t)0xB6)

/* Poczatek pamieci czujnika */
#define BMP180_MEM_START 0xAA

/* Adresy parametrów kalibracyjnych */
#define BMP180_AC1_MSB	((uint8_t)0xAA)			/* Parametr AC1 - adres MSB */
#define BMP180_AC1_LSB	((uint8_t)0xAB)			/* Parametr AC1 - adres LSB */
#define BMP180_AC2_MSB	((uint8_t)0xAC)			/* Parametr AC2 - adres MSB */
#define BMP180_AC2_LSB	((uint8_t)0xAD)			/* Parametr AC2 - adres LSB */
#define BMP180_AC3_MSB	((uint8_t)0xAE)			/* Parametr AC3 - adres MSB */
#define BMP180_AC3_LSB	((uint8_t)0xAF)			/* Parametr AC3 - adres LSB */
#define BMP180_AC4_MSB	((uint8_t)0xB0)			/* Parametr AC4 - adres MSB */
#define BMP180_AC4_LSB	((uint8_t)0xB1)			/* Parametr AC4 - adres LSB */
#define BMP180_AC5_MSB	((uint8_t)0xB2)			/* Parametr AC5 - adres MSB */
#define BMP180_AC5_LSB	((uint8_t)0xB3)			/* Parametr AC5 - adres LSB */
#define BMP180_AC6_MSB	((uint8_t)0xB4)			/* Parametr AC6 - adres MSB */
#define BMP180_AC6_LSB	((uint8_t)0xB5)			/* Parametr AC5 - adres LSB */
#define BMP180_B1_MSB	((uint8_t)0xB6)			/* Parametr B1  - adres MSB */
#define BMP180_B1_LSB	((uint8_t)0xB7)			/* Parametr B1  - adres LSB */
#define BMP180_B2_MSB	((uint8_t)0xB8)			/* Parametr B2  - adres MSB */
#define BMP180_B2_LSB	((uint8_t)0xB9)			/* Parametr B2  - adres LSB */
#define BMP180_MB_MSB	((uint8_t)0xBA)			/* Parametr MB  - adres MSB */
#define BMP180_MB_LSB	((uint8_t)0xBB)			/* Parametr MB  - adres LSB */
#define BMP180_MC_MSB	((uint8_t)0xBC)			/* Parametr MC  - adres MSB */
#define BMP180_MC_LSB	((uint8_t)0xBD)			/* Parametr MC  - adres LSB */
#define BMP180_MD_MSB	((uint8_t)0xBE)			/* Parametr MD  - adres MSB */
#define BMP180_MD_LSB	((uint8_t)0xBF)			/* Parametr MD  - adres LSB */

/* Wartosci trybow pomiaru */
#define BMP180_T_MEASURE	((uint8_t)0x2E)		/* Pomiar temperatury */
#define BMP180_P_MEASURE	((uint8_t)0x34)		/* Pomiar cisnienia   */

/* Tryby pomiaru cisnienia */
#define BMP180_P_MEASURE_ULP	((uint8_t)0x34)	/* Tryb Ultra Low Power  */
#define BMP180_P_MEASURE_ST		((uint8_t)0x74)	/* Tryb Standard 		 */
#define BMP180_P_MEASURE_HR		((uint8_t)0xB4)	/* Tryb High Resolution  */
#define BMP180_P_MEASURE_UHR 	((uint8_t)0xF4)	/* Ultra High Resolution */

/* Tryby pomiaru cisnienia */
typedef enum {
	BMP180_Mode_ULP = 0x34, /* Tryb Ultra Low Power */
	BMP180_Mode_ST = 0x74,  /* Tryb Standard */
	BMP180_Mode_HR = 0xB4,  /* Tryb High Resolution */
	BMP180_Mode_UHR = 0xF4  /* Tryb Ultra High Resolution */
} BMP180Mode_TypeDef;

/* Struktura BMP180 z danymi konfiguracyjnymi */
typedef struct {
	BMP180Mode_TypeDef BMP180_Mode;
	short AC1, AC2, AC3;
	unsigned short AC4, AC5, AC6;
	short B1, B2;
	short MB, MC, MD;
	long B5;
	long UT;
	long UP;
} BMP180_TypeDef;

/* Funkcje BMP180 */
void BMP180_Init(BMP180Mode_TypeDef BMP180_Mode);
void BMP180_StartTemperature();
void BMP180_StartPressure();
int32_t BMP180_GetTemperature();
int32_t BMP180_GetPressure();

#endif /* BMP180_H_ */
