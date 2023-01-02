#include "init.h"


void init(SDL_Window *window,SDL_Renderer *renderer,TTF_Font *font){
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("TETRIS - KUD0132", 50, 50, 880, 960, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

        TTF_Init();

    font = TTF_OpenFont("./src/retrogaming.ttf", 24);
    if (!font)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "TTF_OpenFont Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    
    

}

void gameinit(SDL_Renderer *renderer,SDL_Texture *blocktexture,SDL_Texture *imgtexture, SDL_Texture *mainmenutexture,SDL_Texture *optionstexture,SDL_Texture *infotexture, SDL_Texture *losescreentexture, SDL_Texture *winscreentexture,SDL_Texture *nextblocktexture,int curnumber, int nextnumber,gamestate stateofgame){
    blocktexture = IMG_LoadTexture(renderer,"./src/tetromino.png");
    imgtexture = IMG_LoadTexture(renderer,"./src/MENUS/gamemenu.png");
    mainmenutexture = IMG_LoadTexture(renderer,"./src/MENUS/mainmenu.png");
    optionstexture = IMG_LoadTexture(renderer,"./src/MENUS/optionsmenu.png");
    infotexture = IMG_LoadTexture(renderer,"./src/MENUS/infomenu.png");
    losescreentexture = IMG_LoadTexture(renderer,"./src/MENUS/losemenu.png");
    winscreentexture = IMG_LoadTexture(renderer,"./src/MENUS/winmenu.png");

    nextblocktexture = IMG_LoadTexture(renderer,"./src/tetrominonextblock.png");
    stateofgame = MAINMENU;
    curmap = board[0];
    srand(time(0));
    curnumber = rand() % 7;
    cur = block[curnumber];
    nextnumber = rand() % 7;
    nextblock = block[nextnumber];
}

void input(bool quit,gamestate stateofgame,float secondsElapsed,SDL_Rect scorerect,SDL_Rect linesrect,int mapnumber, float fallspeed){

    const SDL_Rect startbox = {271,410,338,78};
    const SDL_Rect optionsbox = {271,503,338,78};
    const SDL_Rect infobox = {271,591,338,78};
    const SDL_Rect exitbox = {271,680,338,78};
    const SDL_Rect backbox = {271,680,338,78};
    const SDL_Rect plusspeedbox = {623,318,36,36};
    const SDL_Rect minspeedbox = {526,318,36,36};
    const SDL_Rect mapclearbox = {228,456,80,160};
    const SDL_Rect maptbox = {342,456,80,160};
    const SDL_Rect mapcbox = {457,456,80,160};
    const SDL_Rect mapuprbox = {571,456,80,160};


    SDL_Event e;
    SDL_Point mousepos;
    while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&mousepos.x,&mousepos.y);
            } 
            if (stateofgame == GAME)
            {
                if (e.type == SDL_KEYDOWN)
                {
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        if(!colision(&cur,&curmap,3)){
                            rotate_block(&cur);
                        }
                        break;
                    case SDLK_DOWN:
                        if(!issettled(&cur,&curmap)) cur.y += 1;
                        break;
                    case SDLK_LEFT:
                        if(!colision(&cur, &curmap,2)) cur.x -= 1;
                        if (issettled(&cur,&curmap))
                        {
                            secondsElapsed = 0;
                        }
                        
                        break;
                    case SDLK_RIGHT:
                        if(!colision(&cur, &curmap,1)) cur.x += 1;
                        if (issettled(&cur,&curmap))
                        {
                            secondsElapsed = 0;
                        }
                        break;
                    case SDLK_SPACE:
                        harddrop(&cur,&curmap);
                        break;
                    case SDLK_ESCAPE:
                        stateofgame = MAINMENU;
                        curmap = board[0];
                        break;
                    }
                }
            }
            if (stateofgame == MAINMENU)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&startbox)) {
                            stateofgame = GAME;
                            scorerect.x = 727;
                            scorerect.y = 265;
                            scorerect.w = 94;
                            scorerect.h = 38;
                            linesrect.x = 751;
                            linesrect.y = 336;
                            linesrect.w = 46;
                            linesrect.h = 38;
                            grid_reset(&curmap);
                        }
                        if (SDL_PointInRect(&mousepos,&optionsbox))
                        {
                            stateofgame = OPTIONS;
                        }
                        if (SDL_PointInRect(&mousepos,&infobox))
                        {
                            stateofgame = ABOUT;
                        }
                        if (SDL_PointInRect(&mousepos,&exitbox))
                        {
                            quit = true;
                        }
                    }
                    
                }
            }
            if (stateofgame == OPTIONS || stateofgame == ABOUT || stateofgame == WIN || stateofgame == LOSE)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&backbox)){
                            stateofgame = MAINMENU;
                        }
                    }
                }     
            }
            if (stateofgame == OPTIONS)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&plusspeedbox)){
                            if (fallspeed < 1) fallspeed += 0.1;
                        }
                        if (SDL_PointInRect(&mousepos,&minspeedbox))
                        {
                            if (fallspeed > 0.2) fallspeed -= 0.1;
                        }
                        if (SDL_PointInRect(&mousepos,&mapclearbox)){
                            mapnumber = 0;

                            }
                        if (SDL_PointInRect(&mousepos,&maptbox)){
                            mapnumber = 1;
                        }
                        if (SDL_PointInRect(&mousepos,&mapcbox)) mapnumber = 2;
                        if (SDL_PointInRect(&mousepos,&mapuprbox)) mapnumber = 3;
                    }
                }     
            }
        }
}

