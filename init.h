#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


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




static Tetrino block[7] ={{
    START_X,START_Y,4,
    0,0,0,0,
    1,1,1,1,            //! Tvar I
    0,0,0,0,
    0,0,0,0,
    0,0,BOARD_S,BOARD_S},{
    START_X,START_Y,2,
    1,1,0,0,
    1,1,0,0,            //! Tvar O
    0,0,0,0,
    0,0,0,0,
    48,0,BOARD_S,BOARD_S},{
    START_X,START_Y,3,
    5,1,5,0,
    1,1,1,0,            //! Tvar T
    0,0,0,0,
    0,0,0,0,
    96,0,BOARD_S,BOARD_S},{
    START_X,START_Y,3,
    1,5,5,0,
    1,1,1,0,            //! Tvar J
    0,0,0,0,
    0,0,0,0,
    144,0,BOARD_S,BOARD_S},{
    START_X,START_Y,3,
    5,5,1,0,
    1,1,1,0,            //! Tvar L
    0,0,0,0,
    0,0,0,0,
    192,0,BOARD_S,BOARD_S},{
    START_X,START_Y,3,
    5,1,1,0,
    1,1,5,0,            //! Tvar S
    0,0,0,0,
    0,0,0,0,
    240,0,BOARD_S,BOARD_S},{
    START_X,START_Y,3,
    1,1,5,0,
    5,1,1,0,            //! Tvar Z
    0,0,0,0,
    0,0,0,0,
    288,0,BOARD_S,BOARD_S}
    },cur,nextblock;

static Gameboard board[4] = {{
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,        //! clear map
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,4,4,4,4,4,4,4,4,4,4,3},
        {
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,        //! t map
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,6,6,6,6,6,6,0,0,3,
        3,0,0,0,0,6,6,0,0,0,0,3,
        3,0,0,0,0,6,6,0,0,0,0,3,
        3,0,0,0,0,6,6,0,0,0,0,3,
        3,0,0,0,0,6,6,0,0,0,0,3,
        3,0,0,0,0,6,6,0,0,0,0,3,
        3,4,4,4,4,4,4,4,4,4,4,3},
        {
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,        //! c map
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,6,6,6,6,0,0,0,3,
        3,0,0,6,6,6,6,6,6,0,0,3,
        3,0,0,6,6,0,0,0,0,0,0,3,
        3,0,0,6,6,0,0,0,0,0,0,3,
        3,0,0,6,6,0,0,0,0,0,0,3,
        3,0,0,6,6,6,6,6,6,0,0,3,
        3,0,0,0,6,6,6,6,0,0,0,3,
        3,4,4,4,4,4,4,4,4,4,4,3},
        {
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,    //! upr map
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,3,
        3,6,0,0,6,6,6,6,6,6,6,3,
        3,6,0,0,6,6,0,6,6,0,6,3,
        3,6,0,0,6,6,6,6,6,6,6,3,
        3,6,0,0,6,6,0,0,6,6,0,3,
        3,6,0,0,6,6,0,0,6,0,6,3,
        3,0,6,6,0,6,0,0,6,0,6,3,
        3,4,4,4,4,4,4,4,4,4,4,3}
    },curmap;





void gameinit(SDL_Renderer *renderer,SDL_Texture *blocktexture,SDL_Texture *imgtexture, SDL_Texture *mainmenutexture,SDL_Texture *optionstexture,SDL_Texture *infotexture, SDL_Texture *losescreentexture, SDL_Texture *winscreentexture,SDL_Texture *nextblocktexture,int curnumber, int nextnumber,gamestate stateofgame);

void input(bool quit,gamestate stateofgame,float secondsElapsed,SDL_Rect scorerect,SDL_Rect linesrect,int mapnumber, float fallspeed);

void game(float secondsElapsed,float fallspeed,int mapnumber,gamestate stateofgame,int score, int linecounter,int nextnumber,char *scoretext);

void rendergame(SDL_Renderer *renderer,TTF_Font *font,SDL_Texture *scoretexture,SDL_Texture *linetexture,SDL_Texture *imgtexture,SDL_Texture *blocktexture,SDL_Texture *nextblocktexture,SDL_Rect scorerect, SDL_Rect linesrect,char *scoretext,char *linetext,int nextnumber,int score,int linecounter);

void rendermainmenu(SDL_Renderer *renderer,SDL_Texture *mainmenutexture);

void renderlosescreen(SDL_Renderer *renderer,SDL_Rect scorerect, SDL_Rect linesrect, SDL_Texture *losescreentexture, SDL_Texture *scoretexture,SDL_Texture *linetexture);

void renderwinscreen(SDL_Renderer *renderer,SDL_Rect scorerect, SDL_Rect linesrect, SDL_Texture *winscreentexture, SDL_Texture *scoretexture,SDL_Texture *linetexture);

void renderoptions(SDL_Renderer *renderer,TTF_Font *font,char *fallspeedtext,SDL_Texture *fallspeedtexture,SDL_Texture *optionstexture,float fallspeed);

void renderinfo(SDL_Renderer *renderer, SDL_Texture *infotexture);

void destroy(TTF_Font *font,SDL_Texture *nextblocktexture, SDL_Texture *blocktexture,SDL_Texture *imgtexture, SDL_Texture *scoretexture, SDL_Texture *linetexture,SDL_Texture *mainmenutexture, SDL_Texture *losescreentexture, SDL_Texture *optionstexture, SDL_Texture *infotexture,SDL_Texture *fallspeedtexture, SDL_Renderer *renderer, SDL_Window *window);

bool gameover(Gameboard *map);

bool gamewin(Gameboard *map,int mapnumber);


