/*
 * ADC.h
 *
 * Module for handling the ADC behaviour in Node 1. Uses a simple interrupt flag to let the
 * read function know if the conversion is done.
 *
 * Created: 13.09.2017 13:40:55
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/*---------Memory address mapping--------------*/
#define ext_ram         ((volatile char*) 0x1800)
#define ext_ram_size    0x800
#define ext_adc         ((volatile char*) 0x1400)
#define ext_oled_cmd    ((volatile char*) 0x1000)
#define ext_oled_data ((volatile char*) 0x1200)

//-------------CHANNELS------------------------//
//Defining channel inputs for ADC
typedef enum{
	X_axis = 4, //axis 2 Joystick 
	Y_axis = 5, //axis 1 Joystick
	R_slide = 6, //right slider
	L_slide = 7, //left slider
}channel_type;
//----------------------------------------------//

/* Initializing ADC */
void ADC_init(void);

/* Starts conversion from the channel taken in as argument,
 then waits for the conversion to finish, and returns the result. */
uint8_t adc_read(channel_type channel);

#endif /* ADC_H */
