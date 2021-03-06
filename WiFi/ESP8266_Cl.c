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
#include "ESP8266_Cl.h"



const uint8_t IP_address[4]	= {192,168,1,5};
const uint8_t MAC_address[6] = {0x00,0xbe,0x13,0x0d,0x1c,0xe6};

//ESP_ErrorFlag ErrorFlag;

//#define MYUBRR FOSC/16/BAUD-1

/**
  * @Brief:			Fills the ESP8266 init structure with default values.  ??????????
  * @Parameters:	ESP8266_InitStruct: Pointer to an ESP init structure.
  * @Retval:		None
  */
void ESP_InitStruct(ESP_InitTypeDef* ESP8266_InitStruct)
{
	//Zrobic jakas domyslna funkcje tego  ??????????????
	ESP8266_InitStruct->Mode = 1;						// Client mode
	ESP8266_InitStruct->AP_SecurityMode = 0;			// Open - no security
	ESP8266_InitStruct->DHCP_Protocol = 0;				// No DHCP


}

/**
  * @Brief:			Initializes the ESP8266 module, USART and sets user configuration.		??????????
  * @Parameters:	ESP8266_InitStruct - Pointer to an ESP init structure which contains user configuration.
  * @Retval: 		None
  */
void ESP_Init(ESP_InitTypeDef* ESP8266_InitStruct)
{
  //Send
	//ESP_PowerOn();
		char command[11] = {'A','T','+','C','W','M','O','D','E','=','1'};


	//USART_Init(MYUBRR);


}


/**
  * @ Brief  		Connects module with existing network.
  * @ Parameters	-ssid: Pointer to array which contains network identifier,
  *					-password: Pointer to array which contains network password,
  * @ Retval 		None.
  */
void ESP_Connect(char* ssid, char* password)
{
//Send USART AT+ CWJAP =<ssid>,<pwd>
	char command[9]={'A','T','+','C','W','J','A','P','='};				/* Command: AT+CWJAP=<ssid>,<password> */
	char comma[1] = {','};
	USART_TransmitString(command,9);
	USART_TransmitString(ssid, strlen(ssid)-1);
	USART_TransmitString(comma,1);
	USART_TransmitString(password, strlen(password)-1);

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
	USART_TransmitString(command, 6);
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
  * @Brief:  		Disconnect module from the network.
  * @Parameters:	None.
  * @Retval: 		None.
  */
void ESP_Disconnect()
{
	char command[8]={'A','T','+','C','W','Q','A','P'};
	USART_TransmitString(command,8);
}


/**
  * @Brief:			Sets the IPv4 address in Client or Access Point mode.
  * @Parameters:	-ESP8266_InitStruct: Pointer to an ESP init structure which contains configurations parameters.
  *           		-ip_address - pointer to array which contains IPv4 address.
  * @retval
  */
ESP_ErrorFlag ESP_SetIP(ESP_InitTypeDef* ESP8266_InitStruct, uint8_t* ip_address)
{
	if(ESP8266_InitStruct->Mode == ESP8266_STA)
	{
		char command[10] = {'A','T','+','C','I','P','S','T','A','='};				// Command: AT+CIPSTA=<ip>
		USART_TransmitString(command,13);
		USART_TransmitData(ip_address,4);
		return ESP_OK;
	}
	else if(ESP8266_InitStruct->Mode == ESP8266_AP)
	{
		char command[9] = {'A','T','+','C','I','P','A','P','='};		// Command: AT+CIPAP=<ip>
		USART_TransmitString(command,9);
		USART_TransmitData(ip_address,4);
		return ESP_OK;
	}
	else
	{
		return ESP_ERROR;
	}
}


ESP_ErrorFlag ESP_SetMAC(ESP_InitTypeDef* ESP8266_InitStruct, uint8_t* mac_address)
{

	if(ESP8266_InitStruct->Mode == ESP8266_STA)
	{
		char command[13] = {'A','T','+','C','I','P','S','T','A','M','A','C','='};		// Command: AT+CIPSTAMAC=<mac>
		USART_TransmitString(command,13);
		USART_TransmitData(mac_address,6);
		return ESP_OK;
	}
	else if(ESP8266_InitStruct->Mode == ESP8266_AP)
	{
		char command[12] = {'A','T','+','C','I','P','A','P','M','A','C','='};		// Command: AT+CIPAPMAC=<mac>
		USART_TransmitString(command,12);
		USART_TransmitData(mac_address,6);
		return ESP_OK;
	}
	else
	{
		return ESP_ERROR;
	}
}


void ESP_AccessPoint(ESP_InitTypeDef* ESP8266_InitStruct)		// Czy podzielic na 3 funkcje AP i Client
																// Czy haslo kanal i kodowanie w strukturze
{
	//AT+ CWSAP=<nazwa>,<haslo>,<kanal>,<kodowanie>
	char command[9] = {'A','T','+','C','W','S','A','P'};		// Command: AT+C
	char comma[1] = {','};
}


void ESP_Restart()
{
	char command[9] = {'A','T','+','R','S','T'};		// Command: AT+RST

	USART_TransmitString(command,6);
}


