/*
 * BMP180.h
 *
 *  Created on: 28 lip 2015
 *      Author: Bartek
 */

#ifndef BMP180_H_
#define BMP180_H_

#define BMP180_W 0xEE	//BMP180 Slave Address Write
#define BMP180_R 0xEF	//BMP180 Slave Address Read

void bmp180_start();
void bmp180_addr_select(uint8_t address);
void bmp180_read_param();


#endif /* BMP180_H_ */
