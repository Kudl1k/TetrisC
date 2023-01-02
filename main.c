#include "init.h"


int main()
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;

    SDL_Texture *blocktexture;
    SDL_Texture *imgtexture;
    SDL_Texture *mainmenutexture;
    SDL_Texture *optionstexture;
    SDL_Texture *infotexture;
    SDL_Texture *losescreentexture;
    SDL_Texture *winscreentexture;
    SDL_Texture *nextblocktexture;
    SDL_Texture *scoretexture;
    SDL_Texture *linetexture;
    SDL_Texture *fallspeedtexture;

    int curnumber,nextnumber,mapnumber;
    gamestate state = MAINMENU;
    bool quit = false;
    float secondsElapsed, fallspeed = 0;
    int score = 0;
    int linecounter = 0;

    SDL_Rect scorerect = {727,265,94,38};
    SDL_Rect linesrect = {751,336,46,38};

    char scoretext[10000];
    char linetext[1000];
    char fallspeedtext[100];


    init(window, renderer,font);
    gameinit(renderer,blocktexture,imgtexture,mainmenutexture,optionstexture,infotexture,losescreentexture,winscreentexture,nextblocktexture,curnumber,nextnumber,state);
    while (!quit)
    {
        input(quit,state,secondsElapsed,scorerect,linesrect,mapnumber,fallspeed);
        if (state == MAINMENU){
            rendermainmenu(renderer,mainmenutexture);
        }

        if (state == LOSE)
        {
            curmap = board[0];
            renderlosescreen(renderer,scorerect,linesrect,losescreentexture,scoretexture,linetexture);
        }
        if (state == OPTIONS)
        {
            renderoptions(renderer,font,fallspeedtext,fallspeedtexture,optionstexture,fallspeed);
            curmap = board[mapnumber];

        }
        if (state == ABOUT)
        {
            renderinfo(renderer, infotexture);
        }
        if (state == WIN)
        {
            renderwinscreen(renderer,scorerect,linesrect,winscreentexture,scoretexture,linetexture);
        }
        if(state == GAME){
            Uint64 start = SDL_GetPerformanceCounter();
            game(secondsElapsed,fallspeed,mapnumber,state,score,linecounter,nextnumber,scoretext);
            rendergame(renderer,font,scoretexture,linetexture,imgtexture,blocktexture,nextblocktexture,scorerect,linesrect,scoretext,linetext,nextnumber,score,linecounter);
            Uint64 end = SDL_GetPerformanceCounter();
            secondsElapsed = secondsElapsed + ( (end - start) / (float)SDL_GetPerformanceFrequency());
        }
    }
    destroy(font,nextblocktexture,blocktexture,imgtexture,scoretexture,linetexture,mainmenutexture,losescreentexture,optionstexture,infotexture,fallspeedtexture,renderer, window);
    return 0;
}
