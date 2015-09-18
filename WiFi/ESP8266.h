/**
  ******************************************************************************
  * @ File:    ESP8266.h
  * @ Author:  Bartlomiej Kusmierczyk
  * @ Version: V1.0
  * @ Date:    28 August 2015
  * @ Brief:   This file contains all the functions prototypes for the ADC
  * 		   firmware library.?????????????
  ******************************************************************************
  */
#ifndef ESP8266_H_
#define ESP8266_H_

#define ESP_CHIP_PIN	PB0
#define ESP_CHIP_PORT	PORTB



/**
  * @Brief  Configuration Mode enumeration
  */
typedef enum
{
  ESP8266_STA	= 1,		// Client mode
  ESP8266_AP	= 2,		// Acces Point mode
  ESP8266_BOTH	= 3			// Both - Client & Acces Point mode
}ESP_Mode_TypeDef;

/**
  * @Brief  DHCP Protocol enabling enumeration
  */
typedef enum
{ DHCP_DISABLE = 0,
  DHCP_ENABLE
}ESP_DHCP_TypeDef;				//?????????????????


/**
  * @Brief  Configuration ?????????????????? poprawic nazwy?
  */
typedef enum
{
  AP_ECN_OPEN	= 0,		// ??  ECN czy nie
  AP_ECN_WEP		= 1,		//
  AP_ECN_WPA		= 2,		//
  AP_ECN_WPA2		= 3,		//
  AP_ECN_WPA_WPA2	= 4			//
}ESP_SecurityMode_TypeDef;



/**
  * @Brief  ESP8266 Init structure definition
  */
typedef struct
{
  ESP_Mode_TypeDef Mode;
  ESP_DHCP_TypeDef DHCP_Protocol;
  ESP_SecurityMode_TypeDef AP_SecurityMode;		//Czy ma byc tutaj
}ESP_InitTypeDef;

/**
  * @Brief  DHCP Protocol enabling enumeration		?????????
  */
typedef enum
{
	ESP_OK = 0,
	ESP_ERROR = 1
}ESP_ErrorFlag;



/*  ESP8266 Functions  */
void ESP_InitStruct(ESP_InitTypeDef* ESP8266_InitStruct);
void ESP_PowerOn();
void ESP_Init();
void ESP_DeInit();
void ESP_Connect(char* ssid, char* password);
void ESP_Disconnect();
ESP_ErrorFlag ESP_SetIP(ESP_InitTypeDef* ESP8266_InitStruct, uint8_t* ip_address);
ESP_ErrorFlag ESP_SetMAC(ESP_InitTypeDef* ESP8266_InitStruct, uint8_t* mac_address);
void ESP_AccessPoint(ESP_InitTypeDef* ESP8266_InitStruct);
#endif /* ESP8266_H_ */