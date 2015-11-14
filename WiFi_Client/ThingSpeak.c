/*
 * ThingSpeak.c
 *
 *  Created on: 13 lis 2015
 *      Author: Bartek
 */
/**
 *******************************************************************************
 * @ File    BMP180.c
 * @ Author  Bartlomiej Kusmierczyk
 * @ Version V1.0
 * @ Date    28-July-2015
 * @ Brief   This file contains all the BMP180 sensor firmware functions.
 *******************************************************************************
 */

/* Includes -------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "ThingSpeak.h"
#include "ESP8266_Cl.h"



void TS_UpdateField(char* value, uint8_t field)	//?????  zwracac cos i delay
{
	if(field < 10)
	{
		char get[60] = "GET /update?key=";
		char s_field[3];
		sprintf(s_field, "%d=", field);

		strcat(get, ts_APIKey);
		strcat(get, s_field);
		strcat(get, value);
		strcat(get, "\r\n");

		ESP_ConnectServer(ts_ip, "80");
		_delay_ms(5000);
		ESP_SendData(get, strlen(get));
		_delay_ms(3000);
		ESP_Disconnect();
	}
}