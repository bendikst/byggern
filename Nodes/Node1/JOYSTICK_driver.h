/*
 * JOYSTICK_driver.h
 *
 * Module for correctly reading the joystick from the USB-multifunction board in Node 1.
 *
 * Created: 13.09.2017 18:31:17
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 


#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_

#include <stdbool.h>
#include <avr/io.h>

#define MAX_VALUE 255

typedef enum  
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MIDDLE
	
}JOYSTICK_direction_t;

typedef struct
{
	uint8_t x_pos;
	uint8_t y_pos;
}JOYSTICK_position_t;

/* Reads the joystick to gat initial middle values. The joystick should be in the neutral position
 when calling this function. */
void JOYSTICK_init(void);

/* Maps joystick values to 0-100 using a small deadband to avoid jittering. */
JOYSTICK_position_t JOYSTICK_getPosition(void);

/* Returns the direction the joystick is pointing. */
JOYSTICK_direction_t JOYSTICK_getDirection(void);



#endif /* JOYSTICK_DRIVER_H_ */
