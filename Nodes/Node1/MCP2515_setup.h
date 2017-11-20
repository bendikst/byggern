/*
 * MCP2515_setup.h
 *
 * Interface for using the MCP2515 which serves as the conversion layer between the SPI transmission
 * and CAN messages. Only used by the CAN_driver module which is what the programmer would use for
 * everything else.
 *
 * Created: 04.10.2017 14:58:03
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 


#ifndef MCP2515_SETUP_H_
#define MCP2515_SETUP_H_

#include <stdint.h>

/* Functions for reading and writing to the parameter "address".  Selects CAN controller,
 sends R/W command respectively, then reads or sends the data,
 before finally deselects the CAN controller*/
uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t data, uint8_t address);

/*Requests transmit registers to start transmission*/
void MCP2515_req_to_send(uint8_t bit);

/*Returns the status of the MCP2515*/
uint8_t MCP2515_read_status(void);

/* Function to modify the bits defined by mask, to data, in address "address" */
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

/*Resets the MCP2515*/
void MCP2515_reset(void);


#endif /* MCP2515_SETUP_H_ */
