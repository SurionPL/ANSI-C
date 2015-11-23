/*
 * main.c
 *
 *  Created on: 12 lis 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "BMP180/BMP180.h"
#include "I2C/I2C.h"
#include "RTC/RTC.h"
#include "MKUART/mkuart.h"
#include "HTU21D/HTU21D.h"
#include "BH1750/BH1750.h"
#include "ESP8266_CL/ESP8266_Cl.h"
#include "main.h"

//volatile uint8_t int1_flag;	/* Flaga zezwolenia na przejscie do pomiarow */
volatile uint8_t int0_flag;	/* Flaga zezwolenia na wyzwolenie pomiarow */

volatile int8_t temperature[5];
volatile uint8_t illuminance[5];
volatile uint8_t humidity[5];
volatile long pressure[5];


void SendToUart(void);
long temp, press;


ISR(INT0_vect)
{
	int0_flag = MEASUREMENTS_TRIGGER_ENABLE;
}


void ExternalInt_Config()
{
	EICRA = (1<<ISC01) | (1<<ISC00);
	EIMSK = 1<<INT0;
}

void InitializeModules()
{
	ESP_Init();
	HTU21D_Init(Humidity10b_Temperature13b);
}


void InterfaceInit()
{
	TWI_Init(100000/100);
	USART_Init(__UBRR);
}


int main() {
	DDRB  = 1<<PB1;
	//PORTB = 1<<PB1;
	PORTB = 0;
	InterfaceInit();

	//BMP180_Init(BMP180_Mode_ST);
                // inicjalizacja BMP180 - pobranie danych calibracyjnych

    sei();  // globalne odblokowanie przerwa�

    // przedstawienie si� uk�adu przez UART po starcie
    uart_puts("************** Dzien Dobry ******************\r\n");


	while(1){
		//BMP180_StartTemp();
		_delay_ms(60);
		temp = BMP180_GetTemp();
		//BMP180_StartPress();
		//_delay_ms(60);
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
        uart_putint(press/100);
        uart_puts(".");
        if (press%100<10) uart_puts("0");
        uart_putint( press%100);
        uart_puts("\r\n");
}
