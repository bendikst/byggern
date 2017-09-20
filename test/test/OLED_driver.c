/*
 * OLED_driver.c
 *
 * Created: 20.09.2017 12:22:59
 *  Author: aleksra
 */ 
#include "OLED_driver.h"
#include <string.h>
#include "fonts.h"
#include <avr/pgmspace.h>

static uint8_t PAGE, COLUMN;


void OLED_init(void){
	  volatile char *adresse = ext_oled_cmd;
	  
      *adresse = (0xae);        //  display  off
      *adresse = (0xa1);        //segment  remap
      *adresse = (0xda);        //common  pads  hardware:  alternative
      *adresse = (0x12);
      *adresse = (0xc8);        //common output scan direction:com63~com0
      *adresse = (0xa8);        //multiplex  ration  mode:63
      *adresse = (0x3f);
      *adresse = (0xd5);        //display divide ratio/osc. freq. mode
      *adresse = (0x80);
      *adresse = (0x81);        //contrast  control
      *adresse = (0x50);
      *adresse = (0xd9);        //set  pre-charge  period
      *adresse = (0x21);
      *adresse = (0x20);        //Set  Memory  Addressing  Mode
      *adresse = (0x02);
      *adresse = (0xdb);        //VCOM  deselect  level  mode
      *adresse = (0x30);
      *adresse = (0xad);        //master  configuration
      *adresse = (0x00);
      *adresse = (0xa4);        //out  follows  RAM  content
      *adresse = (0xa6);        //set  normal  display
      *adresse = (0xaf);        //  display  on
	  
	  *adresse = (0x00);  //lower colums start adressing
	  *adresse = (0x10);  //higher column start adressing
	  OLED_reset();
	  OLED_home();
	  
}


void OLED_print(unsigned char c)
{
		for(int i = 0; i < 8; i++)
		{
		*ext_oled_data = (pgm_read_byte(&(font8[c - ASCII_OFFSET][i]))); 
		}
		
		//Fra studass: writeData(~pgm_read_byte(&myfont[oledRam[page][col] - ASCII_OFFSET][i]))
}

void OLED_reset(){
	OLED_home();
	for (uint8_t page = 0; page < 8; page++)
	{
		OLED_clear_page(page);
	}
	OLED_home();
}

void OLED_clear_page(uint8_t page){
	OLED_goto_page(page);
	for (int i = 0; i < 128; i++)
	{
		*ext_oled_data = 0;
	}
}

void OLED_home(void){
	PAGE = 0;
	COLUMN = 0;

	*ext_oled_cmd = 0xB0;
	*ext_oled_cmd = 0x00;
	*ext_oled_cmd = 0x10;
}

void OLED_goto_page(uint8_t page){
	PAGE = page;
	page = page + 0xb0;

	*ext_oled_cmd = page;
	*ext_oled_cmd = 0x00;
	*ext_oled_cmd = 0x10;
}

void OLED_goto_column(uint8_t column){
	COLUMN = column;
	*ext_oled_cmd = (0b00001111) & column;
	column = column>>4;
	*ext_oled_cmd = ((0b00001111) & column) + 0b00010000;
}

void OLED_pos(uint8_t page, uint8_t col){
	OLED_goto_page(page);
	OLED_goto_column(col);
}

void OLED_print_str(const char* data){
	for (int i = 0; i<strlen(data); i++)
	
	{
		OLED_print(data[i]);
	}
	
}