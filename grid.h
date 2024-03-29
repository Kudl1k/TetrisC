#pragma once

#include <stdbool.h>
#include "tetromino.h"
#include "gameboard.h"

void grid_init(Tetromino *block,Gameboard *map);
void grid_reset(Gameboard *map);
void fullline(Gameboard *map,int *score,int *linecounter);
void clearline(Gameboard *map,int line);
void movedowngrid(Gameboard *map,int line);


