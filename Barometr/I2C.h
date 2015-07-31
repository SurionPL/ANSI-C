/*
 * twi.h
 *
 *  Created on: 26 lip 2015
 *      Author: Bartek
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_START_ERROR 0x01
#define I2C_NACK_ERROR 	0x05
#define I2C_ACK_ERROR 	0x04



void twi_set_speed(uint16_t speed);
void twi_init();
void twi_start();
void twi_stop();
void twi_send_SLA(uint8_t address);
void twi_send_byte(uint8_t byte);
uint8_t twi_recive_data_ACK();
uint8_t twi_recive_data_NACK();
void twi_ERROR(uint8_t error);
#endif /* twi_H_ */
