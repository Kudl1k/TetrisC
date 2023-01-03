#pragma once

#include "tetromino.h"
#include "gameboard.h"

#include <stdbool.h>

void rotate_block(Tetromino *block);
bool colision(Tetromino *block,Gameboard *map,int side);
void harddrop(Tetromino *block, Gameboard *map);
bool issettled(Tetromino *block, Gameboard *map);
void addseatledblock(Tetromino *block, Gameboard *map,float fallspeed);