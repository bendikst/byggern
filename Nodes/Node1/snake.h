


#ifndef SNAKE_H
#define SNAKE_H

#define HEIGHT 16
#define WIDTH 16

#include <stdint.h>

static const unsigned char block_h[8] = {0b00001111,0b00001111,0b00001111,0b00001111,0b00001111,0b00001111,0b00001111,0b00001111};
static const unsigned char block_l[8] = {0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000};

typedef struct apple_struct{
	uint8_t ax;
	uint8_t ay;
	
}apple_struct;

typedef struct snake_struct snake_struct;

typedef struct snake_struct{
	uint8_t px;
	uint8_t py;
	
	snake_struct *next;
}snake_struct;

snake_struct* snake_init(uint8_t length, uint8_t start_x, uint8_t start_y);
snake_struct* snake_add(snake_struct *next, uint8_t px, uint8_t py);
void snake_remove_last(snake_struct *snake);

void play_snake();//loops while the game is played
apple_struct* rand_apple(apple_struct *apple);
snake_struct* move_snake(snake_struct *snake, uint8_t vx,uint8_t vy);

void draw_square(uint8_t px, uint8_t py);
void draw_apple(apple_struct *apple); //draws an apple randomly on the screen
void draw_snake(snake_struct *snake);

void endgame(snake_struct *snake); //frees all allocated memory








#endif
