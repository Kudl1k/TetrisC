#include "define.h"


void draw_block(Tetrino *block,SDL_Renderer *renderer);
void rotate_block(Tetrino *block);
int colision(Tetrino *block,gboard Gameboard);
int getfirstcord(Tetrino *block);
void drawtetrino(int x, int y, int w, int h, SDL_Color color,SDL_Renderer *renderer);

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("TETRIS - KUD0132", 50, 50, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
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


    cur = block[blknumber];


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
                        break;
                    case SDLK_DOWN:
                        cur.y += 1;
                        break;
                    case SDLK_LEFT:
                        if(colision(&cur,Gameboard) == 0) cur.x -= 1;
                        break;
                    case SDLK_RIGHT:
                        cur.x += 1;
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
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_block(&cur,renderer);

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


void draw_block(Tetrino *block,SDL_Renderer *renderer){
    SDL_Rect blk;
    blk.w = blk.h = BOARD_S-2;
    blk.x = block->x * BOARD_S;
    blk.y = block->y * BOARD_S;
    SDL_Rect outline;
    outline.w = outline.h = BOARD_S;
    outline.x = blk.x;
    outline.y = blk.y;
    int flag = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1)
            {
                drawtetrino(blk.x, blk.y, blk.w, blk.h,block->color,renderer);
            }
            blk.x += BOARD_S;
            outline.x = blk.x;
        }
        blk.x = block->x * BOARD_S;
        blk.y += BOARD_S;
        outline.x = blk.x;
        outline.y = blk.y;
    }
}

int colision(Tetrino *block,gboard Gameboard){
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            
        }
        
    }
    
    return 0;
}

int getfirstcord(Tetrino *block){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    int x =0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1 || block->shape[i][j] == 2 )
            {
                return x = blk.x;
            }
            ++blk.x;
        }
        blk.x = block->x;
    }
    return 0;
}

void drawtetrino(int x, int y, int w, int h, SDL_Color color,SDL_Renderer *renderer){
    SDL_Rect rect = {x,y,w-1,h-1};
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,255);
    SDL_RenderFillRect(renderer,&rect);
    SDL_Rect outline = {x,y,w,h};
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawRect(renderer,&outline);
}