/*
 * MOTOR_driver.h
 *
 * Created: 01.11.2017 12:09:32
 *  Author: bendikss
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_
#include <stdint.h>

//static unsigned char ref;

void MOTOR_init(void);
void MOTOR_move(int16_t val);
void MOTOR_move_PID(uint8_t val, uint8_t direction);
void MOTOR_reset_encoder(void);
int16_t MOTOR_read_encoder(void);
void MOTOR_calibrate();
void MOTOR_set_direction(uint8_t val);
uint8_t MOTOR_get_position(void);

#endif /* MOTOR_DRIVER_H_ */