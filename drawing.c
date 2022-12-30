#include "drawing.h"


void drawnextblock(int blknumber,SDL_Renderer *renderer,SDL_Texture *nextblocks){
    SDL_Rect next;
    next.x = 589;
    next.y = 577;
    next.h = next.w = 192;

    SDL_Rect block;
    next.x = next.y = 0;
    next.w = next.h = 192;

    if (blknumber == 0) {
        block.x = 0;
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        }
    if (blknumber == 1) {
        block.x = 192;
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        }
    if (blknumber == 2) {
        block.x = 384;
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        }
    if (blknumber == 3) {
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        block.x = 576;
        }
    if (blknumber == 4) {
        block.x = 768;
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        }
    if (blknumber == 5) {
        block.x = 960;
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        }
    if (blknumber == 6) {
        block.x = 1080;
        SDL_RenderCopy(renderer,nextblocks,&block,&next);
        }
}

void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer){
    SDL_Rect rect = {x-1,y,BOARD_S,BOARD_S};
    SDL_RenderCopy(renderer,texture,&img,&rect);
}

void drawgrid(Gameboard *map,Tetrino *block,SDL_Renderer *renderer,SDL_Texture *blocktexture){
    SDL_Rect Grey = {336,0,BOARD_S,BOARD_S};
    SDL_Rect LightGrey = {384,0,BOARD_S,BOARD_S};
    SDL_Rect Pink = {432,0,BOARD_S,BOARD_S};
    SDL_Rect grid = {0,0,0,0};
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            if (map->grid[i][j] == 0) drawtetrino(grid.x,grid.y,blocktexture,Grey,renderer);
            if (map->grid[i][j] == 1) drawtetrino(grid.x,grid.y,blocktexture,block->img,renderer);
            if (map->grid[i][j] == 2) drawtetrino(grid.x,grid.y,blocktexture,LightGrey,renderer);
            if (map->grid[i][j] == 6) drawtetrino(grid.x,grid.y,blocktexture,Pink,renderer);
            grid.x += BOARD_S;
        }
        grid.x = 0;
        grid.y += BOARD_S;
    }    
}