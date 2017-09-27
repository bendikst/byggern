/*
 * test.c
 *
 * Created: 30.08.2017 12:31:52
 *  Author: bendikss
 */ 
#define F_OSC 4915200UL
#define F_CPU F_OSC
//#define BAUD 9600
//#define MYUBRR (F_OSC)/(16*BAUD)-1

#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "XMEM_module.h"
#include "SRAM.h"
#include "macaroni.h"
#include "JOYSTICK_driver.h"
#include "SLIDER_driver.h"
#include "ADC.h"
#include "OLED_driver.h"
#include "MENU_system.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

int main(void)
{
	
	UART_init(9600);
	XMEM_init();
	ADC_init();
	sei();
	JOYSTICK_init();
	OLED_init();
	//SRAM_test();
	MENU_init();
	
	_delay_ms(100);

	//OLED_print_str("hallo");
	//OLED_draw_arrow(3);
	//OLED_print_str(main_menu->name);
	//OLED_clear_page(1);
	//OLED_print_str("best");
	//OLED_goto_page(2);
	//OLED_print_str(main_menu->children[0]->name);
	//OLED_goto_page(3);
	//OLED_print_str(main_menu->children[1]->name);
	//OLED_goto_page(4);
	//OLED_print_str(main_menu->children[1]->children[0]->name);
	//OLED_goto_page(5);
	//OLED_print_str(main_menu->children[1]->children[1]->name);
	//OLED_goto_page(6);
	//OLED_print_str(main_menu->children[1]->children[2]->name);
	//OLED_goto_page(7);
	
	//OLED_print_menu(curr_menu);
	//OLED_draw_arrow(position);
	for (int page = 0; page < 8; page++){
		for (int col = 0; col < 128; col++ )
		{
			ext_ram[page*128 + col] = 0x00;
		}
	}
	printf("Done clearing\r\n");
	
	
    while(1)
    {
		SRAM_reset();
		MENU_main();
		OLED_draw();
		
    }
}
