/*
 * TWI.h
 *
 *  Created on: 26 lip 2015
 *      Author: Bartek
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_START_ERROR 	(0x01)
#define I2C_REP_START_ERROR (0x02)
#define I2C_NACK_ERROR 		(0x05)
#define I2C_ACK_ERROR 		(0x04)

//extern uint8_t TWI_ErrorFlag = 0;

void TWI_SetSpeed(uint16_t speed);
void TWI_Init();
void TWI_Start();
void TWI_RStart();
void TWI_Stop();
void TWI_Send_SLA(uint8_t address);
void TWI_Write(uint8_t byte);
uint8_t TWI_Read_ACK();
uint8_t TWI_Read_NACK();
void TWI_ERROR(uint8_t error);
void TWI_Read(uint8_t buffer[], uint8_t size);
#endif /* TWI_H_ */