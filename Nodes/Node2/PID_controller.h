/*
 * PID_controller.h
 *
 * This module acts as the PID-controller for the motor, to make it easier to play the game.
 *
 * Created: 08.11.2017 16:30:33
 *  Author: alexjoha
 */ 


#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

/*Initializes the controller parameters and enables timer for controlling intervals.*/
void PID_init(void);

/*Regulates the motor position based on the encoder input and reference from the slider on the
 USB multifuntion board. Uses integral effect to reach correct position. */
void PID_regulator(void);

#endif /* PID_CONTROLLER_H_ */
