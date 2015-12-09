/**
 *******************************************************************************
 * @ Plik    AVG.c
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    20 listopada 2015
 * @ Opis    Ten plik zawiera wszystkie funkcje do obliczanie sredniej.
 *******************************************************************************
 */

#include <avr/io.h>





int32_t calcAVG_INT32(int32_t* array, uint8_t size)
{
	int32_t sum = 0;

	for (uint8_t i = 0; i < size; i++)
			sum += array[i];

	return ((int32_t)(sum / size));
}


int8_t calcAVG_INT8(int8_t* array, uint8_t size)
{
	int32_t sum = 0;

	for (uint8_t i = 0; i < size; i++)
			sum += array[i];

	return ((int8_t)(sum / size));
}


uint8_t calcAVG_UINT8(uint8_t* array, uint8_t size)
{
	uint32_t sum = 0;

	for (uint8_t i = 0; i < size; i++)
		sum += array[i];

	return ((uint8_t)(sum / size));
}


uint8_t calcAVG_UINT16(uint16_t* array, uint8_t size)
{
	uint32_t sum = 0;

	for (uint8_t i = 0; i < size; i++)
		sum += array[i];

	return ((uint16_t)(sum / size));
}
