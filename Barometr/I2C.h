/*
 * TWI.h
 *
 *  Created on: 26 lip 2015
 *      Author: Bartek
 */

#ifndef I2C_H_
#define I2C_H_

#define TWI_START_ERROR 	(0x01)
#define TWI_REP_START_ERROR (0x02)
#define TWI_NACK_ERROR 		(0x05)
#define TWI_ACK_ERROR 		(0x04)

//extern uint8_t TWI_ErrorFlag = 0;

/*typedef struct
{
	uint16_t TWI_Speed;
}TWI_InitTypeDef;*/



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
