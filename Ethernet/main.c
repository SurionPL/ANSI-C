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
#include "lcd44780.h"

//BIBLIOTEKI CZUJNIKA
#include "1Wire/ds18x20.h"


//======================DO=CZUJNIKA=================================
uint8_t czujniki_cnt;
uint8_t znak, tA, tB;
void wyswietl(uint8_t x);

//======================DO=£¥CZNOŒCI=================================
char *int_to_str(int val, char *str, int8_t fw, char znak_wiodacy);
// ustalamy adres MAC
static uint8_t mymac[6] = {0x00,0xbe,0x13,0x0d,0x1c,0xe6};
// ustalamy adres IP urz¹dzenia
static uint8_t myip[4] = {192,168,1,100};
//static const char *bla="Ala"; ???????
// server listen port for www
#define MYWWWPORT 80
#define BUFFER_SIZE 850
static uint8_t buf[BUFFER_SIZE+1];

//ZMIENNE DO WYSWIETLENIA
char bufor1[4];
char bufor2[3];
char *temp[2];

uint16_t http200ok(void)
{
        return(fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")));
}

// prepare the webpage by writing the data to the tcp send buffer
uint16_t print_webpage(uint8_t *buf)
{

	    //itoa(bla,temp,10);
		temp[0]=int_to_str(tA,bufor1,2,' ');
		temp[1]=int_to_str(tB,bufor2,1,' ');
        uint16_t plen;
        plen=http200ok();
        plen=fill_tcp_data_p(buf,plen,PSTR("<font color='blue' size='5'><b>Temperatura</b>: </font>"));
        if(znak!=0)
        {
        	plen=fill_tcp_data_p(buf,plen,PSTR("-"));
            plen=fill_tcp_data(buf,plen,temp[0]);
            plen=fill_tcp_data_p(buf,plen,PSTR("."));
            plen=fill_tcp_data(buf,plen,temp[1]);
        }
        else
        {
        	plen=fill_tcp_data(buf,plen,temp[0]);
        	plen=fill_tcp_data_p(buf,plen,PSTR("."));
        	plen=fill_tcp_data(buf,plen,temp[1]);
        }
        return(plen);
}




//======================================MAIN============================================
int main(void){
	DDRB |=(1<<PB1);
	PORTB |=(1<<PB1);
	lcd_init();
	char tekst[]="Temperatura:";

	czujniki_cnt = search_sensors();



    uint16_t dat_p;



     //initialize the hardware driver for the enc28j60
     enc28j60Init(mymac);
//enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
//delay_loop_1(0); // 60us
     enc28j60PhyWrite(PHLCON,0x476);

     //init the ethernet/ip layer:
     init_ip_arp_udp_tcp(mymac,myip,MYWWWPORT);

     sei();

     while(1){

    	 //POMIAR TEMPERATURY
    	 if(tA<10) lcd_cls();
    	 lcd_locate(0,0);
    	 lcd_str(tekst);

    	 DS18X20_start_meas(DS18X20_POWER_EXTERN,NULL);
    	 _delay_ms(750);
    	 lcd_int(czujniki_cnt);
    	 if(DS18X20_OK==DS18X20_read_meas(gSensorIDs[0],&znak,&tA,&tB))
    	 {
    		 wyswietl(5);
    	 }


            // read packet, handle ping and wait for a tcp packet:
            dat_p=packetloop_icmp_tcp(buf,enc28j60PacketReceive(BUFFER_SIZE, buf));

            /* dat_p will be unequal to zero if there is a valid
            * http get */
            if(dat_p==0){
             // no http request
            	continue;
             }
                // tcp port 80 begin
                if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
                        // head, post and other methods:
                        dat_p=http200ok();
                        dat_p=fill_tcp_data_p(buf,dat_p,PSTR("<h1>200 OK</h1>"));
                        goto SENDTCP;
                }
                // just one web page in the "root directory" of the web server
                if (strncmp("/ ",(char *)&(buf[dat_p+4]),2)==0){
						dat_p=print_webpage(buf);
                        goto SENDTCP;
                }else{
                        dat_p=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
                        goto SENDTCP;
                }
                SENDTCP:
                www_server_reply(buf,dat_p); // send web page data
                // tcp port 80 end==
                _delay_ms(5000);
     }
        return (0);
}

//----Wyœwietlanie temperatury----
void wyswietl(uint8_t x) {
	lcd_locate(1,x);
	if(znak)
	{
		lcd_str("-");
	}
	else {
		lcd_str(" ");
	}
	lcd_int(tA);
	lcd_str(".");
	lcd_int(tB);
	lcd_str(" C ");
}


char *int_to_str(int val, char *str, int8_t fw, char znak_wiodacy) {
	char *strp = str;
	uint8_t subzero = 0;

	if(val<0) {			// jeœli liczba jest ujemna
		val = ~val+1;	// zaneguj i koryguj
		subzero=1;		// ustaw znacznik na 1
		fw--;
	}

   do{
      div_t divmod = div(val, 10);   	// opracja dzielenia oraz modulo - wynik do struktury ldiv_t
      //*strp++ = divmod.rem + '0';   	// wstawianie cyfr od najmniej znacz¹cej do ³añcucha

      if((val == 0) && (strp != str)) {
         *strp++ = znak_wiodacy;
      } else {
         *strp++ = divmod.rem + '0';
      }


      val = divmod.quot;            	// wartoœæ zmniejsza siê o jednostki, dziesi¹tki, setki itd
      fw--;                     		// zmniejszenie licznika szerokoœci formatowanego pola
      // wykonuj pêtlê do momentu sprawdzenia ostatniej cyfry znacz¹cej lub zajêtoœci ca³ego pola
   } while ( (fw>0)  );

   if(subzero) *strp++ = '-';			// jeœli by³a to liczba ujemna, wstaw znak minus
   *strp = 0;                     		// zakoñcz ³añcuch zerem

   // w zwi¹zku z tym, ¿e w ³añcuchu jest odwrócona kolejnoœæ cyfr
   // wykonaj ich zamianê
   strrev(str);

   // zwróæ wskaŸnik do pocz¹tku ³añucha z liczb¹
   return str;
}
