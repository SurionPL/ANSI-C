/*
 * BMP180.c
 *
 *  Created on: 18 wrz 2015
 *      Author: Bartek
 */

/*
 * main.c
 *
 *  Created on: 28 kwi 2014
 *  Autor: £ukasz £uczko
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "I2C_TWI/i2c_twi.h"
#include "BMP180.h"


int AC1, AC2, AC3, B1, B2, MB, MC, MD;
unsigned int AC4, AC5, AC6;
long ut, up, t, p, B5;

void BMP180_init( void ) {
        uint8_t buf[22];
        TWI_read_buf( BMP180_ADDR, 0xAA, 22, buf );

        AC1 = ((int) buf[0] <<8 | ((int) buf[1]));
        AC2 = ((int) buf[2] <<8 | ((int) buf[3]));
        AC3 = ((int) buf[4] <<8 | ((int) buf[5]));
        AC4 = ((unsigned int) buf[6] <<8 | ((unsigned int) buf[7]));
        AC5 = ((unsigned int) buf[8] <<8 | ((unsigned int) buf[9]));
        AC6 = ((unsigned int) buf[10] <<8 | ((unsigned int) buf[11]));
        B1 = ((int) buf[12] <<8 | ((int) buf[13]));
        B2 = ((int) buf[14] <<8 | ((int) buf[15]));
        MB = ((int) buf[16] <<8 | ((int) buf[17]));
        MC = ((int) buf[18] <<8 | ((int) buf[19]));
        MD = ((int) buf[20] <<8 | ((int) buf[21]));

}

void BMP180_getut(void) {
        //odczyt temperatury bez kompensacji
        uint8_t  buf[2], g=0x2E;
        TWI_write_buf( BMP180_ADDR, 0xF4, 1, &g );
        _delay_ms(5); // min. 4.5ms
        TWI_read_buf( BMP180_ADDR, 0xF6, 2, buf );
        ut = ((long) buf[0] << 8 | ((long) buf[1]));
}

void BMP180_getup(void){
        //odczyt cisnienia bez kompensacji
        uint8_t  buf[3], g;
        g=0x34+(BMP180_MODE << 6);
        TWI_write_buf( BMP180_ADDR, 0xF4, 1, &g );
        _delay_ms(2 + (3<<BMP180_MODE));
        TWI_read_buf( BMP180_ADDR, 0xF6, 3, buf );
        up = ((((long) buf[0] <<16) | ((long) buf[1] <<8) | ((long) buf[2])) >> (8-BMP180_MODE)); // wartoœæ cisnienia bez kompensacji
}

long BMP180_gett(void){
        long x1,x2, t;
        BMP180_getut();
        x1 = ((long)ut -  AC6) *  AC5 >> 15;
        x2 = ((int32_t) MC << 11) / (x1 +  MD);
        B5 = x1 + x2;
        t = ((B5 + 8)>>4);
        return t;
}

long BMP180_getp(void){
//      long x1,x2,x3,b3,b6;
        int32_t x1,x2,x3,b3,b6;
        unsigned long b4,b7;
        long p;

        BMP180_getup();
        b6 = B5 - 4000;
        x1 = ( B2* (b6 * b6) >> 12) >> 11;
        x2 = ( AC2 * b6) >> 11;
        x3 = x1 + x2;
        b3 = (((((long) AC1) * 4 + x3) << BMP180_MODE) + 2) >> 2;
        x1 = ( AC3 * b6) >> 13;
        x2 = ( B1 * ((b6 * b6) >> 12)) >> 16;
        x3 = ((x1 + x2) + 2) >> 2;
        b4 = ( AC4 * (uint32_t)(x3 + 32768)) >> 15;
        b7 = ((uint32_t)up - b3) * (50000 >> BMP180_MODE);
        p = b7 < 0x80000000 ? (b7 << 1) / b4 : (b7 / b4) << 1;
        x1 = (p >> 8) * (p >> 8);
        x1 = (x1 * 3038) >> 16;
        x2 = (-7357 * p) >> 16;
        p = p + ((x1 + x2 + 3791) >> 4);
        return p;
}