void game(float secondsElapsed,float fallspeed,int mapnumber,gamestate stateofgame,int score, int linecounter,int nextnumber,char *scoretext){
        grid_reset(&curmap);

        if (secondsElapsed >fallspeed && (!issettled(&cur,&curmap)))
        {
            
            cur.y += 1;       //! posunovac
            secondsElapsed = 0;
        }
        
        grid_init(&cur,&curmap);

        if (issettled(&cur,&curmap))
        {
            if (gameover(&curmap)) {
                stateofgame = LOSE;
            }
            if (gamewin(&curmap,mapnumber)) {
                stateofgame = WIN;
            }

            if(secondsElapsed > fallspeed){
                addseatledblock(&cur,&curmap,secondsElapsed);
                fullline(&curmap,&score,&linecounter);
                cur = nextblock;
                srand(time(0));
                nextnumber = rand() % 7;
                nextblock = block[nextnumber];
                sprintf(scoretext,"%d",score);
            }
        }
}


void rendergame(SDL_Renderer *renderer,TTF_Font *font,SDL_Texture *scoretexture,SDL_Texture *linetexture,SDL_Texture *imgtexture,SDL_Texture *blocktexture,SDL_Texture *nextblocktexture,SDL_Rect scorerect, SDL_Rect linesrect,char *scoretext,char *linetext,int nextnumber,int score,int linecounter){
    SDL_Color White = {255,255,255,255};
    SDL_Surface *scoresurface = TTF_RenderText_Solid(font,  scoretext, White);
    scoretexture = SDL_CreateTextureFromSurface(renderer, scoresurface);
    SDL_FreeSurface(scoresurface);
    sprintf(scoretext,"%d",score);
    SDL_Surface *linesurface = TTF_RenderText_Solid(font,  linetext, White);
    linetexture = SDL_CreateTextureFromSurface(renderer, linesurface);
    SDL_FreeSurface(linesurface);
    sprintf(linetext,"%d",linecounter);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,imgtexture,NULL,NULL);
    SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
    SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
    drawgrid(&curmap,&cur,renderer,blocktexture);
    drawnextblock(nextnumber,renderer,nextblocktexture);
    SDL_RenderPresent(renderer);
}

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

