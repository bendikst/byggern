/*
 * JOYSTICK_driver.c
 *
 * Created: 13.09.2017 18:30:57
 *  Author: bendikss
 */ 

#include "JOYSTICK_driver.h"
#include "ADC.h"


static int x_initialpos, y_initialpos;



void JOYSTICK_init(){
	x_initialpos = adc_read(X_axis);
	y_initialpos = adc_read(Y_axis);
}



JOYSTICK_position_t JOYSTICK_getPosition(void){
	JOYSTICK_position_t returner;
	returner.x_pos = (adc_read(X_axis)-x_initialpos)/();
	
	
	
}


JOYSTICK_direction_t JOYSTICK_getDirection(void){
	
	JOYSTICK_position_t position = JOYSTICK_getPosition();
	
	int mid_lim = 50;
	position.x_pos > mid_lim ? return UP:
	position.x_pos < -mid_lim ? return DOWN:
	position.y_pos > mid_lim ? return RIGHT:
	position.y_pos < -mid_lim ? return LEFT:
	
	return MIDDLE
}