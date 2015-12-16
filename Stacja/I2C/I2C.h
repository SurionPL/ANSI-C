/*
 *******************************************************************************
 * @ Plik    I2C.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    26 lipca 2015
 * @ Opis    Ten plik zawiera wszystkie funkcje do obslugi interfejsu TWI
 * 			 w mikrokontrolerach AVR.
 *******************************************************************************
 */


#ifndef I2C_H_
#define I2C_H_

/* Wartosci flagi bledu */
typedef enum
{
	I2C_OK = 0,
	I2C_Start_Error,
	I2C_Rep_Start_Error,
	I2C_NACK_Error,
	I2C_ACK_Error,
	I2C_SLA_Error
}I2C_ErrorFlag;


/* Funkcje */
void I2C_Init(uint32_t speed);
void I2C_Start();
void I2C_RStart();
void I2C_Stop();
void I2C_Write_SLA(uint8_t address);
void I2C_WriteByte(uint8_t byte);
uint8_t I2C_ReadByte_ACK();
uint8_t I2C_ReadByte_NACK();
void I2C_WriteBytes(uint8_t SLA, uint8_t address, uint8_t size, uint8_t* buffer);
void I2C_ReadBytes(uint8_t SLA, uint8_t address, uint8_t size, uint8_t* buffer);
I2C_ErrorFlag I2C_CheckErrorFlag();

#endif /* I2C_H_ */
