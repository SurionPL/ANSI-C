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


void USART_Init(uint16_t ubrr); //++
void USART_Transmit(uint8_t data);  //
void USART_Flush(void);
void USART_TransmitInt(uint16_t data);
uint8_t USART_Receive();
void USART_TransmitString(char* string);

void USART_TransmitData(unsigned char data[], uint16_t size);
#endif /* USART_H_ */
