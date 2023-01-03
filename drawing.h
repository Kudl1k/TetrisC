#pragma once

#include "tetromino.h"
#include "gameboard.h"
#include <stdio.h>

int drawnextblock(int blknumber);
void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer);
void drawgrid(Gameboard *map,Tetromino *block,SDL_Renderer *renderer, SDL_Texture *blocktexture);


