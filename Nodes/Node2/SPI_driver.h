/*
 * SPI_driver.h
 *
 * Created: 04.10.2017 11:57:21
 *  Author: aleksra
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <stdint.h>
#include "MCP2515.h"
/* 
SPI communication driver
*/

void SPI_MasterInit(void);
char SPI_transceive(char cData);



#endif /* SPI_DRIVER_H_ */