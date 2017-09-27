/*
 * JOYSTICK_driver.h
 *
 * Created: 13.09.2017 18:31:17
 *  Author: bendikss
 */ 


#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_

#include <stdbool.h>

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
	int x_pos;
	int y_pos;
}JOYSTICK_position_t;


void JOYSTICK_init(void);
void JOYSTICK_calibrate(void);
bool JOYSTICK_button(int button);
JOYSTICK_position_t JOYSTICK_getPosition(void);
JOYSTICK_direction_t JOYSTICK_getDirection(void);
void MENU_main(void);



#endif /* JOYSTICK_DRIVER_H_ */