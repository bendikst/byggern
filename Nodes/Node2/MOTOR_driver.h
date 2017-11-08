/*
 * MOTOR_driver.h
 *
 * Created: 01.11.2017 12:09:32
 *  Author: bendikss
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_
#include <stdint.h>

void MOTOR_init(void);
void MOTOR_move(uint8_t val);
void MOTOR_move_PID(uint8_t val);
void MOTOR_reset_encoder(void);
int16_t MOTOR_read_encoder(void);
void MOTOR_calibrate();
void MOTOR_set_direction(uint8_t val);

#endif /* MOTOR_DRIVER_H_ */