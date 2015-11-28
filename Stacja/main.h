/*
 * main.h
 *
 *  Created on: 22 lis 2015
 *      Author: Bartek
 */

#ifndef MAIN_H_
#define MAIN_H_



/* Wartości flag */
#define MEASUREMENTS_TRIGGER_DISABLE ((uint8_t)0x00)	/* Brak zgody na wyzwolenie pomiarow */
#define MEASUREMENTS_TRIGGER_ENABLE  ((uint8_t)0x01)	/* Zgodna na wyzwolenie pomiarow */

#define RESET_CONNECTION_DISABLE ((uint8_t)0x00)	/* Brak zgody na reset połączenia z routerem */
#define RESET_CONNECTION_ENABLE  ((uint8_t)0x01)	/* Zgodna na reset połączenia z routerem */

#endif /* MAIN_H_ */
