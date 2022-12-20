#include "define.h"



void rotate_block(Tetrino *block);
bool colision(Tetrino *block,Gameboard *board,int side);
bool isseatled(Tetrino *block, Gameboard *board);
void addseatledblock(Tetrino *block, Gameboard *board,float timer);
void getfirstcord(Tetrino *block);
void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer);
void drawgrid(Gameboard *board,Tetrino *block,SDL_Renderer *renderer, SDL_Texture *blocktexture);
void grid_init(Tetrino *block,Gameboard *board);
void grid_reset(Gameboard *board);
void fullline(Gameboard *board,int *score,int *linecounter);
void clearline(Gameboard *board,int line);
void movedowngrid(Gameboard *board,int line);
void drawnextblock(Tetrino *block,SDL_Renderer *renderer,SDL_Texture *blocktexture);
bool gameover(Gameboard *board);


int main()
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("TETRIS - KUD0132", 50, 50, WINDOW_W+400, WINDOW_H, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

        TTF_Init();

    TTF_Font* font = TTF_OpenFont("./src/retrogaming.ttf", 24);
    if (!font)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "TTF_OpenFont Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_Texture *imgtexture = IMG_LoadTexture(renderer,"./src/gameimg.png");
    SDL_Texture *blocktexture = IMG_LoadTexture(renderer,"./src/blocks.png");
    SDL_Rect wall = {0,0,880,960};
    SDL_Rect scorerect = {691,193,128,40};
    SDL_Rect linesrect = {691,261,128,40};

    //* generace random block na startu
    srand(time(0));
    int curnumber = rand() % 7;
    float secondsElapsed = 0;
    int nextnumber = rand() % 7;

    int linecounter = 0;
    int score = 0;
    



    cur = block[curnumber];
    nextblock = block[nextnumber];
    int gamestage = 1;
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        SDL_Surface* scoresurface = TTF_RenderText_Solid(font,  scoretext, White);
        SDL_Texture* scoretexture = SDL_CreateTextureFromSurface(renderer, scoresurface);
        SDL_FreeSurface(scoresurface);
        sprintf(scoretext,"%d",score);

        Uint64 start = SDL_GetPerformanceCounter();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        if(!colision(&cur,&board,3)) rotate_block(&cur);
                        break;
                    case SDLK_DOWN:
                        if(!isseatled(&cur,&board)) cur.y += 1;
                        break;
                    case SDLK_LEFT:
                        if(!colision(&cur, &board,2)) cur.x -= 1;
                        break;
                    case SDLK_RIGHT:
                        if(!colision(&cur, &board,1)) cur.x += 1;
                        break;
                }
            }
            
        }
        getfirstcord(block);


        if (secondsElapsed >0.5)
        {
            cur.y += 1;       //! posunovac
            secondsElapsed = 0;
        }
        
        grid_reset(&board);
        grid_init(&cur,&board);

        if (isseatled(&cur,&board))
        {
            if (gameover(&board)) quit = true;
            addseatledblock(&cur,&board,secondsElapsed);
            fullline(&board,&score,&linecounter);
            srand(time(0));
            cur = nextblock;
            nextnumber = rand() % 7;
            nextblock = block[nextnumber];
            sprintf(scoretext,"%d",score);

        }
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,imgtexture,NULL,NULL);
        SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
        


        drawgrid(&board,&cur,renderer,blocktexture);
        drawnextblock(&nextblock,renderer,blocktexture);
        SDL_RenderPresent(renderer);

        Uint64 end = SDL_GetPerformanceCounter();
        secondsElapsed = secondsElapsed + ( (end - start) / (float)SDL_GetPerformanceFrequency());
    }
    TTF_CloseFont(font);
    SDL_DestroyTexture(blocktexture);
    SDL_DestroyTexture(imgtexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//! pomocne funkce



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
    printf("x1: %d y1: %d\n",block->x,block->y);
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


bool isseatled(Tetrino *block, Gameboard *board){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((block->shape[i][j] == 1 && board->grid[blk.y + 1][blk.x] == 4) || (block->shape[i][j] == 1 && board->grid[blk.y + 1][blk.x] == 2))
            {
                //printf("x: %d y: %d\n",block->x,block->y);
                return true;
            } 
            blk.x++;
        }
        blk.x = block->x;
        blk.y++;
    }
    return false;
}

void addseatledblock(Tetrino *block, Gameboard *board,float timer){
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


void getfirstcord(Tetrino *block){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    int flag = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1 || block->shape[i][j] == 2 )
            {
                block->x = blk.x;
                block->y = blk.y;
                flag = 1;
                break;
            }
            ++blk.x;
        }
        if (flag == 1)
        {
            break;
        }
        blk.y++;
        blk.x = block->x;
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
    for (int i = 19; i > 0; i--)
    {
        for (int j = 1; j <= BOARD_W; j++){
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
    next.x = 600;
    next.y = 480;
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
        next.x = 600;
        next.y += next.w;
    }
}

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