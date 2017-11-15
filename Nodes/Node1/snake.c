#define F_OSC 4915200UL
#define F_CPU F_OSC

#include "JOYSTICK_driver.h"
#include "snake.h"
#include "OLED_driver.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <util/delay.h>



snake_struct* snake_init(uint8_t length, uint8_t start_x, uint8_t start_y){
	
	snake_struct* n = snake_add(NULL, start_x, start_y);
	for(int i = 1; i<length; i++){
		n = snake_add(n, start_x + i, start_y);
		//printf("for\n");
	}
	return n;
}

snake_struct* snake_add(snake_struct *next, uint8_t px, uint8_t py){
	snake_struct* n = malloc(sizeof(snake_struct));
	n->next = next;
	n->px = px;
	n->py = py;
	//printf("inside: %d , %d \n",n->px, n->py);
	return n;
}

void snake_remove_last(snake_struct *snake){
	snake_struct *n = snake;
	snake_struct *temp = n;
	
	while(n->next != NULL){
		temp = n;
		n = n->next;
	}
	free(n);
	temp->next = NULL;
}

void play_snake(){
	
	SRAM_reset();
	printf("snake\n");
	OLED_pos(0, 40);
	OLED_print_str("SNEK");
	OLED_pos(4, 20);
	OLED_print_str("Get ready...");
	OLED_draw();
	_delay_ms(2000);
	
	uint8_t vx = 1;
	uint8_t vy = 0; // snake velocity
	
	uint8_t px = 3;
	uint8_t py = 8;
	uint8_t length = 5;
	snake_struct* head = snake_init(length, px, py);
	apple_struct n; //allokerer plass til eple i compile time
	apple_struct *apple = rand_apple(&n); //lagrer pekeren til eplet
	
	snake_struct* temp;
	
	bool gameover = false; // true when game is over
	bool eating = false; // true if the snake has hit an apple this move
	while (!gameover){
		//----initializing variables----//
		eating = false;
		
		//-----drawing------//
		SRAM_reset();
		draw_snake(head);
		draw_apple(apple);
		OLED_draw();
		//printf("drawing\n");
		
		//-----checking for gameover-----// !!!//TODO: sjekk om snaken treffer seg selv
		if(head->px < 0 || head->px>=WIDTH){
			gameover = true;
		} else if (head->py < 0 || head->py >= HEIGHT){
			gameover = true;
		}
		
		temp = head->next;
		while (temp != NULL){
			if(head->px == temp->px && head->px == temp->py){
				//gameover = true;
			}
			temp = temp->next;
		}
		
		
		//-----checking for apple---//
		if (head->px == apple->ax && head->py == apple->ay){
			eating = true;
			length++;
			apple = rand_apple(apple);
		}
		
		//----updating snake velocity ----//
		switch (JOYSTICK_getDirection())
		{
		case UP:
			if (vy != -1){
				vy = -1;
				vx = 0;
			}
			break;
		case DOWN:
			if (vy != 1){
				vy = 1;
				vx = 0;
			}
			break;
		case LEFT:
			if (vx != 1){
				vy = 0;
				vx = -1;
			}
			break;
		case RIGHT:
			if (vx != -1){
				vy = 0;
				vx = 1;
			}
			break;
		default:
			break;
		}
		//----move snake---//
		head = move_snake(head,vx,vy);
		if (!eating){
			snake_remove_last(head);
		}
		_delay_ms(200);
		
	}
	endgame(head);
}

apple_struct* rand_apple(apple_struct *apple){
	
	apple->ax = rand()%WIDTH;
	apple->ay = rand()%HEIGHT;
	
	return apple;
}

snake_struct* move_snake(snake_struct *snake, uint8_t vx,uint8_t vy){
	snake = snake_add(snake, snake->px+vx, snake->py+vy);
	return snake;
}

void draw_square(uint8_t px, uint8_t py){
	OLED_pos(py/2,px*8);
	//printf("py/2,px*8 = %d, %d \n", py/2,px*8);
	if (py%2 == 1){
		SRAM_custom_print(block_l);
	}else{
		SRAM_custom_print(block_h);
	}
	
}

void draw_apple(apple_struct *apple){
	draw_square(apple->ax, apple->ay);
}

void draw_snake(snake_struct *snake){
	snake_struct *n = snake;
	while(n != NULL){
	draw_square(n->px, n->py);
	n = n->next;
	}
}

void endgame(snake_struct *snake){
	snake_struct *temp;
	while(snake != NULL){
		temp = snake->next;
		free(snake);
		snake = temp;
	}
	//printf("gameover\n");
	SRAM_reset();
	OLED_pos(4, 25);
	OLED_print_str("GAME OVER");
	OLED_draw();
}