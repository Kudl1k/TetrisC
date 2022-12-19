#include "define.h"



void rotate_block(Tetrino *block);
bool colision(Tetrino *block,Gameboard *board,int side);
bool isseatled(Tetrino *block, Gameboard *board);
void addseatledblock(Tetrino *block, Gameboard *board);
void getfirstcord(Tetrino *block);
int getlastcord(Tetrino *block);
void drawtetrino(int x, int y,SDL_Color color,SDL_Renderer *renderer);
void drawgrid(Gameboard *board,Tetrino *block,SDL_Renderer *renderer);
void grid_init(Tetrino *block,Gameboard *board);
void grid_reset(Gameboard *board);
bool fullline(Gameboard *board);
void clearline(Gameboard *board);
void movedowngrid(Gameboard *board);

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
    //* generace random block na startu
    srand(time(0));
    int blknumber = rand() % 7;
    
    float secondsElapsed = 0;


    cur = block[1];
    int gamestage = 1;
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        blknumber = rand() % 7;
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
                        rotate_block(&cur);
                        grid_reset(&board);
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
                    case SDLK_r:
                        cur = block[blknumber];
                }
            }
            
        }
        // if (secondsElapsed >1)
        // {
        //     cur.y += BOARD_S;       //! posunovac
        //     secondsElapsed = 0;
        // }
        
        if (isseatled(&cur,&board))
        {
            addseatledblock(&cur,&board);
            nextblock = block[1];
            cur = nextblock;
        }
        if (fullline(&board))
        {
            clearline(&board);
            movedowngrid(&board);
        }
        
        


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        grid_reset(&board);
        grid_init(&cur,&board);

        drawgrid(&board,&cur,renderer);

        SDL_RenderPresent(renderer);

        Uint64 end = SDL_GetPerformanceCounter();
        secondsElapsed = secondsElapsed + ( (end - start) / (float)SDL_GetPerformanceFrequency());
    }

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
}



bool colision(Tetrino *block,Gameboard *board,int side){
    getfirstcord(block);
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((block->shape[i][j] == 1 && board->grid[blk.y][blk.x + 1] == 3) && side == 1)
            {
                return true;
            }
            if ((block->shape[i][j] == 1 && board->grid[blk.y][blk.x - 1] == 3) && side == 2)
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
    getfirstcord(block);
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((block->shape[i][j] == 1 && board->grid[blk.y + 1][blk.x] == 3) || (block->shape[i][j] == 1 && board->grid[blk.y + 1][blk.x] == 2))
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

void addseatledblock(Tetrino *block, Gameboard *board){
    getfirstcord(block);
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


int getlastcord(Tetrino *block){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    int x =0;
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 3; j >= 0; i--)
        {
            if (block->shape[j][i] == 1 || block->shape[j][i] == 2)
            {
                return x = blk.x;
            }
            ++blk.x;
        }
        blk.x = block->x;
    }
    return 0;
}

void drawtetrino(int x, int y,SDL_Color color,SDL_Renderer *renderer){
    SDL_Rect rect = {x-1,y,BOARD_S,BOARD_S};
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,255);
    SDL_RenderFillRect(renderer,&rect);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawRect(renderer,&rect);
}

void drawgrid(Gameboard *board,Tetrino *block,SDL_Renderer *renderer){
    SDL_Rect grid = {0,0,0,0};
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            //printf("%d",board->grid[i][j]);
            if (board->grid[i][j] == 0) drawtetrino(grid.x,grid.y,Grey,renderer);
            if (board->grid[i][j] == 1) drawtetrino(grid.x,grid.y,block->color,renderer);
            if (board->grid[i][j] == 2) drawtetrino(grid.x,grid.y,LightGrey,renderer);
            grid.x += BOARD_S;
        }
        //printf("\n");
        grid.x = 0;
        grid.y += BOARD_S;
    }
    //printf("\n");
    
}

void grid_init(Tetrino *block,Gameboard *board){

    getfirstcord(block);
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1 && board->grid[blk.y][blk.x] == 0)
            {
                board->grid[blk.y][blk.x] = block->shape[i][j];
            }
            blk.x++;
        }
        blk.x = block->x;
        blk.y++;
    }
    
}

bool fullline(Gameboard *board){
    int flag = 0;
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            if (board->grid[i][j] == 2)continue;
            flag = 1;
        }
        if (flag == 1) return false;
    }
    printf("full line");
    return true;
}

void clearline(Gameboard *board){
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            board->grid[i][j] = 0;
        }
    }
}

void movedowngrid(Gameboard *board){
    for (int i = 19; i >= 0; i--)
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