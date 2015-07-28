/*
 * main.c
 *
 *  Created on: 20 gru 2014
 *      Author: Bartek
 */
//=========================================BIBLIOTEKI====================================================
//BIBLIOTEKI PODSTAWOWE
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

//BIBLIOTEKI ETHERNET
#include "Ethernet/enc28j60.h"
#include "Ethernet/net.h"
#include "Ethernet/ip_arp_udp_tcp.h"
#include "Ethernet/ip_config.h"

//BIBLIOTEKI LCD
#include "LCD/lcd44780.h"

//BIBLIOTEKI CZUJNIKA
#include "1Wire/ds18x20.h"

//======================DO=CZUJNIKA=================================
//Liczba sensorow
uint8_t sensors;
//Rezultat pomiaru
uint8_t minus, tA, tB;

//Wyswietlanie temperatury na LCD
void disp_temp();
uint8_t deg[8]={14,17,17,14,32,32,32,32};
char tekst[]="Temperatura:";
uint8_t flag=20;
//======================DO=£¥CZNOŒCI=================================
// adres MAC urzadzenia
static uint8_t mymac[6] = {0x00,0xbe,0x13,0x0d,0x1c,0xe6};
// adres IP urzadzenia
static uint8_t myip[4] = {192,168,1,100};
// port do nasluchu
#define MYPORT 80
//rozmiar bufora
#define BUFFER_SIZE 900
static uint8_t buf[BUFFER_SIZE+1];

//============WYSWIETLANIE=TEMPERATURY=NA=WWW=================
//Funkcja zamieniajaca intiger na ciag znakow
char *int_to_str(int val, char *str, int8_t fw, char fill);
//Budory potrzebne do zmiany int->char
char bufor1[4];
char bufor2[3];
//Rezultat konwersji
char *temp[2];

#define PIN_OUT DDRB |=(1<<PB1);
#define LED_ON PORTB |=(1<<PB1);

uint16_t http200ok(void)
{
        return(fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")));
}

// Przygotowanie danych do wys³ania (strona www)
uint16_t print_webpage(uint8_t *buf)
{
		uint16_t plen;

		temp[0]=int_to_str(tA,bufor1,2,' ');
		temp[1]=int_to_str(tB,bufor2,1,' ');

        plen=http200ok();
        plen=fill_tcp_data_p(buf,plen,PSTR("<head><meta http-equiv='Refresh' content='30' /></head>"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<font color='blue' size='5'><b>Temperatura</b>: </font>"));

        if(minus!=0) {
        	plen=fill_tcp_data_p(buf,plen,PSTR("-"));
            plen=fill_tcp_data(buf,plen,temp[0]);
            plen=fill_tcp_data_p(buf,plen,PSTR("."));
            plen=fill_tcp_data(buf,plen,temp[1]);
        }
        else {
        	plen=fill_tcp_data(buf,plen,temp[0]);
        	plen=fill_tcp_data_p(buf,plen,PSTR("."));
        	plen=fill_tcp_data(buf,plen,temp[1]);
        }

        plen=fill_tcp_data_p(buf,plen,PSTR(" °C"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<br><br><tt>Copyright 2015, Jaworski & Kusmierczyk</tt>"));
        return(plen);
}




//======================================MAIN============================================
int main(void) {

	PIN_OUT;
	LED_ON;   						//Zapalenie diody
	lcd_init();						//Inicjalizacja LCD
	lcd_defchar(0x80,deg);			//Definicja wlasnego znaku

	sensors = search_sensors();		//Sprawdzenie sensorow

    uint16_t data;

    //Inicjalizacja sprzetowej karty i nadanie MAC
    enc28j60Init(mymac);
    enc28j60PhyWrite(PHLCON,0x476);

    //Inicjalizacja warstwy stosu
    init_ip_arp_udp_tcp(mymac,myip,MYPORT);

    while(1) {

    	//POMIAR TEMPERATURY
    	if(flag%20==0) {
    		if(tA<10) lcd_cls();
    		lcd_locate(0,0);
    		lcd_str(tekst);

    		DS18X20_start_meas(DS18X20_POWER_EXTERN,NULL);  					//Zadanie rozpoczecia pomiaru
    		_delay_ms(750);
    		if(DS18X20_OK==DS18X20_read_meas(gSensorIDs[0],&minus,&tA,&tB))
    		{
    			disp_temp();
    		}
    		flag=0;
    	}
    	flag++;

        //Odczyt pakietu i obsluga ping
        data=packetloop_icmp_tcp(buf,enc28j60PacketReceive(BUFFER_SIZE, buf));

        //data bedzie rowny zero, gdy nie nadeszlo zapytanie
        if(data==0) {
        	continue;
        }
        //Rozpoczecie obslugi portu 80
        if (strncmp("GET ",(char *)&(buf[data]),4)!=0) {
             data=http200ok();
             data=fill_tcp_data_p(buf,data,PSTR("<h1>200 OK</h1>"));
             goto SENDTCP;
        }
        if (strncmp("/ ",(char *)&(buf[data+4]),2)==0) {
        	data=print_webpage(buf);
            goto SENDTCP;
        }
        else {
        	data=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
            goto SENDTCP;
        }
        SENDTCP:
        www_server_reply(buf,data);    //Wysyla dane na strone
        // Koniec obslugi portu 80
        _delay_ms(2000);
     }
        return (0);
}

//----Wyœwietlanie temperatury----
void disp_temp() {
	lcd_locate(1,4);
	if(minus) {
		lcd_str("-");
	}
	else {
		lcd_str(" ");
	}
	lcd_int(tA);
	lcd_str(".");
	lcd_int(tB);
	lcd_char(0x80);
	lcd_str("C ");
}

/*int->char | val - wartosc int, *str - wskaznik na bufor, fw - spodziewana liczba znakow
fill - znak do wypelnienia pustego pola*/
char *int_to_str(int val, char *str, int8_t fw, char fill) {
	char *strp = str;
	uint8_t subzero = 0;

	if(val<0) {
		val = ~val+1;
		subzero=1;
		fw--;
	}

   do {
      div_t divmod = div(val, 10);

      if((val == 0) && (strp != str)) {
         *strp++ = fill;
      } else {
         *strp++ = divmod.rem + '0';
      }

      val = divmod.quot;
      fw--;
   } while (fw>0);

   if(subzero) *strp++ = '-';
   *strp = 0;
   strrev(str);
   return str;
}
