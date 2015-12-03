/*
 *******************************************************************************
 * @ Plik    I2C.c
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    26 lipca 2015
 * @ Opis    Ten plik zawiera wszystkie funkcje do obslugi interfejsu TWI
 * 			 w mikrokontrolerach AVR.
 *******************************************************************************
 */


#ifndef I2C_H_
#define I2C_H_

#define I2C_START_ERROR 	(0x01)
#define I2C_REP_START_ERROR (0x02)
#define I2C_NACK_ERROR 		(0x05)
#define I2C_ACK_ERROR 		(0x04)

//extern uint8_t TWI_ErrorFlag = 0;

void TWI_Init(uint16_t speed);
//void TWI_Init(TWI_InitTypeDef* TWI_InitStruct);
void TWI_Start();
void TWI_RStart();
void TWI_Stop();
void TWI_Write_SLA(uint8_t address);
void TWI_WriteByte(uint8_t byte);
uint8_t TWI_ReadByte_ACK();
uint8_t TWI_ReadByte_NACK();
void TWI_WriteBytes(uint8_t SLA, uint8_t address, uint8_t size, uint8_t* buffer);
void TWI_ReadBytes(uint8_t SLA, uint8_t address, uint8_t size, uint8_t* buffer);
void TWI_ERROR(uint8_t error);

#endif /* TWI_H_ */
