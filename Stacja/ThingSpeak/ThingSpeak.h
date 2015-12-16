/**
 *******************************************************************************
 * @ Plik    ThingSpeak.h
 * @ Autor   Bartlomiej Kusmierczyk
 * @ Wersja  V1.0
 * @ Data    10 listopada 2015
 * @ Opis    Plik zawiera definicje funkcji do uaktualniania pola kana³u na
 * 			 ThingSpeak.com
 *******************************************************************************
 */
#ifndef THINGSPEAK_H_
#define THINGSPEAK_H_

/* Funkcje ThingSpeak */
void TS_UpdateField(char* value, uint8_t field);

#endif /* THINGSPEAK_H_ */
