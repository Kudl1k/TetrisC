#pragma once

#include "tetromino.h"
#include "gameboard.h"

#include <stdbool.h>

void rotate_block(Tetrino *block);
bool colision(Tetrino *block,Gameboard *map,int side);
void harddrop(Tetrino *block, Gameboard *map);
bool issettled(Tetrino *block, Gameboard *map);
void addseatledblock(Tetrino *block, Gameboard *map,float fallspeed);