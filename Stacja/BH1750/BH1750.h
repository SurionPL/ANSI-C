/**
  *******************************************************************************
  * @ Plik    BH1750.h
  * @ Autor   Bartlomiej Kusmierczyk
  * @ Wersja  V1.0
  * @ Data    11 wrzesnia 2015
  * @ Opis    Ten plik zawiera wszystkie prototypy funkcji do sterowania
  * 		  czujnikiem natezenie oswietlenia BH1750. Pin ADDR musi byc
  * 		  podlaczony do GND.
  *******************************************************************************
  */
#ifndef BH1750_H_
#define BH1750_H_


#define BH1750_SLA 	((uint8_t)0x46)				/* Adres slave ukladu */

#define BH1750_Power_OFF	((uint8_t)0x00)		/* Stan uspienia */
#define BH1750_Power_ON		((uint8_t)0x01)		/* Stan aktywnosci */

#define BH1750_RESET		((uint8_t)0x07)		/* Komenda resetu rejestru danych */

/* Tryby pomiarow */
#define BH1750_CHR_MODE    ((uint8_t)0x10)		/* Continuously H-Resolution Mode */
#define BH1750_CHR_MODE2   ((uint8_t)0x11)		/* Continuously H-Resolution Mode2 */
#define BH1750_CLR_MODE    ((uint8_t)0x13)		/* Continuously L-Resolution Mode */
#define BH1750_OTHR_MODE   ((uint8_t)0x20)		/* One Time H-Resolution Mode */
#define BH1750_OTHR_MODE2  ((uint8_t)0x21)		/* One Time H-Resolution Mode2 */
#define BH1750_OTLR_MODE   ((uint8_t)0x23)		/* One Time L-Resolution Mode */

/* Funkcje BH1750 */
void BH1750_PowerOn();
void BH1750_PowerDown();
void BH1750_Start(uint8_t mode);
uint16_t BH1750_Read();
void BH1750_ResetDR();


#endif /* BH1750_H_ */
