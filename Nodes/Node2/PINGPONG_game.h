/*
 * PINGPONG_game.h
 *
 * Created: 13.11.2017 16:17:06
 *  Author: bendikss
 */ 


#ifndef PINGPONG_GAME_H_
#define PINGPONG_GAME_H_

#include <stdbool.h>
#include <stdint.h>
//TODO: store in fdjska 
//
//typedef struct game_parameters{
	//uint8_t score; //Make this larger? store in 
	//bool lose; //True if ball falls down
	//}game;


void PINGPONG_init(void);
void PINGPONG_play(void);
bool PINGPONG_lose(void);



#endif /* PINGPONG_GAME_H_ */