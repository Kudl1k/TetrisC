#include "init.h"




void rendermainmenu(SDL_Renderer *renderer,SDL_Texture *mainmenutexture){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,mainmenutexture,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void renderlosescreen(SDL_Renderer *renderer,SDL_Rect scorerect, SDL_Rect linesrect, SDL_Texture *losescreentexture, SDL_Texture *scoretexture,SDL_Texture *linetexture){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    scorerect.x = linesrect.x = 472;
    scorerect.y = 461;
    scorerect.w = linesrect.w = 116;
    scorerect.h = linesrect.h = 50;
    linesrect.y = 516;
    SDL_RenderCopy(renderer,losescreentexture,NULL,NULL);
    SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
    SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
    SDL_RenderPresent(renderer);
}

void renderwinscreen(SDL_Renderer *renderer,SDL_Rect scorerect, SDL_Rect linesrect, SDL_Texture *winscreentexture, SDL_Texture *scoretexture,SDL_Texture *linetexture){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    scorerect.x = linesrect.x = 472;
    scorerect.y = 461;
    scorerect.w = linesrect.w = 116;
    scorerect.h = linesrect.h = 50;
    linesrect.y = 516;
    SDL_RenderCopy(renderer,winscreentexture,NULL,NULL);
    SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
    SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
    SDL_RenderPresent(renderer);
}

void renderoptions(SDL_Renderer *renderer,TTF_Font *font,char *fallspeedtext,SDL_Texture *fallspeedtexture,SDL_Texture *optionstexture,float fallspeed){

    SDL_Color White = {255,255,255,255};
    const SDL_Rect speedtextbox = {574,318,36,36};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *fallspeedsurface = TTF_RenderText_Solid(font,  fallspeedtext, White);
    fallspeedtexture = SDL_CreateTextureFromSurface(renderer, fallspeedsurface);
    SDL_FreeSurface(fallspeedsurface);
    sprintf(fallspeedtext,"%0.1f",fallspeed);

    SDL_RenderCopy(renderer,optionstexture,NULL,NULL);
    SDL_RenderCopy(renderer,fallspeedtexture,NULL,&speedtextbox);

    
    SDL_RenderPresent(renderer);
}

void renderinfo(SDL_Renderer *renderer, SDL_Texture *infotexture){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,infotexture,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void destroy(TTF_Font *font,SDL_Texture *nextblocktexture, SDL_Texture *blocktexture,SDL_Texture *imgtexture, SDL_Texture *scoretexture, SDL_Texture *linetexture,SDL_Texture *mainmenutexture, SDL_Texture *losescreentexture, SDL_Texture *optionstexture, SDL_Texture *infotexture,SDL_Texture *fallspeedtexture, SDL_Renderer *renderer, SDL_Window *window){
    TTF_CloseFont(font);
    SDL_DestroyTexture(nextblocktexture);
    SDL_DestroyTexture(blocktexture);
    SDL_DestroyTexture(imgtexture);
    SDL_DestroyTexture(scoretexture);
    SDL_DestroyTexture(linetexture);
    SDL_DestroyTexture(mainmenutexture);
    SDL_DestroyTexture(losescreentexture);
    SDL_DestroyTexture(optionstexture);
    SDL_DestroyTexture(infotexture);
    SDL_DestroyTexture(fallspeedtexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

