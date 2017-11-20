/*
 * SPI_driver.h
 *
 * Lowest layer module for using the SPI language communication, between the Atmega162 and MCP2515.
 *
 * Created: 04.10.2017 11:57:21
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "MCP2515.h"

/* SPI communication driver */

void SPI_MasterInit(void);
char SPI_transceive(char cData);

#endif /* SPI_DRIVER_H_ */
