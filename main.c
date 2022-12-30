#include "define.h"
#include "tetromino.h"
#include "gameboard.h"
#include "update.h"
#include "drawing.h"
#include "grid.h"


//! game
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;





bool quit = false;





SDL_Texture *imgtexture;
SDL_Texture *blocktexture;
SDL_Texture *mainmenu;
SDL_Texture *losescreen;
SDL_Texture *winscreen;
SDL_Texture *options;
SDL_Texture *info;
SDL_Texture *fallspeedtexture;
SDL_Surface *fallspeedsurface;

SDL_Texture *nextblocktexture;



SDL_Rect wall = {0,0,880,960};


int mapnumber = 0;
int curnumber = 0;
int nextnumber = 0;
float secondsElapsed = 0;
float fallspeed = 0.5;
int linecounter = 0;
int score = 0;
SDL_Event e;

SDL_Surface* scoresurface;
SDL_Texture* scoretexture;
SDL_Surface* linesurface;
SDL_Texture* linetexture;



//! game.h



//! drawing.h

//! grid.h


//! ...




int main()
{
    tetris();
    return 0;
}

//! game.h
