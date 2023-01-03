#include "update.h"

void rotate_block(Tetromino *block){
    int N = block->size;
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

bool colision(Tetromino *block,Gameboard *map,int side){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (((block->shape[i][j] == 1 && map->grid[blk.y][blk.x + 1] == 3) || (block->shape[i][j] == 1 && map->grid[blk.y][blk.x + 1] == 2) || (block->shape[i][j] == 1 && map->grid[blk.y][blk.x + 1] == 6) )  && side == 1)
            {
                return true;
            }
            if (((block->shape[i][j] == 1 && map->grid[blk.y][blk.x - 1] == 3) || (block->shape[i][j] == 1 && map->grid[blk.y][blk.x - 1] == 2) || (block->shape[i][j] == 1 && map->grid[blk.y][blk.x - 1] == 6))&& side == 2)
            {
                return true;
            }
            if ((map->grid[blk.y][blk.x - 1] == 3 || map->grid[blk.y][blk.x + 1] == 3) && side == 3)
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

void harddrop(Tetromino *block, Gameboard *map){
    while (!issettled(block,map))
    {
        block->y++;
    }
    
}

bool issettled(Tetromino *block, Gameboard *map){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((block->shape[i][j] == 1 && map->grid[blk.y + 1][blk.x] == 4) || (block->shape[i][j] == 1 && map->grid[blk.y + 1][blk.x] == 2) ||(block->shape[i][j] == 1 && map->grid[blk.y + 1][blk.x] == 6))
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

void addseatledblock(Tetromino *block, Gameboard *map,float fallspeed){
    SDL_Rect blk;
    blk.x = block->x;
    blk.y = block->y;
    
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block->shape[i][j] == 1)
            {
                map->grid[blk.y][blk.x] = 2;
            } 
            blk.x++;
        }
        blk.x = block->x;
        blk.y++;
    }


}
