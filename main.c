#include "define.h"


//! game
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
bool quit = false;
SDL_Point mousepos;
const SDL_Rect startbox = {239,364,400,93};
const SDL_Rect optionsbox = {239,480,400,93};
const SDL_Rect infobox = {239,595,400,93};
const SDL_Rect exitbox = {239,710,400,93};
const SDL_Rect backbox = {239,710,400,93};
const SDL_Rect plusspeedbox = {576,393,36,36};
const SDL_Rect minspeedbox = {478,393,36,36};
const SDL_Rect speedtextbox = {528,393,36,36};



SDL_Texture *imgtexture;
SDL_Texture *blocktexture;
SDL_Texture *mainmenu;
SDL_Texture *losescreen;
SDL_Texture *options;
SDL_Texture *info;
SDL_Texture *fallspeedtexture;
SDL_Surface *fallspeedsurface;


SDL_Rect wall = {0,0,880,960};
SDL_Rect scorerect = {727,265,94,38};
SDL_Rect linesrect = {751,336,46,38};


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
void renderinfo();
void renderoptions();

//! movement.h
void rotate_block(Tetrino *block);
bool colision(Tetrino *block,Gameboard *board,int side);
bool issettled(Tetrino *block, Gameboard *board);
void addseatledblock(Tetrino *block, Gameboard *board,float fallspeed);
//! drawing.h
void drawnextblock(Tetrino *block,SDL_Renderer *renderer,SDL_Texture *blocktexture);
void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer);
void drawgrid(Gameboard *board,Tetrino *block,SDL_Renderer *renderer, SDL_Texture *blocktexture);
//! grid.h
void grid_init(Tetrino *block,Gameboard *board);
void grid_reset(Gameboard *board);
void fullline(Gameboard *board,int *score,int *linecounter);
void clearline(Gameboard *board,int line);
void movedowngrid(Gameboard *board,int line);

//! ...
bool gameover(Gameboard *board);



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
    imgtexture = IMG_LoadTexture(renderer,"./src/gamegraphics.png");
    mainmenu = IMG_LoadTexture(renderer,"./src/mainmenu.png");
    options = IMG_LoadTexture(renderer,"./src/options.png");
    info = IMG_LoadTexture(renderer,"./src/info.png");
    losescreen = IMG_LoadTexture(renderer,"./src/losescreen.png");

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
                        if(!colision(&cur,&board,3)){
                            rotate_block(&cur);
                        }
                        break;
                    case SDLK_DOWN:
                        if(!issettled(&cur,&board)) cur.y += 1;
                        break;
                    case SDLK_LEFT:
                        if(!colision(&cur, &board,2)) cur.x -= 1;
                        break;
                    case SDLK_RIGHT:
                        if(!colision(&cur, &board,1)) cur.x += 1;
                        break;
                    case SDLK_ESCAPE:
                        gamestate = 0;
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
                            grid_reset(&board);
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
                            printf("proslo");
                            quit = true;
                        }
                    }
                    
                }
            }
            if (gamestate == 2 || gamestate == 3  || gamestate == 4)
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
                        printf("%f\n",fallspeed);
                    }
                }     
            }
        }
}

void game(){
        grid_reset(&board);

        if (secondsElapsed >fallspeed)
        {
            
            cur.y += 1;       //! posunovac
            secondsElapsed = 0;
        }
        
        grid_init(&cur,&board);

        if (issettled(&cur,&board))
        {
            if (gameover(&board)) {
                gamestate = 2;
                grid_reset(&board);
            }
            addseatledblock(&cur,&board,secondsElapsed);
            fullline(&board,&score,&linecounter);
            cur = nextblock;
            srand(time(0));
            nextnumber = rand() % 7;
            nextblock = block[nextnumber];
            sprintf(scoretext,"%d",score);
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
    drawgrid(&board,&cur,renderer,blocktexture);
    drawnextblock(&nextblock,renderer,blocktexture);
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
    scorerect.x = linesrect.x = 473;
    scorerect.y = 522;
    scorerect.w = linesrect.w = 120;
    scorerect.h = linesrect.h = 40;
    linesrect.y = 600;
    SDL_RenderCopy(renderer,losescreen,NULL,NULL);
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
            renderlosescreen();
        }
        
        if (gamestate == 3)
        {
            renderoptions();
        }
        if (gamestate == 4)
        {
            renderinfo();
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
void rotate_block(Tetrino *block){
    int N = 4;
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
            int temp = block->shape[i][j];
            block->shape[i][j] = block->shape[N - 1 - j][i];
            block->shape[N - 1 - j][i] = block->shape[N - 1 - i][N - 1 - j];
            block->shape[N - 1 - i][N - 1 - j] = block->shape[j][N - 1 - i];
            block->shape[j][N - 1 - i] = temp;
        }
    }
}

