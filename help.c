#include "help.h"

void drawtetrino(int x, int y, int w, int h, SDL_Color color,SDL_Renderer *renderer){
    SDL_Rect rect = {x,y,w-2,h-2};
    SDL_GetRenderDrawColor(renderer,color.r,color.g,color.b,255);
    SDL_RenderFillRect(renderer,&rect);
    SDL_Rect outline = {x,y,w,h};
    SDL_GetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&outline);
}