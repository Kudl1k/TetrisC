#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>

#define RUNNING 1
#define SEATLED 2


//* Definice herního pole

#define BOARD_W 10
#define BOARD_H 20
#define BOARD_S 48

#define WINDOW_W BOARD_S*BOARD_W
#define WINDOW_H BOARD_S*BOARD_H

#define START_X 1
#define START_Y 0

//* Definice barev
SDL_Rect Grey = {336,0,BOARD_S,BOARD_S};
SDL_Rect LightGrey = {384,0,BOARD_S,BOARD_S};

//* Definice Tetrinů
typedef struct
{
    int x;
    int y;
    int shape[4][4];
    SDL_Rect img;
}Tetrino;

typedef struct
{
    int grid[BOARD_H+1][BOARD_W+2];
}Gameboard;

Gameboard board = {
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
        3,4,4,4,4,4,4,4,4,4,4,3
    };

Tetrino block[7] ={{
    START_X,START_Y,
    0,0,0,0,
    1,1,1,1,            //! Tvar I
    0,0,0,0,
    0,0,0,0,
    0,0,BOARD_S,BOARD_S},{
    START_X,START_Y,
    1,1,0,0,
    1,1,0,0,            //! Tvar O
    0,0,0,0,
    0,0,0,0,
    48,0,BOARD_S,BOARD_S},{
    START_X,START_Y,
    2,1,2,0,
    1,1,1,0,            //! Tvar T
    0,0,0,0,
    0,0,0,0,
    96,0,BOARD_S,BOARD_S},{
    START_X,START_Y,
    2,1,0,0,
    2,1,0,0,            //! Tvar J
    1,1,0,0,
    0,0,0,0,
    144,0,BOARD_S,BOARD_S},{
    START_X,START_Y,
    1,2,0,0,
    1,2,0,0,            //! Tvar L
    1,1,0,0,
    0,0,0,0,
    192,0,BOARD_S,BOARD_S},{
    START_X,START_Y,
    2,1,1,0,
    1,1,2,0,            //! Tvar S
    0,0,0,0,
    0,0,0,0,
    240,0,BOARD_S,BOARD_S},{
    START_X,START_Y,
    1,1,2,0,
    2,1,1,0,            //! Tvar Z
    0,0,0,0,
    0,0,0,0,
    288,0,BOARD_S,BOARD_S}
    },cur,nextblock;