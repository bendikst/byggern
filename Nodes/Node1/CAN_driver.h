/*
 * CAN_driver.h
 *
 *  Top layer module for transmitting messages over the CAN connection. 
 *  Uses the MCP2515 driver and the SPI driver to convert information.
 *
 * Created: 04.10.2017 11:56:33
 *  Author: aleksra, Alexander Johansen, Bendik Standal
 * 
 */ 


/*-------------CAN_message IDs------------------
ID:			Function:
0___________Gamecontrols
5___________Start game to Node 2
8___________New game difficulty to Node 2
11__________Game lost from Node 2
---------------CAN_message IDs-----------------*/


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_
#include <stdint.h>
#include "JOYSTICK_driver.h"


typedef struct CAN_message {
	
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	
	}CAN_message;

/*Initializes the SPI interface and MCP2515 in NORMAL mode, enables all receive interrupts*/
uint8_t CAN_init(void);

/*Writes the struct members to their corresponding registers in the MCP2515*/
void CAN_transmit(CAN_message* msg);

/*Reads the receive buffer registers in the MCP2515, handles rollover. Runs every CAN-interrupt*/
CAN_message CAN_receive(void);

/*Returns the 'private' variable "rec_msg" which holds the latest received CAN message.*/
CAN_message CAN_get_curr(void);

/*Reads the state of the joystick, slider and button to be used for playing the game.*/
CAN_message CAN_gamecontrols_transmit(void);
CAN_message CAN_joystick_transmit(void);

#endif /* CAN_DRIVER_H_ */
