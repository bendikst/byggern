/*
 * MCP2515_setup.c
 *
 * Created: 04.10.2017 14:58:25
 *  Author: aleksra
 */ 
#include "SPI_driver.h"
#include "MCP2515_setup.h"
#include "macaroni.h"
#include <avr/io.h>


/*uint8_t MCP2515_init(void){
	uint8_t value;
	
	SPI_MasterInit();
	MCP2515_reset();
	
	//SELF TEST (From lab lecture)
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in config mode after reset!\n");
		return 1;
	}
	//MORE INIT??
	return 0;
}*/

uint8_t MCP2515_read(uint8_t address){
	uint8_t result;
	
	clear_bit(PORTB, PB4); //Select CAN controller
	SPI_transceive(MCP_READ); //Send read command
	SPI_transceive(address); //Send address
	result = SPI_transceive(0x00); //Read result
	
	set_bit(PORTB, PB4); // Deselect CAN-controlla
	return result;
}

void MCP2515_write(uint8_t data, uint8_t address){
	
	clear_bit(PORTB, PB4); //Select CAN controller
	SPI_transceive(MCP_WRITE); //Send write command
	SPI_transceive(address);
	SPI_transceive(data);
	set_bit(PORTB, PB4);
}

void MCP2515_req_to_send(uint8_t bit){
	
	clear_bit(PORTB, PB4); //Select CAN controller
	switch (bit)
	{
	case 0:
		SPI_transceive(MCP_RTS_TX0);
		break;
	case 1:
		SPI_transceive(MCP_RTS_TX1);
		break;
	case 2:
		SPI_transceive(MCP_RTS_TX2);
	}
	
	set_bit(PORTB, PB4);
}

uint8_t MCP2515_read_status(){
	uint8_t result;
	
	clear_bit(PORTB,PB4);
	
	SPI_transceive(MCP_READ_STATUS); 
	result = SPI_transceive(0xFF);
	
	set_bit(PORTB, PB4);
	
	return result;
}


void MCP2515_bit_modify(uint8_t addresse, uint8_t mask, uint8_t data){
	clear_bit(PORTB,PB4);
	
	SPI_transceive(MCP_BITMOD);
	SPI_transceive(addresse);
	SPI_transceive(mask);
	SPI_transceive(data);
	set_bit(PORTB,PB4);
}

void MCP2515_reset(){
	clear_bit(PORTB,PB4);
	
	SPI_transceive(MCP_RESET);
	set_bit(PORTB,PB4);
}