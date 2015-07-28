/*
 * I2C.h
 *
 *  Created on: 26 lip 2015
 *      Author: Bartek
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_START_ERROR 0x01
#define I2C_NACK_ERROR 	0x05
#define I2C_ACK_ERROR 	0x04



void I2C_SetSpeed(uint16_t speed);
void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_SendAddr(uint8_t address);
void I2C_SendByte(uint8_t byte);
uint8_t I2C_ReciveData_ACK();
uint8_t I2C_ReciveData_NACK();
void I2C_ERROR(uint8_t error);
#endif /* I2C_H_ */
