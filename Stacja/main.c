/*
 * main.c
 *
 *  Created on: 12 lis 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BMP180/BMP180.h"
#include "I2C/I2C.h"
#include "RTC/RTC.h"
#include "MKUART/mkuart.h"
#include "HTU21D/HTU21D.h"
#include "BH1750/BH1750.h"
#include <stdio.h>


void SendToUart(void);
long temp, press;
//#define MYUBRR FOSC/16/BAUD-1
//BMP180_InitTypeDef bmp180_structure;

ISR(INT1_vect)
{

}



void InterfaceInit()
{
	//TWI_InitTypeDef TWI_InitStruct;
	//TWI_InitStruct.TWI_Speed = 100000/100;
	TWI_Init(100000/100);
	USART_Init(__UBRR);

}


int main() {
	DDRB  = 1<<PB1;
	//PORTB = 1<<PB1;
	PORTB = 0;
	InterfaceInit();
	temp = 0;
	press = 0;
	//bmp180_init.BMP180_Mode = 0x74;
	BMP180_Init(BMP180_Mode_ST);
    //BMP180_Init(&bmp180_structure);                  // inicjalizacja BMP180 - pobranie danych calibracyjnych

    sei();  // globalne odblokowanie przerwa�

    // przedstawienie si� uk�adu przez UART po starcie
    uart_puts("************** Dzien Dobry ******************\r\n");


	//unsigned char ciag[] = " TEMP: ";
	//USART_Send_String(ciag, 6);
	while(1){
		BMP180_StartTemp();
		_delay_ms(60);
		temp = BMP180_GetTemp();
		BMP180_StartPress();
		_delay_ms(60);
		press = BMP180_GetPress();
		SendToUart();
		_delay_ms(5000);
	}
}

void SendToUart(void){
        //uart_puts("************** T ******************\r\n");
        uart_puts("Temperatura:");
        uart_putint( temp/10);
        uart_puts(".");
        uart_putint( temp%10);
        uart_puts(" \t");
        //uart_puts("************** P ******************\r\n");
        uart_puts(" Cisnienie:");
        uart_putint( press/100);
        uart_puts(".");
        if (press%100<10) uart_puts("0");
        uart_putint( press%100);
        uart_puts("\r\n");
}
