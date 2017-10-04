/*
 * CAN_driver.c
 *
 * Created: 04.10.2017 11:56:16
 *  Author: aleksra
 */ 
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_setup.h"
#include "MCP2515.h"

uint8_t CAN_init(){
	uint8_t value;
	
	SPI_MasterInit();
	MCP2515_reset();
	
	//SELF TEST (From lab lecture)
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in config mode after reset!\n");
		return 1;
	}
	
	MCP2515_bit_modify(MCP_CANINTE, MODE_MASK, MCP_TX_INT); //Enabling all transmit interrupts. Er dette riktig? all transmit.
	MCP2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_LOOPBACK);
	
	return 0;
}



void CAN_transmit(CAN_message* msg){
	
	
}
