/*
 * main.c
 *
 *  Created on: 6 cze 2015
 *      Author: Bartek
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile uint8_t _BUTTON = 0;

ISR(INT0_vect) {							// PROCEDURA OBSLUGI PRZERWANIA INT0
	_BUTTON ^= 1;
}

ISR(TIMER0_COMPA_vect) { 					// PROCEDURA OBSLUGI PRZERWANIA COMPARE MATCH
	if (_BUTTON == 1) {
		PORTB ^= (1<<PB0);
	}
	else {
		PORTB &= ~(1<<PB0);
	}
}

int main() {

	DDRB	= (1<<PB0) | (1<<PB1);
	PORTB	= (1<<PB1);

	//INT0
	EICRA	= (1<<ISC01);					// OPADAJACE ZBOCZE
	EIMSK	= (1<<INT0);					// WLACZENIE PRZERWAN OD INT0

	//Timer0 Interrupt
	TCCR0A |= (1<<WGM01) | (1<<WGM00);  	// TRYB CTC
	TCCR0B	= (1<<CS02)  | (1<<CS00);  		// PRESKALER 1024
	OCR0A	= 255;							// DODATKOWY DZIELNIK
	TIMSK0	= (1<<OCIE0A);					// WLACZENIE PRZERWAN COMPARE MATCH

	// PWM
	TCCR1A	= (1<<COM1A1) | (1<<WGM10);		// FAST PWM 8-BIT
	TCCR1B	= (1<<WGM12)  | (1<<CS10);		// FAST PWM 8-BIT | PRESKALER - 1
	OCR1A	= 0;

	sei();									// GLOBALNE WLACZENIE PRZERWAN
	uint8_t i;

	while (1) {
			for (i=0; i<255; i++) {
				OCR1A = i;
				_delay_ms(4);
			}
			for (i=255; i>0; i--) {
				OCR1A = i;
				_delay_ms(4);
			}
	}
}