bool colision(Tetrino *block,Gameboard *board,int side){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (((block->shape[i][j] == 1 && board->grid[blk.y][blk.x + 1] == 3) || (block->shape[i][j] == 1 && board->grid[blk.y][blk.x + 1] == 2))  && side == 1)
            {
                return true;
            }
            if (((block->shape[i][j] == 1 && board->grid[blk.y][blk.x - 1] == 3) || (block->shape[i][j] == 1 && board->grid[blk.y][blk.x - 1] == 2) )&& side == 2)
            {
                return true;
            }
            if ((board->grid[blk.y][blk.x - 1] == 3 || board->grid[blk.y][blk.x + 1] == 3) && side == 3)
            {
                return true;
            }
            
            
            blk.x++;
        }
        blk.x = block->x;
        blk.y++;
    }
    return false;
}


bool issettled(Tetrino *block, Gameboard *board){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((block->shape[i][j] == 1 && board->grid[blk.y + 1][blk.x] == 4) || (block->shape[i][j] == 1 && board->grid[blk.y + 1][blk.x] == 2))
            {
                return true;
            } 
            blk.x++;
        }
        blk.x = block->x;
        blk.y++;
    }
    return false;
}

void addseatledblock(Tetrino *block, Gameboard *board,float fallspeed){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1)
            {
                board->grid[blk.y][blk.x] = 2;
            } 
            blk.x++;
        }
        blk.x = block->x;
        blk.y++;
    }


}


//! grid.h


void grid_init(Tetrino *block,Gameboard *board){    
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++,blk.y++)
    {
        for (int j = 0; j < 4; j++,blk.x++)
        {
            if (block->shape[i][j] == 1)
            {   
                board->grid[blk.y][blk.x] = block->shape[i][j];
            }
        }
        blk.x = block->x;
    }
}

void fullline(Gameboard *board,int *score,int *linecounter){
    int flag = 0;
    int j;
    for (int i = 19; i > 0; i--)
    {
        for (j = 1; j <= BOARD_W; j++){
            if (board->grid[i][j] != 2)
            {
                flag = 0;
                break;
            }
            flag = 1;
        }
        if (flag == 1) {
            (*score) += 100;
            (*linecounter) += 1;
            clearline(board,i);
            movedowngrid(board,i);
        }
    }
}

void clearline(Gameboard *board,int line){
    for (int j = 1; j <= BOARD_W; j++)
    {
        board->grid[line][j] = 0;
    }

}

void movedowngrid(Gameboard *board,int line){
    for (int i = line; i > 0; i--)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            board->grid[i][j] = board->grid[i-1][j];
        }
    }
}

void grid_reset(Gameboard *board){
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++){
            if (board->grid[i][j] == 1)
            {
                board->grid[i][j] = 0;
            }
        }
    }
}

void drawnextblock(Tetrino *block,SDL_Renderer *renderer,SDL_Texture *blocktexture){
    SDL_Rect next;
    next.x = 525;
    next.y = 676;
    next.h = next.w = 48;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j]==1){
                SDL_RenderCopy(renderer,blocktexture,&block->img,&next);
            }
            next.x += next.w;
        }
        next.x = 525;
        next.y += next.w;
    }
}

void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer){
    SDL_Rect rect = {x-1,y,BOARD_S,BOARD_S};
    SDL_RenderCopy(renderer,texture,&img,&rect);
}

void drawgrid(Gameboard *board,Tetrino *block,SDL_Renderer *renderer,SDL_Texture *blocktexture){
    SDL_Rect grid = {0,0,0,0};
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            if (board->grid[i][j] == 0) drawtetrino(grid.x,grid.y,blocktexture,Grey,renderer);
            if (board->grid[i][j] == 1) drawtetrino(grid.x,grid.y,blocktexture,block->img,renderer);
            if (board->grid[i][j] == 2) drawtetrino(grid.x,grid.y,blocktexture,LightGrey,renderer);
            grid.x += BOARD_S;
        }
        grid.x = 0;
        grid.y += BOARD_S;
    }    
}

//! ...


bool gameover(Gameboard *board){
    for (int j = 1; j <= BOARD_W; j++)
    {
        if (board->grid[3][j] == 2)
        {
            return true;
        }
    }
    return false;
}