/*=================================================
 * Obs³uga czujnika DHT11
 *
 *  Pliki: 				DHT11.h, DHT11.c
 *  Mikrokontrolery: 	Atmel AVR
 *  Data: 				czerwiec 2015
 *  Autor: 				Bartlomiej Kusmierczyk
 *  ================================================
 */

#ifndef DHT11_DHT11_H_
#define DHT11_DHT11_H_

#define DHT_TIMEOUT_ERROR 	0x01
#define DHT_SUM_ERROR 		0x02
#define DHT_OK 				0

#define DHT_PIN  PB0
#define DHT_IN   PINB
#define DHT_OUT  PORTB
#define DHT_DDR  DDRB


#define WIRE1 	 DHT_DDR|=(1<<DHT_PIN); 	DHT_OUT|=(1<<DHT_PIN);
#define WIRE0	 DHT_DDR|=(1<<DHT_PIN); 	DHT_OUT&=~(1<<DHT_PIN);
#define WIRE_IN  DHT_DDR&=~(1<<DHT_PIN); 	DHT_OUT|=(1<<DHT_PIN);


uint8_t Reset();
uint8_t Measure(uint8_t* temp, uint8_t* hum);

#endif /* DHT11_DHT11_H_ */
