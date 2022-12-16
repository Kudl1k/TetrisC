#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

//* Definice herního pole

#define BOARD_W 10
#define BOARD_H 20
#define BOARD_S 48

#define WINDOW_W BOARD_S*BOARD_W
#define WINDOW_H BOARD_S*BOARD_H

#define START_X 0
#define START_Y 0

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
    int width;
    int height;
    int orientation;    //* 0 - start, 1 - prvni cyklus, 2 - druhy cyklus, 3 - treti cyklus
    SDL_Color color;
}Tetrino;

Tetrino block[7] ={{
    START_X,START_Y,
    1,1,1,1,
    0,0,0,0,            //! Tvar I
    0,0,0,0,
    0,0,0,0,
    4,1,0,
    0,255,255},{
    START_X,START_Y,
    1,1,0,0,
    1,1,0,0,            //! Tvar O
    0,0,0,0,
    0,0,0,0,
    2,2,0,
    255,255,0},{
    START_X,START_Y,
    0,1,0,0,
    1,1,1,0,            //! Tvar T
    0,0,0,0,
    0,0,0,0,
    3,2,0,
    128,0,128},{
    START_X,START_Y,
    0,1,0,0,
    0,1,0,0,            //! Tvar J
    1,1,0,0,
    0,0,0,0,
    3,2,0,
    0,0,255},{
    START_X,START_Y,
    1,0,0,0,
    1,0,0,0,            //! Tvar L
    1,1,0,0,
    0,0,0,0,
    3,2,0,
    255,165,0},{
    START_X,START_Y,
    0,1,1,0,
    1,1,0,0,            //! Tvar S
    0,0,0,0,
    0,0,0,0,
    3,2,0,
    78,252,78},{
    START_X,START_Y,
    1,1,0,0,
    0,1,1,0,            //! Tvar Z
    0,0,0,0,
    0,0,0,0,
    3,2,0,
    255,0,0}
    },cur;