/*
 * twi.c
 *
 *  Created on: 26 lip 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include "I2C.h"
#include "USART.h"

char table[2] = {'O','K'};
char table2[2] = {'N','O'};

void twi_set_speed(uint16_t speed)
{
	speed=(4000000/speed/100-16)/2;
	uint8_t prescaler = 0;
	while(speed>255) {
		prescaler++;
		speed/=4;
	}
	TWSR = (TWSR & ((1<<TWPS1) | (1<<TWPS0))) | prescaler;
	TWBR = speed;
}

void twi_init()
{
	TWCR = (1<<TWEA) | (1<<TWEN);
	twi_set_speed(100000/100);
}

void twi_start()  //Dodac zwracanie statusu wszedzie!
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	//Wait for TWINT Flag set. This	indicates that the START condition
	//has been transmitted
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_START)
	twi_ERROR(I2C_START_ERROR);

}

void twi_stop()
{
	//Send Stop bit
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void twi_send_SLA(uint8_t address)
{
	uint8_t status;
	if((address & 0x01) == 0) status = TW_MT_SLA_ACK;
	else status = TW_MR_SLA_ACK;
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT))); //Czekaj na zakonczenie
	if (TW_STATUS != status){
		twi_ERROR(I2C_ACK_ERROR); //NACK error
		//Send_String(table2,2);
	}
}


void twi_send_byte(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if(TW_STATUS != TW_MT_DATA_ACK)
		twi_ERROR(I2C_NACK_ERROR);
}

uint8_t twi_recive_data_NACK()
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if(TW_STATUS != TW_MR_DATA_ACK) twi_ERROR(I2C_NACK_ERROR);
	return TWDR;
}

uint8_t twi_recive_data_ACK()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	if(TW_STATUS != TW_MR_DATA_ACK) twi_ERROR(I2C_NACK_ERROR);
	return TWDR;
}


void twi_ERROR(uint8_t error)
{
	//Wypelnic czyms do interfejsu z uzytkownikiem
}
