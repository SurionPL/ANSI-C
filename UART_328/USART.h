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

#define UART_RX_BUF_SIZE 32
#define UART_RX_MASK (UART_RX_BUF_SIZE - 1)
#define UART_TX_BUF_SIZE 16
#define UART_TX_MASK (UART_TX_BUF_SIZE - 1)




void UART_Init(uint16_t ubrr); //++
void UART_Transmit(uint8_t data);  //
void UART_Flush(void);
void UART_TransmitInt(uint16_t data);
uint8_t UART_ReceiveByte();
void UART_TransmitString(char data[], uint16_t size);
void UART_TransmitData(unsigned char data[], uint16_t size);
#endif /* USART_H_ */
