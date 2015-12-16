/**
  ******************************************************************************
  * @ Opis    ESP8266_CL.h
  * @ Autor   Bartlomiej Kusmierczyk
  * @ Wersja  V1.0
  * @ Data    28 sierpnia 2015
  * @ Opis    Ten plik zawiera wszystkie prototypy funkcji do obslugi
  * 		  modulu Wi-Fi ESP8266 w trybie klienta, obsluge jednego kanalu
  * 		  wykorzystujac protokol TCP.
  ******************************************************************************
  */
#ifndef ESP8266_H_
#define ESP8266_H_

/* Pin CH_PD */
#define ESP_CHPD_PIN	PB0
#define ESP_CHPD_PORT	PORTB
#define ESP_CHPD_DIR	DDRB

/*  Funkcje ESP8266 */
void ESP_PowerOn();
void ESP_PowerOff();
void ESP_Init();
void ESP_Connect();
void ESP_Disconnect();
void ESP_ConnectServer(char* ip_address, char* port);
void ESP_DisconnectServer();
void ESP_SendData(char* data, uint8_t length);
void ESP_Restart();

#endif /* ESP8266_H_ */
