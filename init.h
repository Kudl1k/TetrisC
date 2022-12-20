
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


SDL_Renderer* renderer;
SDL_Window* window;
TTF_Font* font;
SDL_Texture *imgtexture;
SDL_Texture *blocktexture;

int init(void);
void destroy();