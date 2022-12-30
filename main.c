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


SDL_Color White = {255,255,255,255};
char scoretext[10000];
char linetext[1000];
char fallspeedtext[100];
int gamestate = 0; //* 0 = main menu, 1 = game, 2 = end screen, 3 = options, 4 = about , 5 = winscreen


bool quit = false;
SDL_Point mousepos;
const SDL_Rect startbox = {271,410,338,78};
const SDL_Rect optionsbox = {271,503,338,78};
const SDL_Rect infobox = {271,591,338,78};
const SDL_Rect exitbox = {271,680,338,78};
const SDL_Rect backbox = {271,680,338,78};
const SDL_Rect plusspeedbox = {623,318,36,36};
const SDL_Rect minspeedbox = {526,318,36,36};
const SDL_Rect speedtextbox = {574,318,36,36};

const SDL_Rect mapclearbox = {228,456,80,160};
const SDL_Rect maptbox = {342,456,80,160};
const SDL_Rect mapcbox = {457,456,80,160};
const SDL_Rect mapuprbox = {571,456,80,160};


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
SDL_Rect scorerect = {727,265,94,38};
SDL_Rect linesrect = {751,336,46,38};

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


//! drawing.h

//! grid.h


//! ...




int main()
{
    tetris();
    return 0;
}

//! game.h
void init(){
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("TETRIS - KUD0132", 50, 50, 880, 960, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

        TTF_Init();

    font = TTF_OpenFont("./src/retrogaming.ttf", 24);
    if (!font)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "TTF_OpenFont Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    
    

}

void gameinit(){
    blocktexture = IMG_LoadTexture(renderer,"./src/tetromino.png");
    imgtexture = IMG_LoadTexture(renderer,"./src/MENUS/gamemenu.png");
    mainmenu = IMG_LoadTexture(renderer,"./src/MENUS/mainmenu.png");
    options = IMG_LoadTexture(renderer,"./src/MENUS/optionsmenu.png");
    info = IMG_LoadTexture(renderer,"./src/MENUS/infomenu.png");
    losescreen = IMG_LoadTexture(renderer,"./src/MENUS/losemenu.png");
    winscreen = IMG_LoadTexture(renderer,"./src/MENUS/winmenu.png");

    nextblocktexture = IMG_LoadTexture(renderer,"./src/tetrominonextblock.png");

    curmap = board[0];
    srand(time(0));
    curnumber = rand() % 7;
    cur = block[curnumber];
    nextnumber = rand() % 7;
    nextblock = block[nextnumber];
}

void input(){
    while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&mousepos.x,&mousepos.y);
            } 
            if (gamestate == 1)
            {
                if (e.type == SDL_KEYDOWN)
                {
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        if(!colision(&cur,&curmap,3)){
                            rotate_block(&cur);
                        }
                        break;
                    case SDLK_DOWN:
                        if(!issettled(&cur,&curmap)) cur.y += 1;
                        break;
                    case SDLK_LEFT:
                        if(!colision(&cur, &curmap,2)) cur.x -= 1;
                        if (issettled(&cur,&curmap))
                        {
                            secondsElapsed = 0;
                        }
                        
                        break;
                    case SDLK_RIGHT:
                        if(!colision(&cur, &curmap,1)) cur.x += 1;
                        if (issettled(&cur,&curmap))
                        {
                            secondsElapsed = 0;
                        }
                        break;
                    case SDLK_SPACE:
                        harddrop(&cur,&curmap);
                        break;
                    case SDLK_ESCAPE:
                        gamestate = 0;
                        break;
                    }
                }
            }
            if (gamestate == 0)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&startbox)) {
                            gamestate = 1;
                            scorerect.x = 727;
                            scorerect.y = 265;
                            scorerect.w = 94;
                            scorerect.h = 38;
                            linesrect.x = 751;
                            linesrect.y = 336;
                            linesrect.w = 46;
                            linesrect.h = 38;
                            grid_reset(&curmap);
                        }
                        if (SDL_PointInRect(&mousepos,&optionsbox))
                        {
                            gamestate = 3;
                        }
                        if (SDL_PointInRect(&mousepos,&infobox))
                        {
                            gamestate = 4;
                        }
                        if (SDL_PointInRect(&mousepos,&exitbox))
                        {
                            quit = true;
                        }
                    }
                    
                }
            }
            if (gamestate == 2 || gamestate == 3  || gamestate == 4 || gamestate == 5)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&backbox)){
                            gamestate = 0;
                        }
                    }
                }     
            }
            if (gamestate == 3)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&plusspeedbox)){
                            if (fallspeed < 1) fallspeed += 0.1;
                        }
                        if (SDL_PointInRect(&mousepos,&minspeedbox))
                        {
                            if (fallspeed > 0.2) fallspeed -= 0.1;
                        }
                        if (SDL_PointInRect(&mousepos,&mapclearbox)){
                            mapnumber = 0;

                            }
                        if (SDL_PointInRect(&mousepos,&maptbox)){
                            mapnumber = 1;
                        }
                        if (SDL_PointInRect(&mousepos,&mapcbox)) mapnumber = 2;
                        if (SDL_PointInRect(&mousepos,&mapuprbox)) mapnumber = 3;
                    }
                }     
            }
        }
}

