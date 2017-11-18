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

/*Game function that reads the IR-sensor and utilizes a digital low pass filter for determining
if the game is lost, then controls the physical components based on the latest received CAN gamecontrol message.*/
void PINGPONG_play();

void PINGPONG_difficulty(uint8_t difficulty);

#endif /* PINGPONG_GAME_H_ */
