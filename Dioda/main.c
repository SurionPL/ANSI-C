/*
 * main.c
 *
 *  Created on: 27 lis 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initializeTimers()
{

	//Dla 328P
	TCCR1B = (1<<WGM12) |
			 (1<<CS12) | (1<<CS10);  //Preskaler 1024    7372800/1024=7200
	OCR1A = 7200;
	TIMSK1 = 1 << OCIE1A;   //Aktywowanie przerwan CTC OCR1A
}



int main()
{
	DDRB = 1<< PB1;
	PORTB = 2;
	initializeTimers();
	sei();
	while(1) {
		//PORTB ^= 1<<PB1;
		//_delay_ms(2000);
	}
}

ISR(TIMER1_COMPA_vect)
{

//	if (seconds % 60 == 0)
//	{
//		seconds = 0;
//		minutes++;
//		trigger_flag = MEASUREMENTS_TRIGGER_ENABLE;
//	}
//	if (minutes % 5 == 0)
//	{
//		minutes = 0;
//		reset_connection_flag = RESET_CONNECTION_ENABLE;
//
//	}
	PORTB ^= 1<<PB1;
	//seconds++;
}
