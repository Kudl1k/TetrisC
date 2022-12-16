#include "define.h"


void draw_block(Tetrino *block,SDL_Renderer *renderer);
void rotate_block(Tetrino *block);
int colision(Tetrino *block,SDL_Renderer *renderer);


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
                        cur.y += BOARD_S;
                        break;
                    case SDLK_LEFT:
                        cur.x -= BOARD_S;
                        break;
                    case SDLK_RIGHT:
                        cur.x += BOARD_S;
                }
            }
            
        }
        if (secondsElapsed >1)
        {
            cur.y += BOARD_S;       //! posunovac
            secondsElapsed = 0;
        }
        

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
    blk.x = block->x;
    blk.y = block->y;
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
                SDL_SetRenderDrawColor(renderer,block->color.r,block->color.g,block->color.b,255);
                SDL_RenderFillRect(renderer,&blk);
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_RenderDrawRect(renderer,&outline);
            }
            blk.x += BOARD_S;
            outline.x = blk.x;
        }
        blk.x = block->x;
        blk.y += BOARD_S;
        outline.x = blk.x;
        outline.y = blk.y;
    }
}

int colision(Tetrino *block,SDL_Renderer *renderer){
    SDL_Rect blk;
    printf("block.x: %d \n",block->x);
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            
            blk.x += BOARD_S;
        }
        blk.x = block->x;
    }
    return 0;
}


