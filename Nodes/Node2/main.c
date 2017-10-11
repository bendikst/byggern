/*
 * Node2.c
 *
 * Created: 11.10.2017 16:57:57
 *  Author: alexjoha
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include "SPI_driver.h"
#include "CAN_driver.h"
#include "macaroni.h"
#include "UART_driver.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	
	cli();
	UART_init(9600);
	CAN_init();
	sei();
	SPI_MasterInit();
	
	printf("node 2 \n");
	
	
    while(1)
    {
		printf("node 2 \n");
        //TODO:: Please write your application code 
    }
}