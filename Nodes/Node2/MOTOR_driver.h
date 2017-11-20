/*
 * MOTOR_driver.h
 *
 * This module controls the motor box with the motor encoder. Used by the PINGPONG module
 * for controlling the position of the bouncer.
 *
 * Created: 01.11.2017 12:09:32
 *  Author: bendikss
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_
#include <stdint.h>

/* Initializes the TWI, enables motor and encoder and setting data bits as input.*/
void MOTOR_init(void);

/*Takes in a value val that gives both direction and speed of the motor,
 based of the error calculated in the PID controller module */
void MOTOR_move(int16_t val);

/*Resets encoder value*/
void MOTOR_reset_encoder(void);

/* Returns the read encoder value*/
int16_t MOTOR_read_encoder(void);

/*Runs the motor to its leftmost position to calibrate the encoder value reference
 and make calculating og the position possible.*/
void MOTOR_calibrate();

/*Setting direction of travel for the motor.*/
void MOTOR_set_direction(uint8_t val);

/*Reads the motor position form the encoder value as distance from the reference. Returns
 distance between 0-255.*/
uint8_t MOTOR_get_position(void);

#endif /* MOTOR_DRIVER_H_ */