void game(){
        grid_reset(&curmap);

        if (secondsElapsed >fallspeed && (!issettled(&cur,&curmap)))
        {
            
            cur.y += 1;       //! posunovac
            secondsElapsed = 0;
        }
        
        grid_init(&cur,&curmap);

        if (issettled(&cur,&curmap))
        {
            if (gameover(&curmap)) {
                gamestate = 2;
            }
            if (gamewin(&curmap,mapnumber)) {
                gamestate = 5;
            }

            if(secondsElapsed > fallspeed){
                addseatledblock(&cur,&curmap,secondsElapsed);
                fullline(&curmap,&score,&linecounter);
                cur = nextblock;
                srand(time(0));
                nextnumber = rand() % 7;
                nextblock = block[nextnumber];
                sprintf(scoretext,"%d",score);
            }
        }
}


void rendergame(){
    scoresurface = TTF_RenderText_Solid(font,  scoretext, White);
    scoretexture = SDL_CreateTextureFromSurface(renderer, scoresurface);
    SDL_FreeSurface(scoresurface);
    sprintf(scoretext,"%d",score);
    linesurface = TTF_RenderText_Solid(font,  linetext, White);
    linetexture = SDL_CreateTextureFromSurface(renderer, linesurface);
    SDL_FreeSurface(linesurface);
    sprintf(linetext,"%d",linecounter);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,imgtexture,NULL,NULL);
    SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
    SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
    drawgrid(&curmap,&cur,renderer,blocktexture);
    drawnextblock(nextnumber,renderer,nextblocktexture);
    SDL_RenderPresent(renderer);
}

void rendermainmenu(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,mainmenu,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void renderlosescreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    scorerect.x = linesrect.x = 472;
    scorerect.y = 461;
    scorerect.w = linesrect.w = 116;
    scorerect.h = linesrect.h = 50;
    linesrect.y = 516;
    SDL_RenderCopy(renderer,losescreen,NULL,NULL);
    SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
    SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
    SDL_RenderPresent(renderer);
}

void renderwinscreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    scorerect.x = linesrect.x = 472;
    scorerect.y = 461;
    scorerect.w = linesrect.w = 116;
    scorerect.h = linesrect.h = 50;
    linesrect.y = 516;
    SDL_RenderCopy(renderer,winscreen,NULL,NULL);
    SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
    SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
    SDL_RenderPresent(renderer);
}

void renderoptions(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    fallspeedsurface = TTF_RenderText_Solid(font,  fallspeedtext, White);
    fallspeedtexture = SDL_CreateTextureFromSurface(renderer, fallspeedsurface);
    SDL_FreeSurface(fallspeedsurface);
    sprintf(fallspeedtext,"%0.1f",fallspeed);

    SDL_RenderCopy(renderer,options,NULL,NULL);
    SDL_RenderCopy(renderer,fallspeedtexture,NULL,&speedtextbox);

    
    SDL_RenderPresent(renderer);
}

void renderinfo(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,info,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void destroy(){
    TTF_CloseFont(font);
    SDL_DestroyTexture(nextblocktexture);
    SDL_DestroyTexture(blocktexture);
    SDL_DestroyTexture(imgtexture);
    SDL_DestroyTexture(scoretexture);
    SDL_DestroyTexture(linetexture);
    SDL_DestroyTexture(mainmenu);
    SDL_DestroyTexture(losescreen);
    SDL_DestroyTexture(options);
    SDL_DestroyTexture(info);
    SDL_DestroyTexture(fallspeedtexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void tetris(){
    init();
    gameinit();
    while (!quit)
    {
        input();
        if (gamestate == 0){
            rendermainmenu();
        }

        if (gamestate == 2)
        {
            curmap = board[0];
            renderlosescreen();
        }
        
        if (gamestate == 3)
        {
            renderoptions();
            curmap = board[mapnumber];

        }
        if (gamestate == 4)
        {
            renderinfo();
        }
        if (gamestate == 5)
        {
            renderwinscreen();
        }
        
        
        if(gamestate == 1){
            Uint64 start = SDL_GetPerformanceCounter();
            game();
            rendergame();
            Uint64 end = SDL_GetPerformanceCounter();
            secondsElapsed = secondsElapsed + ( (end - start) / (float)SDL_GetPerformanceFrequency());
        }
        
    }
    destroy();
}

//! movement.h


//! grid.h


