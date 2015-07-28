/*
 * main.c
 *
 *  Created on: 19 maj 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD/lcd44780.h"

#define WIRE1 DDRC|=(1<<PC3); PORTC|=(1<<PC3);
#define WIRE0 DDRC|=(1<<PC3); PORTC&=~(1<<PC3);
#define WIRE_IN DDRC&=~(1<<PC3);PORTC|=(1<<PC3);

#define PIN_1WIRE 3
#define PORT_1WIRE PORTC
#define DDR_1WIRE DDRC
#define PIN_READ_1WIRE PINC



#define READ_ROM 0x33
#define SKIP_ROM 0xCC
#define READ_SCR 0xBE
#define CONVERT 0x44
#define WRITE_SCR 0x4E
#define COPY_SCR 0x48
#define MATCH_ROM 0x55
#define SEARCH_ROM 0x55
#define ALARM_SEARCH 0xEC
#define RECALL_E2 0xB8

void Reset();
void SendByte(uint8_t byte);
uint8_t ReadBit();
uint8_t ReadByte();

char buffer[10];

void Reset() {
    char tab[]="Dziala";
    char tab2[]="Nie dziala";

    int i;
    WIRE0;
    _delay_us(500);
    WIRE_IN;
    _delay_us(20);

    for(i=0;i<12;i++) {
        if(bit_is_clear(PIN_READ_1WIRE,PIN_1WIRE)){
            break;
        }
        _delay_us(10);
    }

    if(i<12) {
        lcd_str(tab);
    }
    else {
        lcd_str(tab2);
    }
}


void SendByte(uint8_t byte) {
    /* Send Byte */
    int i;
    for(i=0;i<8;i++) {

        if((byte & 1) == 1) {   //Wysyla 1
            WIRE0;
            _delay_us(2);
            WIRE1;
            _delay_us(58);
        }
        else {                  //Wysyla 0
            WIRE0;
            _delay_us(60);
            WIRE1;
            _delay_us(10);
        }

        byte=(byte>>1);
    }
}

void Measure() {

}

unsigned char ReadBit() {
    unsigned char bit = 0;
    WIRE0;

    _delay_us(2);
    WIRE_IN;
    _delay_us(10);
    if(bit_is_set(PIN_READ_1WIRE,PIN_1WIRE)) {
        bit = 1;
    }
    else {
        bit = 0;
    }

    return bit;
}


unsigned char ReadByte() {
    /* Read Byte */
    int i;
    unsigned char byte = 0;
    for (i=0;i<8;i++) {
        if(ReadBit())
            byte |= 1 << i;
        _delay_us(15);
    }

    return byte;
}

uint16_t MeasureTemp() {
	uint16_t temp = 0;

	Reset();
	SendByte(SKIP_ROM);
	int i;
	SendByte(0x44);
	WIRE_IN;
	Reset();
	SendByte(SKIP_ROM);
	SendByte(0xBE);

	temp = ReadByte();
	temp |= (ReadByte() << 8);
	//for(i=0;i<7;i++)
		//ReadByte();
	return temp;
}


int main(void) {
    lcd_init();
    lcd_cls();

    //Reset();
   // _delay_ms(1000);
    //lcd_cls();


    //sprintf(buffer,"%02x",code);
    //lcd_str(buffer);
   // SendByte(SKIP_ROM);
   // SendByte(SKIP_ROM);

    uint16_t temp = 0;
    while(1) {
    temp = MeasureTemp();
    temp  = temp >> 4;

    lcd_cls();
    sprintf(buffer,"%02d",temp);
    lcd_str(buffer);
    lcd_str("st. C");
    _delay_ms(5000);

    }
   // while(1);
    //if(PINB&(1<<PB1)==0)
    //break;

}
