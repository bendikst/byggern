/*
 * IR_driver.h
 *
 * Module for reading the IR-sensor on the game board.
 *
 * Created: 25.10.2017 15:38:00
 *  Author: bendikss
 */ 


#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_
#include <stdint.h>

/* Enables the atmega2560s internalADC, sets prescaler, reference voltage and enables interrupt*/
void IR_init(void);

/* Starts a conversion of the IR-sensor data, and waits for the conversion to finish.
 Returns result.*/
uint8_t IR_read(void);

#endif /* IR_DRIVER_H_ */
