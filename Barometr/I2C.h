/*
 * twi.h
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



void twi_SetSpeed(uint16_t speed);
void twi_Init();
void twi_Start();
void twi_RStart();
void twi_Stop();
void twi_Send_SLA(uint8_t address);
void twi_Write(uint8_t byte);
uint8_t twi_Read_ACK();
uint8_t twi_Read_NACK();
void twi_ERROR(uint8_t error);
#endif /* twi_H_ */
