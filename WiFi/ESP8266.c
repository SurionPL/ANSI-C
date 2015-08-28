/*
 * ESP8266_H_.c
 *
 *  Created on: 28 sie 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "USART.h"
#include "ESP8266.h"

#define MYUBRR FOSC/16/BAUD-1


/**
  * @brief  Fills the ESP8266 init structure with default values.  ??????????
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ESP_InitStruct(ESP_InitTypeDef* ESP8266_InitStruct)
{
	//Zrobic jakas domyslna funkcje tego  ??????????????
	ESP8266_InitStruct->AP_SecurityMode = 0;
	ESP8266_InitStruct->DHCP_Protocol = 0;
	ESP8266_InitStruct->Mode = 0;

}

/**
  * @brief  Enables or disables the specified USART peripheral.		??????????
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ESP_Init(ESP_InitTypeDef* esp8266_InitStruct)
{
  //Send
	USART_Init(MYUBRR);
}


/**
  * @ Brief  		Connects module with existing network
  * @ Parameters	-ssid: Pointer to array which contains network identifier
  *					-password: Pointer to array which contains network password
  * @ Retval 		None
  */
void ESP_Connect(char* ssid, char* password)
{
//Send USART AT+ CWJAP =<ssid>,<pwd>
	char command[10]={'A','T','+','C','W','J','A','P','=',','};				// Command: AT+CWJAP=<ssid>,<password>
	char comma[1] = {','};
	USART_Send_String(command,9);
	USART_Send_String(ssid, strlen(ssid));
	USART_Send_String(comma,1);
	USART_Send_String(password, strlen(password));

}



/**
  * @brief  Enables or disables the specified USART peripheral.				???????????
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ESP_DeInit()
{
//Send USART AT+RST
	char command[6] = {'A','T','+','R','S','T'};
	USART_Send_String(command, 6);
}

/**
  * @brief  Enables or disables the specified USART peripheral.				????????
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ESP_PowerOn()
{
	ESP_CHIP_PORT |= (1<<ESP_CHIP_PIN);
}

/**
  * @brief  Enables or disables the specified USART peripheral.				??
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ESP_PowerOff()
{
	ESP_CHIP_PORT &= ~(1<<ESP_CHIP_PIN);
}




/**
  * @Brief  	Disconnect module from the network.
  * @Parameters	None
  * @Retval 	None
  */
void ESP_Disconnect()
{
	char command[8]={'A','T','+','C','W','Q','A','P'};
	USART_Send_String(command,8);
}



uint8_t ESP_SetIP(ESP_InitTypeDef* ESP8266_InitStruct)
{
	return 0;
}


uint8_t ESP_SetMAC(ESP_InitTypeDef* ESP8266_InitStruct)
{
	return 0;
}


void ESP_AccessPoint(ESP_InitTypeDef* ESP8266_InitStruct)
{

}



