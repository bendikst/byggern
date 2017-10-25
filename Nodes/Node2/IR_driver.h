/*
 * IR_driver.h
 *
 * Created: 25.10.2017 15:38:00
 *  Author: bendikss
 */ 


#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_
#include <stdint.h>

void IR_init(void);
uint8_t IR_read(void);

#endif /* IR_DRIVER_H_ */