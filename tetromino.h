#pragma once

#include "define.h"

typedef struct
{
    int x;
    int y;
    int size;
    int shape[4][4];
    SDL_Rect img;
}Tetrino;

Tetrino block[7] ={{
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