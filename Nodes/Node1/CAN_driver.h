/*
 * CAN_driver.h
 *
 * Created: 04.10.2017 11:56:33
 *  Author: aleksra
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_
#include <stdint.h>
#include "JOYSTICK_driver.h"


typedef struct CAN_message {
	
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	
	}CAN_message;


static CAN_message rec_msg;

uint8_t CAN_init(void);
void CAN_transmit(CAN_message* msg);
CAN_message CAN_receive(void);

CAN_message CAN_joystick_transmit(void);

void CAN_print(void); //TESTFUNKSJON

#endif /* CAN_DRIVER_H_ */