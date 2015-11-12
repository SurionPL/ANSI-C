/*
 * ESP8266_H_.c
 *
 *  Created on: 28 sie 2015
 *      Author: Bartek
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "MKUART/mkuart.h"
#include "ESP8266_Cl.h"
#include "avr/pgmspace.h"
#include "string.h"

// UZYC STRCAT(DEST,SRC)

//const uint8_t IP_address[4]	= {192,168,1,5};
//const uint8_t MAC_address[6] = {0x00,0xbe,0x13,0x0d,0x1c,0xe6};

const char IP_address[] = "192.168.1.5";
const char MAC_address[] = "00:BE:13:0D:1C:E6";
//prog_char TAB[] = "00:BE:13:0D:1C:E6";
//char *LINE1 = PSTR("Pierwsza linia na LCD");

//ESP_ErrorFlag ErrorFlag;

//#define MYUBRR FOSC/16/BAUD-1

/**
  * @Brief:			Fills the ESP8266 init structure with default values.  ??????????
  * @Parameters:	ESP8266_InitStruct: Pointer to an ESP init structure.
  * @Retval:		None
  */
void ESP_InitStruct()
{
	//ESP8266_InitStruct->DHCP_Protocol = 0;				// No DHCP


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
		//char command[11] = {'A','T','+','C','W','M','O','D','E','=','1'};
	uart_puts(PSTR("AT+CWMODE=1\r\n"));
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
	char command[50] = "AT+CWJAP=\"";
	strcat(command, ssid);
	strcat(command, "\",\"");
	strncat(command, password, strlen(password));
	strcat(command,"\r\n");
//Send USART AT+ CWJAP =<ssid>,<pwd>
	uart_puts(command);

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
	//char command[6] = {'A','T','+','R','S','T'};
	//USART_TransmitString(command, 6);
	uart_puts(PSTR("AT+RST\r\n"));
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
	uart_puts(PSTR("AT+CWQAP\r\n"));

}


/**
  * @Brief:			Sets the IPv4 address in Client or Access Point mode.
  * @Parameters:	-ESP8266_InitStruct: Pointer to an ESP init structure which contains configurations parameters.
  *           		-ip_address - pointer to array which contains IPv4 address.
  * @retval
  */
ESP_ErrorFlag ESP_SetIP(ESP_InitTypeDef* ESP8266_InitStruct, uint8_t* ip_address)
{
	if(1)
	{
		//char command[10] = {'A','T','+','C','I','P','S','T','A','='};				// Command: AT+CIPSTA=<ip>
		//char command[11] = "AT+CIPSTA=";
		uart_puts("AT+CIPSTA=");
		//USART_TransmitString(command,11);

		//USART_TransmitData(ip_address,4);
		return ESP_OK;
	}
	else
	{
		return ESP_ERROR;
	}
}


ESP_ErrorFlag ESP_SetMAC(ESP_InitTypeDef* ESP8266_InitStruct, uint8_t* mac_address)
{

	if(1)
	{
		//char command[13] = {'A','T','+','C','I','P','S','T','A','M','A','C','='};
		//char command[]="AT+CIPSTAMAC="// Command: AT+CIPSTAMAC=<mac>
		//USART_TransmitString(command,13);
		uart_puts("AT+CIPSTAMAC=");
		//USART_TransmitData(mac_address,6);
		return ESP_OK;
	}
	else
	{
		return ESP_ERROR;
	}
}





void ESP_Restart()
{
	//char command[9] = {'A','T','+','R','S','T'};		// Command: AT+RST

	//USART_TransmitString(command,6);
	uart_puts("AT+RST\r\n");
}

void ESP_ConnectServer(char* ip_address, char* port)
{
	char command[50]= "AT+CIPSTART=\"TCP\",";
	strcat(command, ip_address);
	strcat(command ,"\",");
	strcat(command, port);
	strcat(command, "\r\n");

	uart_puts(command);

}
