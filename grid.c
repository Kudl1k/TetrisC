#include "grid.h"


void grid_init(Tetrino *block,Gameboard *map){    
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++,blk.y++)
    {
        for (int j = 0; j < 4; j++,blk.x++)
        {
            if (block->shape[i][j] == 1)
            {   
                map->grid[blk.y][blk.x] = block->shape[i][j];
            }
        }
        blk.x = block->x;
    }
}

void fullline(Gameboard *map,int *score,int *linecounter){
    int flag = 0;    
        for (int i = 19; i > 0; i--)
        {
            for (int j = 1; j <= BOARD_W; j++){
                
                if (map->grid[i][j] == 2 || map->grid[i][j] == 6)
                {
                    flag = 1;
                }
                else{
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                (*score) += 800;
                (*linecounter) += 1;
                clearline(map,i);
                movedowngrid(map,i);
                fullline(map,score,linecounter);
            }
        }
    
    
}

void clearline(Gameboard *map,int line){
    for (int j = 1; j <= BOARD_W; j++)
    {
        map->grid[line][j] = 0;
    }

}

void movedowngrid(Gameboard *map,int line){
    for (int i = line; i > 0; i--)
    {
        for (int j = 1; j <= BOARD_W; j++)
        {
            map->grid[i][j] = map->grid[i-1][j];
        }
    }
}

void grid_reset(Gameboard *map){
    for (int i = 0; i < BOARD_H; i++)
    {
        for (int j = 1; j <= BOARD_W; j++){
            if (map->grid[i][j] == 1)
            {
                map->grid[i][j] = 0;
            }
        }
    }
}

bool gameover(Gameboard *map){
    for (int j = 1; j <= BOARD_W; j++)
    {
        if (map->grid[3][j] == 2)
        {
            curmap = board[0];
            return true;
        }
    }
    return false;
}

bool gamewin(Gameboard *map,int mapnumber){
    if (mapnumber == 1 || mapnumber == 2 || mapnumber == 3)
    {
        for (int i = 0; i < BOARD_H; i++)
        {
            for (int j = 1; j <= BOARD_W; j++)
            {
                if (map->grid[i][j] == 6)
                {
                    return false;
                }
            }
        }
        return true;
    }
        
    return false;
}