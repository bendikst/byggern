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



JOYSTICK_position_t JOYSTICK_getPosition(void){ //maps joystick values to 0-100 with a small deadband
	JOYSTICK_position_t returner;
	int deadband = 3;
	
	uint8_t xval = adc_read(X_axis);
	uint8_t yval = adc_read(Y_axis);
	
	if(xval>x_initialpos+deadband || xval<x_initialpos-deadband){ //implement small deadband to avoid jittering
		returner.x_pos = (xval)/(double)(MAX_VALUE)*100;
	}else{
		returner.x_pos = 50;
	}
	if(yval>y_initialpos+deadband || yval<y_initialpos-deadband){
	returner.y_pos = (yval)/(double)(MAX_VALUE)*100;
	}else{
		returner.y_pos = 50;
	}
	
	if(returner.x_pos < 2){//avoiding jittering
		returner.x_pos = 0;
	}
	if(returner.y_pos < 2){
		returner.y_pos = 0;
	}
	
	/* previous implementation mapped from -100 to 100
	returner.x_pos = (adc_read(X_axis)-x_initialpos)/(double)(MAX_VALUE-x_initialpos)*100;
	returner.y_pos = (adc_read(Y_axis)-y_initialpos)/(MAX_VALUE-y_initialpos)*100;	
	*/
	
	return returner;
}


JOYSTICK_direction_t JOYSTICK_getDirection(void){
	
	JOYSTICK_position_t position = JOYSTICK_getPosition();
	
	int middle = 50;
	int deadband = 15;
	
	if (position.y_pos > middle+deadband) return UP;
	if (position.y_pos < middle-deadband) return DOWN;
	if (position.x_pos > middle+deadband) return RIGHT;
	if (position.x_pos < middle-deadband) return LEFT;
	return MIDDLE;
}