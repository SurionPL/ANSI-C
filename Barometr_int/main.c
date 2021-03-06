/*
 * main.c
 *
 *  Created on: 18 wrz 2015
 *      Author: Bartek
 */

/*
 * main.c
 *
 *  Created on: 25 kwi 2014
 *  Autor: �ukasz �uczko
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//#include "LCD/lcd44780.h"
#include "I2C_TWI/i2c_twi.h"
#include "MKUART/mkuart.h"

#include "BMP180.h"

#define LED             (1<<PB1)                        // Pod�wietlenie wy�wietlacza
#define LED_DIR         DDRB
#define LED_PORT        PORTB
#define LED_PIN         PINB
#define LED_OFF         LED_PORT &= ~LED
#define LED_ON          LED_PORT |= LED
#define LED_TOG         LED_PORT ^= LED


//void ShowOnLCD(void);           // Wswietla na LCD
void SendToUart(void);          // Wysy�a do RS

long temp, press;

int main(void) {
        //lcd_init();
        //lcd_cls();
        //lcd_str("start...");
        // pod�wietlenie LCD
        LED_DIR |= LED; // kierunek WYJ�CIE
        LED_ON;                 // domy�lnie w��czenie pod�wietlenia
        USART_Init(__UBRR);             // inicjalizacja UART
        i2cSetBitrate(100);             // inicjalizacja I2C
        BMP180_init();                  // inicjalizacja BMP180 - pobranie danych calibracyjnych

        sei();  // globalne odblokowanie przerwa�

        // przedstawienie si� uk�adu przez UART po starcie
        uart_puts("************** Dzien Dobry ******************\r\n");

        while(1){
                temp = BMP180_gett();
                press = BMP180_getp();
                //ShowOnLCD();
                SendToUart();
                _delay_ms(500);
        }
}
/*void ShowOnLCD(void){
        lcd_locate(0,0);
        lcd_str("Temp: ");
        lcd_int(temp/10);
        lcd_str(".");
        lcd_int(temp%10);
        lcd_str("   ");
        lcd_locate(1,0);
        lcd_str("Cisn: ");
        lcd_int(press/100);
        lcd_str(".");
        if (press%100<10) lcd_str("0");
        lcd_int(press%100);
        lcd_str("   ");

}*/
void SendToUart(void){
        //uart_puts("************** T ******************\r\n");
        uart_puts("Temperatura:");
        uart_putint( temp/10, 10 );
        uart_puts(".");
        uart_putint( temp%10, 10 );
        uart_puts(" \t");
        //uart_puts("************** P ******************\r\n");
        uart_puts(" Cisnienie:");
        uart_putint( press/100, 10 );
        uart_puts(".");
        if (press%100<10) uart_puts("0");
        uart_putint( press%100, 10 );
        uart_puts("\r\n");
}
