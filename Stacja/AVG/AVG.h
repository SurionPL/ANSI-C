/**
 *******************************************************************************
 * @ Plik    AVG.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    20 listopada 2015
 * @ Opis    Ten plik zawiera wszystkie prototypy funkcji potrzebne do
 * 			 obliczania sredniej.
 *******************************************************************************
 */


#ifndef AVG_AVG_H_
#define AVG_AVG_H_

/* Funkcje */
int32_t calcAVG_INT32(int32_t* array, uint8_t size);

int8_t calcAVG_INT8(int8_t* array, uint8_t size);

uint8_t calcAVG_UINT8(uint8_t* array, uint8_t size);

uint8_t calcAVG_UINT16(uint16_t* array, uint8_t size);


#endif /* AVG_AVG_H_ */
