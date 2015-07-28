/*
 * main.c
 *
 *  Created on: 23 sty 2015
 *      Author: Bartek
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd44780.h"
volatile uint16_t wynik;
volatile uint32_t i=5;

/*ISR(ADC_vect)
{
	if(i%5==0)
	{
		PORTB^=(1<<PB1);
		wynik=(ADCH<<8)|ADCL;
		i=0;
	}


	i++;
	ADCSRA |= 1<<ADSC;
	//ADCSRA&=~(1<<ADIF);
}
*/
int main()
{
	DDRC&=~(1<<PC5); //Input
	DDRB |=(1<<PB1);
	lcd_init();
	/*TCNT0=0;
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02);		//preskaler = 256
	OCR0A = 10;*/						//podzial przez 10

	/*ADMUX |= (1<<REFS1)|(1<<REFS0)|(1<<MUX2)|(1<<MUX0); //1,1V REF || Chan ADC5
	ADCSRB|=(1<<ADTS1)|(1<<ADTS0); //Trigger: Timer0 CpMA
	ADCSRA |= (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC Enable | Start Conv ||| Prescaler 128
	*/
	//ADMUX |= (1<<REFS1)|(1<<REFS0)|(1<<MUX2)|(1<<MUX0); //1,1V REF || Chan ADC5
	//ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC Enable | Start Conv ||| Prescaler 128
	//ADCSRA |= 1<<ADSC; //ADC On

	ADMUX |=(3<<6)|(5<<0);
	ADCSRA |=(1<<7)|(6<<0);
	ADCSRA |= 1<<ADSC; //Start Meas

	//sei();
	while(1)
	{
		while(ADCSRA &(1<<ADSC));
		wynik=(ADCH<<8)|ADCL;
		lcd_locate(0,0);
		lcd_int(wynik);
		_delay_ms(500);
		ADCSRA |= 1<<ADSC; //Start Meas
	}

}

