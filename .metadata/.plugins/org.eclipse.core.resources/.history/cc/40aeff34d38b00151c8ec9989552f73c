/**
 *******************************************************************************
 * @ File    ESP8266_CL.c
 * @ Author  Bartlomiej Kusmierczyk
 * @ Version V1.0
 * @ Date    28-August-2015
 * @ Brief   This file contains all the ESP8266 wi-fi module firmware functions.
 *******************************************************************************
 */

/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "MKUART/mkuart.h"
#include "ESP8266_Cl.h"
#include "avr/pgmspace.h"
#include "string.h"

//const char IP_address[] = "192.168.1.5";
//const char MAC_address[] = "00:BE:13:0D:1C:E6";




/**
  * @Brief:			Initializes the ESP8266 module - Client mode and single channel connection.
  * @Parameters:	None.
  * @Retval: 		None.
  */
void ESP_Init()
{
  //Send
	//ESP_PowerOn();
	uart_puts(PSTR("AT+CWMODE=1\r\n"));		/* Client mode */
	_delay_ms(4000);
	uart_puts(PSTR("AT+CIPMUX=0\r\n"));		/* Multi channel connection */
	_delay_ms(4000);
	//USART_Init(MYUBRR);
}


/**
  * @ Brief  		Connects module with existing network.
  * @ Parameters	-ssid: Pointer to array which contains network identifier.
  *					-password: Pointer to array which contains network password,
  * @ Retval 		None.
  */
void ESP_Connect(char* ssid, char* password)
{
	char command[50] = "AT+CWJAP=\"";
	strcat(command, ssid);
	strcat(command, "\",\"");
	strcat(command, password);
	strcat(command,"\"\r\n");
//Send USART AT+ CWJAP =<ssid>,<pwd>
	uart_puts(command);
	_delay_ms(3000);

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
  * @brief  Enables or disables the specified USART peripheral.				????????
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ESP_Restart()
{
	//USART_TransmitString(command,6);
	uart_puts(PSTR("AT+RST\r\n"));
	_delay_ms(1000);
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
ESP_ErrorFlag ESP_ConnectServer(char* ip_address, char* port)
{
	//Jeden kanal i jeden protokol
		char command[50] = "AT+CIPSTART=\"TCP\",\"";
		strcat(command, ip_address);
		strcat(command ,"\",");
		strcat(command, port);
		strcat(command, "\r\n");

		uart_puts(command);

		return ESP_OK;
}

void ESP_SendData(char* data, uint8_t length)
{
	char s_length[4];
	char command[25] = "AT+CIPSEND=";

	sprintf(s_length, "%d", length);
	strcat(command, s_length);
	strcat(command, "\r\n");

	uart_puts(command);
	_delay_ms(1000);
	uart_puts(data);

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
void ESP_DisconnectServer()
{
	uart_puts(PSTR("AT+CIPCLOSE\r\n"));
}
