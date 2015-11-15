/**
  ******************************************************************************
  * @ File:    ESP8266_CL.h
  * @ Author:  Bartlomiej Kusmierczyk
  * @ Version: V1.0
  * @ Date:    28-August-2015
  * @ Brief:   This file contains all the functions prototypes for the ESP8266
  * 		   firmware library in client mode.
  ******************************************************************************
  */
#ifndef ESP8266_H_
#define ESP8266_H_

#define ESP_CHIP_PIN	PB0
#define ESP_CHIP_PORT	PORTB

//http://www.tutorialspoint.com/c_standard_library/string_h.htm

//static uint8_t ESP8266_MAC[6] = {0x00, 0xbe, 0x13, 0x0d, 0x1c, 0xe6};
//static uint8_t ESP8266_IP[4] = {192, 168, 1, 100};



/**
  * @Brief  ES82266 error flags enumeration
  */
typedef enum
{
	ESP_OK = 0,
	ESP_Error = 1,
	ESP_Chan_Error,
	ESP_Protocol_Error
}ESP_ErrorFlag;


/*  ESP8266 Functions  */
void ESP_PowerOn();
void ESP_Init();
void ESP_Restart();	//++
void ESP_Connect(char* ssid, char* password);
void ESP_Disconnect();
ESP_ErrorFlag ESP_ConnectServer(char* ip_address, char* port);
void ESP_DisconnectServer();
void ESP_SendData(char* data, uint8_t length);

#endif /* ESP8266_H_ */
