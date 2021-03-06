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
#ifndef ESP8266_CL_H_
#define ESP8266_CL_H_

#define ESP_CHIP_PIN	PB0
#define ESP_CHIP_PORT	PORTB

//


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

#endif /* ESP8266_CL_H_ */
