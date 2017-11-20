/*
 * OLED_driver.h
 *
 * Snake game for the OLED screen on the USB multifunction board.
 *
 * Created: 20.09.2017 12:23:16
 *  Author: Alexander Johansen
 *      Revised by: Bendik Standal
 */

#ifndef SNAKE_game_H
#define SNAKE_game_H

#define HEIGHT 16
#define WIDTH 16

#include <stdint.h>

static const unsigned char block_h[8] = {0b00001111,0b00001111,0b00001111,0b00001111,0b00001111,0b00001111,0b00001111,0b00001111};
static const unsigned char block_l[8] = {0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000};

typedef struct apple_struct {
	uint8_t ax;
	uint8_t ay;
	
}apple_struct;

typedef struct snake_struct snake_struct;

typedef struct snake_struct {
	uint8_t px;
	uint8_t py;
	snake_struct *next;
}snake_struct;

/*Initializes a snake of length "length" and start position.*/
snake_struct* SNAKE_init(uint8_t length, uint8_t start_x, uint8_t start_y);

/* Adds a new square to the snake. */
snake_struct* SNAKE_add(snake_struct *next, uint8_t px, uint8_t py);

/* Function for removing the last square of the snake if it is not eating an apple. */
void SNAKE_remove_last(snake_struct *snake);

/* Game loop function. Draws the snake and handles game logic. */
void SNAKE_play(char* player);

/* Functions for making the snake head move and creating a new apple at a random position. */
apple_struct* rand_apple(apple_struct *apple);
snake_struct* move_snake(snake_struct *snake, uint8_t vx,uint8_t vy);

/* Functions for drawing the snake and apple to the OLED screen. Utilizes the SRAM for dual
 frame buffering. */
void draw_square(uint8_t px, uint8_t py);
void draw_apple(apple_struct *apple);
void draw_snake(snake_struct *snake);

/*Frees all allocated memory. */
void endgame(snake_struct *snake);

#endif
