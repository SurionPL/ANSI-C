/*
 * main.c
 *
 *  Created on: 2 wrz 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
//#include "I2C.h"
#include "BH1750.h"

int main() {
	BH1750_Read();
while(1){} 
}
