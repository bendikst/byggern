/*
 * PWM_driver.h
 *
 * Created: 25.10.2017 11:29:45
 *  Author: Administrator
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "CAN_driver.h"

void PWM_init(void);
void PWM_set_duty_cycle(int cycles); //@param value between 1800 and 4200 to set the servo angle
void PWM_joystick_control(uint8_t val);
void PWM_set_duty_cycle_difficulty(int cycles);

#endif /* PWM_H_ */