#include "init.h"


int main()
{
    // Incializace SDLka
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("TETRIS - KUD0132", 50, 50, 880, 960, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./src/retrogaming.ttf", 24);
    if (!font)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "TTF_OpenFont Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Texture *scoretexture;
    SDL_Texture *linetexture;
    SDL_Texture *fallspeedtexture;

    // nastaveni zakladnich promenych
    int curnumber,nextnumber,mapnumber;
    gamestate state = MAINMENU;
    bool quit = false;
    float secondsElapsed = 0,fallspeed = 0.5;
    int score = 0;
    int linecounter = 0;
    SDL_Rect scorerect = {727,265,94,38};
    SDL_Rect linesrect = {751,336,46,38};
    SDL_Rect nextblockloc = {589,577,192,192};
    SDL_Rect nextblockpiece = {0,0,192,192};
    char scoretext[10000];
    char linetext[1000];
    char fallspeedtext[100];


    // Loadnuti textur
    SDL_Texture *blocktexture = IMG_LoadTexture(renderer,"./src/tetromino.png");
    SDL_Texture *imgtexture = IMG_LoadTexture(renderer,"./src/MENUS/gamemenu.png");
    SDL_Texture *mainmenutexture = IMG_LoadTexture(renderer,"./src/MENUS/mainmenu.png");
    SDL_Texture *optionstexture = IMG_LoadTexture(renderer,"./src/MENUS/optionsmenu.png");
    SDL_Texture *infotexture = IMG_LoadTexture(renderer,"./src/MENUS/infomenu.png");
    SDL_Texture *losescreentexture = IMG_LoadTexture(renderer,"./src/MENUS/losemenu.png");
    SDL_Texture *winscreentexture = IMG_LoadTexture(renderer,"./src/MENUS/winmenu.png");
    SDL_Texture *nextblocktexture = IMG_LoadTexture(renderer,"./src/tetrominonextblock.png");

    

    // Tlacitka v menu
    SDL_Rect startbox = {271,410,338,78};
    SDL_Rect optionsbox = {271,503,338,78};
    SDL_Rect infobox = {271,591,338,78};
    SDL_Rect exitbox = {271,680,338,78};
    SDL_Rect backbox = {271,680,338,78};
    SDL_Rect plusspeedbox = {623,318,36,36};
    SDL_Rect minspeedbox = {526,318,36,36};
    SDL_Rect mapclearbox = {228,456,80,160};
    SDL_Rect maptbox = {342,456,80,160};
    SDL_Rect mapcbox = {457,456,80,160};
    SDL_Rect mapuprbox = {571,456,80,160};


    //Nastaveni hry
    state = MAINMENU;
    curmap = board[0];
    srand(time(0));
    curnumber = rand() % 7;
    cur = block[curnumber];
    nextnumber = rand() % 7;
    nextblock = block[nextnumber];
    SDL_Event e;
    SDL_Point mousepos;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&mousepos.x,&mousepos.y); //pozice mysi
            } 
            if (state == GAME) //input pro hru
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
                        state = MAINMENU;
                        curmap = board[0];
                        break;
                    }
                }
            }
            if (state == MAINMENU) //input pro mainmenu
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&startbox)) {
                            state = GAME;
                            scorerect.x = 727;
                            scorerect.y = 265;
                            scorerect.w = 94;
                            scorerect.h = 38;
                            linesrect.x = 751;
                            linesrect.y = 320;
                            linesrect.w = 46;
                            linesrect.h = 38;
                            grid_reset(&curmap);
                        }
                        if (SDL_PointInRect(&mousepos,&optionsbox))
                        {
                            state = OPTIONS;
                        }
                        if (SDL_PointInRect(&mousepos,&infobox))
                        {
                            state = ABOUT;
                        }
                        if (SDL_PointInRect(&mousepos,&exitbox))
                        {
                            quit = true;
                        }
                    }
                    
                }
            }
            if (state == OPTIONS || state == ABOUT || state == WIN || state == LOSE) // input pro backbutton pro menu
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (SDL_PointInRect(&mousepos,&backbox)){
                            state = MAINMENU;
                        }
                    }
                }     
            }
            if (state == OPTIONS) // input pro options
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
        if (state == MAINMENU){ // renderovani mainmenu
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,mainmenutexture,NULL,NULL);
            SDL_RenderPresent(renderer);
        }
        if (state == LOSE) // renderovani losescreenu
        {
            curmap = board[0];
            renderlosescreen(renderer,scorerect,linesrect,losescreentexture,scoretexture,linetexture);
        }
        if (state == OPTIONS) // renderovani options
        {
            renderoptions(renderer,font,fallspeedtext,fallspeedtexture,optionstexture,fallspeed);
            curmap = board[mapnumber];

        }
        if (state == ABOUT) // renderovani infa
        {
            renderinfo(renderer, infotexture);
        }
        if (state == WIN) // renderovani winscreenu
        {
            renderwinscreen(renderer,scorerect,linesrect,winscreentexture,scoretexture,linetexture);
        }
        if(state == GAME){ // renderovani hry
            Uint64 start = SDL_GetPerformanceCounter();
            grid_reset(&curmap);
            if (secondsElapsed >fallspeed && (!issettled(&cur,&curmap)))
            {
                
                cur.y += 1;       // posunovac
                secondsElapsed = 0;
            }
            
            grid_init(&cur,&curmap);

            if (issettled(&cur,&curmap))
            {
                if (gameover(&curmap)) {
                    state = LOSE;
                }
                if (gamewin(&curmap,mapnumber)) {
                    state = WIN;
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

            //zapsani score
            SDL_Color White = {255,255,255,255};
            SDL_Surface *scoresurface = TTF_RenderText_Solid(font,  scoretext, White);
            scoretexture = SDL_CreateTextureFromSurface(renderer, scoresurface);
            SDL_FreeSurface(scoresurface);
            sprintf(scoretext,"%d",score);
            SDL_Surface *linesurface = TTF_RenderText_Solid(font,  linetext, White);
            linetexture = SDL_CreateTextureFromSurface(renderer, linesurface);
            SDL_FreeSurface(linesurface);
            sprintf(linetext,"%d",linecounter);

            //vyrendrovani hry
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,imgtexture,NULL,NULL);
            SDL_RenderCopy(renderer,scoretexture,NULL,&scorerect);
            SDL_RenderCopy(renderer,linetexture,NULL,&linesrect);
            drawgrid(&curmap,&cur,renderer,blocktexture);
            printf("%d\n",nextnumber);
            nextblockpiece.x = drawnextblock(nextnumber);
            SDL_RenderCopy(renderer,nextblocktexture,&nextblockpiece,&nextblockloc);
            SDL_RenderPresent(renderer);
            Uint64 end = SDL_GetPerformanceCounter();
            secondsElapsed = secondsElapsed + ( (end - start) / (float)SDL_GetPerformanceFrequency());
        }
    }
    destroy(font,nextblocktexture,blocktexture,imgtexture,scoretexture,linetexture,mainmenutexture,losescreentexture,optionstexture,infotexture,fallspeedtexture,renderer, window);
    return 0;
}
