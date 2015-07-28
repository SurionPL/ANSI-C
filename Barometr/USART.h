/*
 * USART.h
 *
 *  Created on: 4 lut 2015
 *      Author: Bartek
 */

#ifndef USART_H_
#define USART_H_

#define FOSC 4000000// Clock Speed
#define BAUD 9600



void USART_Transmit(unsigned char data);
void USART_Flush(void);
void USART_Init(unsigned int ubrr);
void USART_Transmit_Int(unsigned int data);
uint8_t USART_Receive();
void Send_String(unsigned char data[], unsigned int size);
#endif /* USART_H_ */