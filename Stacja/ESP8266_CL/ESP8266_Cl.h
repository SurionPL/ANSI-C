/**
  ******************************************************************************
  * @ Opis    ESP8266_CL.h
  * @ Autor   Bartlomiej Kusmierczyk
  * @ Wersja  V1.0
  * @ Data    28 sierpnia 2015
  * @ Opis    Ten plik zawiera wszystkie prototypu funkcji do obslugi wysylania
  * 		  danych modulu Wi-Fi ESP8266 w trybie klienckim (STA).
  ******************************************************************************
  */
#ifndef ESP8266_H_
#define ESP8266_H_

#define ESP_CHIP_PIN	PB0
#define ESP_CHIP_PORT	PORTB
#define ESP_CHIP_DIR	DDRB

/* Bledy */
typedef enum
{
	ESP_OK = 0,
	ESP_Error = 1,
	ESP_Chan_Error,
	ESP_Protocol_Error
}ESP_ErrorFlag;


/*  Funkcje ESP8266 */
void ESP_PowerOn();
void ESP_Init();
void ESP_Restart();	//++
void ESP_Connect(char* ssid, char* password);
void ESP_Disconnect();
ESP_ErrorFlag ESP_ConnectServer(char* ip_address, char* port);
void ESP_DisconnectServer();
void ESP_SendData(char* data, uint8_t length);

#endif /* ESP8266_H_ */
