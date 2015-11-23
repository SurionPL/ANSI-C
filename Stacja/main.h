/*
 * main.h
 *
 *  Created on: 22 lis 2015
 *      Author: Bartek
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Wartosci dla flagi od przerwania INT0 */
//#define MEASUREMENTS_DISABLE ((uint8_t)0x00)			/* Brak zgody na wejscie w tryb pomiarow */
//#define MEASUREMENTS_ENABLE  ((uint8_t)0x01)			/* Zgoda na wejscie w tryb pomiarow */

/* Wartosci dla flagi od przerwania INT1 */
#define MEASUREMENTS_TRIGGER_DISABLE ((uint8_t)0x00)	/* Brak zgody na wyzwolenie pomiarow */
#define MEASUREMENTS_TRIGGER_ENABLE  ((uint8_t)0x01)	/* Zgodna na wyzwolenie pomiarow */




#endif /* MAIN_H_ */