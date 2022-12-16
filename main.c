#include "define.h"


void draw_block(Tetrino *block,SDL_Renderer *renderer);
void rotate_block(Tetrino *block);
int check_border(Tetrino *block);


SDL_Rect border = {0,0,WINDOW_W,WINDOW_H};


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


    float secondsElapsed = 0;


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
                        rotate_block(&block[4]);
                        break;
                    case SDLK_DOWN:
                        block[4].y += BOARD_S;
                        break;
                    case SDLK_LEFT:
                        if(check_border(&block[4]) == 0) block[4].x -= BOARD_S;
                        break;
                    case SDLK_RIGHT:
                        block[4].x += BOARD_S;
                }
            }
            
        }
        if (secondsElapsed >1)
        {
            block[4].y += BOARD_S;
            secondsElapsed = 0;
        }
        




        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_block(&block[4],renderer);

        SDL_RenderPresent(renderer);

        Uint64 end = SDL_GetPerformanceCounter();
        secondsElapsed = secondsElapsed + ( (end - start) / (float)SDL_GetPerformanceFrequency());
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


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
    blk.w = blk.h = BOARD_S;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1)
            {
                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                SDL_RenderFillRect(renderer,&blk);
            }
            blk.x += BOARD_S;
        }
        blk.x = block->x;
        blk.y += BOARD_S;
    }
}

int check_border(Tetrino *block){
    SDL_Rect tetr;
    tetr.x = block->x;
    tetr.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; i++)
        {
            printf("%d",block[4].shape[i][j]);
            tetr.x += BOARD_S;
        }
        tetr.x = block->x;
        tetr.y += BOARD_S;
    }
    return 0;
}