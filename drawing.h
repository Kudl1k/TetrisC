#pragma once

#include "tetromino.h"
#include "gameboard.h"
#include <stdio.h>


void drawnextblock(int blknumber,SDL_Renderer *renderer,SDL_Texture *nextblocks);
void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer);
void drawgrid(Gameboard *map,Tetrino *block,SDL_Renderer *renderer, SDL_Texture *blocktexture);


