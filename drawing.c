#include "drawing.h"


int drawnextblock(int blknumber){
    if (blknumber == 0) {
        return 0;
        }
    if (blknumber == 1) {
        return 192;
        }
    if (blknumber == 2) {
        return 384;
        }
    if (blknumber == 3) {
        return 576;
        }
    if (blknumber == 4) {
        return 768;
        }
    if (blknumber == 5) {
        return 960;
        }
    if (blknumber == 6) {
        return 1152;
        }
    
}

void drawtetrino(int x, int y,SDL_Texture *texture,SDL_Rect img,SDL_Renderer *renderer){
    SDL_Rect rect = {x-1,y,BOARD_S,BOARD_S};
    SDL_RenderCopy(renderer,texture,&img,&rect);
}

void drawgrid(Gameboard *map,Tetromino *block,SDL_Renderer *renderer,SDL_Texture *blocktexture){
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