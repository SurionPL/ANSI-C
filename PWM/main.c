/*
 * main.c
 *
 *  Created on: 21 mar 2015
 *      Author: Bartek
 */
#include <avr/io.h>
#include <util/delay.h>


int main() {
	//DDRB |= (1<<PB1);
	//TCCR1B |= (1<<CS12) | (1<<CS10); //Preskaler 1024
	//TCCR1B |= (1<<WGM13)|(1<<WGM12);
	//TCCR1A |= (1<<WGM11)
	//while(1);

	 int i;

	   // Konfiguracja portów we/wy
	   DDRB = (1<<PB1);

	  /* Ustawienie sprzêtowego PWM */
	   ICR1  = 399;  //8/ICR1
	   OCR1A = 0;
	   OCR1B = 0;

	  // Fast PWM mode (14), patrz str. 89  atmega8 datasheet
	  TCCR1A=(1<<COM1A1)|(1<<WGM11);
	  TCCR1B=(1<<WGM13)|(1<WGM12)|(1<<CS10);

	   while(1) {
		   for(i=0;i<=399;i++) {
			   OCR1A=i;
			   _delay_ms(2);
		   }
		   for(i=399;i>=0;i--) {
			   OCR1A=i;
			   _delay_ms(2);
		   }
	   }
}
