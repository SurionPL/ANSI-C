/*
 * main.c
 *
 *  Created on: 27 lis 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
int main() {
DDRB = 1<< PB1;
PORTB = 2;
while(1){
	PORTB ^= 1<<PB1;
	_delay_ms(2000);



}
}
