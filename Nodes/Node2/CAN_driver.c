/*
 * CAN_driver.c
 *
 * Created: 04.10.2017 11:56:16
 *  Author: aleksra
 */ 
#include "CAN_driver.h"
#include "SPI_driver.h"
#include <stdio.h>
#include "MCP2515_setup.h"
#include "MCP2515.h"
#include "macaroni.h"
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

uint8_t CAN_init(){
	//--- setup of interrupts on the ATmega 2560 for CAN receive----//
	
		//Interrupt on falling edge PD0:
		clear_bit(EICRA, ISC00);
		set_bit(EICRA, ISC01);
		//Enabler interrupt on a pit:
		set_bit(EIMSK, INT2);
		// INT2 intflag is cleared by writing 1 to INTF2
		set_bit(EIFR, INTF2);
	

	SPI_MasterInit();
	MCP2515_reset();
	_delay_us(100);
	
	//MCP2515_write(MODE_CONFIG, MCP_CANSTAT);
	//SELF TEST (From lab lecture)
	uint8_t value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in config mode after reset!\n");
		return 1;
	}
	
	MCP2515_bit_modify(MCP_CANINTE, 0b11, MCP_RX_INT); //Enable all receive interrupts
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	return 0;
}



void CAN_transmit(CAN_message* msg){
	
	MCP2515_write((uint8_t)(msg->id>>3), MCP_TXB0SIDH);
	MCP2515_write((uint8_t)(msg->id<<5), MCP_TXB0SIDL);
	
	
	MCP2515_write(msg->length, MCP_TXB0DLC);
	for(int i = 0; i< msg->length; i++){
		MCP2515_write(msg->data[i],MCP_TXB0D+i);
	}
	
	
	MCP2515_req_to_send(0);
}


CAN_message CAN_receive(){

	CAN_message msg;
	
	if (MCP2515_read(MCP_CANINTF) & (0b10)) //Checking rollover
	{ 
		msg.id = (MCP2515_read(MCP_RXB1SIDH)<<3) + (MCP2515_read(MCP_RXB1SIDL)>>5);
		msg.length = MCP2515_read(MCP_RXB1DLC);
		for (uint8_t i = 0; i < msg.length; i++)
		{
			msg.data[i] = MCP2515_read(MCP_RXB1D+i);
		}
		
		MCP2515_bit_modify(MCP_CANINTF, 0x02, 0); //Clear interrupt flag
		
	} else //if(MCP2515_read(MCP_CANINTF) & (0b01))
	{
		msg.id = (MCP2515_read(MCP_RXB0SIDH)<<3) + (MCP2515_read(MCP_RXB0SIDL)>>5);
		msg.length = MCP2515_read(MCP_RXB0DLC);
		for (uint8_t i = 0; i < msg.length; i++)
		{
			msg.data[i] = MCP2515_read(MCP_RXB0D+i);
		}
		MCP2515_bit_modify(MCP_CANINTF, 0x01, 0); //Clear interrupt flag
	}//else{
		//msg.id = 100;
	//}
	
	return msg;
}


//void CAN_print(void){ //TESTFUNKSJON
	//
	//CAN_message* msg = &rec_msg;
	//
	//char temp[msg->length+1];
	//for (uint8_t i = 0; i < msg->length; i++){
		//temp[i] = (unsigned char)msg->data[i];
	//}
	//temp[msg->length] = '\0';
	//printf("Message received: \nid:%d \nlength%d \nData:%s\n", msg->id, msg->length, temp);
//}

CAN_message CAN_get_curr(){
	return rec_msg;
}


ISR(INT2_vect){
	//Studass mener heller vi bør bruke et eget flagg som sier at interrupt har skjedd?
	//rec_flag = 1;
	rec_msg = CAN_receive();
}