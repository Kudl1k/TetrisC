#pragma once

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

void init();
void gameinit();
void input();
void game();
void rendergame();
void destroy();
void tetris();
void rendermainmenu();
void renderlosescreen();
void renderwinscreen();
void renderinfo();
void renderoptions();