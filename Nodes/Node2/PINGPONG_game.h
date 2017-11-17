/*
 * PINGPONG_game.h
 * 
 * Module for playing the pingpong game in Node 2 made in TTK4155 - Embedded and Industrial computer systems design.
 * 
 * Created: 13.11.2017 16:17:06
 *  Author: Aleksander Asp, Alexander Johansen, Bendik Standal
 */ 


#ifndef PINGPONG_GAME_H_
#define PINGPONG_GAME_H_

#include <stdbool.h>
#include <stdint.h>

/*This initializes the hardware and software for playing the pingpong game. In its current state, the initial position 
of the motor will be decided  by where it was when the last game was lost.*/
void PINGPONG_init(void);
void PINGPONG_play(void);


#endif /* PINGPONG_GAME_H_ */
