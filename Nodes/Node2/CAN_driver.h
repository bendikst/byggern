/*
 * CAN_driver.h
 *
 * Top layer module for transmitting messages over the CAN connection.
 *  Uses the MCP2515 driver and the SPI driver to convert information.
 *
 * Created: 04.10.2017 11:56:33
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct CAN_message {
	
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	
	}CAN_message;

typedef enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MIDDLE
	
}JOYSTICK_direction_t;

volatile static CAN_message rec_msg;

/*Initializes the SPI interface and MCP2515 in NORMAL mode, enables all receive interrupts*/
uint8_t CAN_init(void);

/*Writes the struct members to their corresponding registers in the MCP2515*/
void CAN_transmit(CAN_message* msg);

/*Reads the receive buffer registers in the MCP2515, handles rollover. Runs every CAN-interrupt*/
CAN_message CAN_receive(void);

/*Returns the 'private' variable "rec_msg" which holds the latest received CAN message.*/
CAN_message CAN_get_curr(void);

/*Sends a CAN message back to Node 1 when the game is lost.*/
void CAN_transmit_game(bool lose);


#endif /* CAN_DRIVER_H_ */
