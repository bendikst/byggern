/*
 * MCP2515_setup.h
 *
 * Created: 04.10.2017 14:58:03
 *  Author: aleksra
 */ 


#ifndef MCP2515_SETUP_H_
#define MCP2515_SETUP_H_




//uint8_t MCP2515_init(void); Tror ikke vi trenger
uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t data, uint8_t address); //HVorfor ikke char*?
void MCP2515_req_to_send(uint8_t bit);
uint8_t MCP2515_read_status(void);
void MCP2515_bit_modify(uint8_t addresse, uint8_t mask, uint8_t data);
void MCP2515_reset(void);


#endif /* MCP2515_SETUP_H_ */