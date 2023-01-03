#pragma once



#include "gameboard.h"
#include "tetromino.h"
#include "drawing.h"
#include "grid.h"
#include "update.h"
#include <string.h>


typedef enum{
    MAINMENU,
    GAME,
    LOSE,
    WIN,
    OPTIONS,
    ABOUT
}gamestate;



void rendermainmenu(SDL_Renderer *renderer,SDL_Texture *mainmenutexture);

void renderlosescreen(SDL_Renderer *renderer,SDL_Rect scorerect, SDL_Rect linesrect, SDL_Texture *losescreentexture, SDL_Texture *scoretexture,SDL_Texture *linetexture);

void renderwinscreen(SDL_Renderer *renderer,SDL_Rect scorerect, SDL_Rect linesrect, SDL_Texture *winscreentexture, SDL_Texture *scoretexture,SDL_Texture *linetexture);

void renderoptions(SDL_Renderer *renderer,TTF_Font *font,char *fallspeedtext,SDL_Texture *fallspeedtexture,SDL_Texture *optionstexture,float fallspeed);

void renderinfo(SDL_Renderer *renderer, SDL_Texture *infotexture);

void destroy(TTF_Font *font,SDL_Texture *nextblocktexture, SDL_Texture *blocktexture,SDL_Texture *imgtexture, SDL_Texture *scoretexture, SDL_Texture *linetexture,SDL_Texture *mainmenutexture, SDL_Texture *losescreentexture, SDL_Texture *optionstexture, SDL_Texture *infotexture,SDL_Texture *fallspeedtexture, SDL_Renderer *renderer, SDL_Window *window);

bool gameover(Gameboard *map);

bool gamewin(Gameboard *map,int mapnumber);


