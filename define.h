#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

//* Definice herního pole

#define BOARD_W 10
#define BOARD_H 20
#define BOARD_S 48

#define WINDOW_W BOARD_S*BOARD_W
#define WINDOW_H BOARD_S*BOARD_H

#define START_X BOARD_S*4
#define START_Y BOARD_S*2

//* Definice barev
SDL_Color Red = {255,0,0};
SDL_Color Green = {0,255,0};
SDL_Color Blue = {0,0,255};


//* Definice Tetrinů
typedef struct
{
    int x;
    int y;
    int shape[4][4];
}Tetrino;

Tetrino block[7] ={{
    START_X,START_Y,
    1,1,1,1,
    0,0,0,0,            //! Tvar I
    0,0,0,0,
    0,0,0,0},{
    START_X,START_Y,
    0,0,0,0,
    0,1,1,0,            //! Tvar O
    0,1,1,0,
    0,0,0,0},{
    START_X,START_Y,
    0,1,0,0,
    1,1,1,0,            //! Tvar T
    0,0,0,0,
    0,0,0,0},{
    START_X,START_Y,
    0,1,0,0,
    0,1,0,0,            //! Tvar J
    1,1,0,0,
    0,0,0,0},{
    START_X,START_Y,
    0,1,0,0,
    0,1,0,0,            //! Tvar L
    0,1,1,0,
    0,0,0,0},{
    START_X,START_Y,
    0,1,1,0,
    1,1,0,0,            //! Tvar S
    0,0,0,0,
    0,0,0,0},{
    START_X,START_Y,
    1,1,0,0,
    0,1,1,0,            //! Tvar Z
    0,0,0,0,
    0,0,0,0}
    },cur;