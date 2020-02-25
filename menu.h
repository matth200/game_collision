#ifndef INCLUDE_MENU
#define INCLUDE_MENU

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "draw.h"

class Menu
{
    public:
        Menu(SDL_Renderer *renderer);
        ~Menu();
        void drawStart();
        void drawFinish();
        void drawDead();
        void drawEndGame();
        void manageClick(SDL_Event &event);
        bool isStarted() const;
        void setText(TTF_Font *font,SDL_Texture* &t,SDL_Rect *rect, const char *text, int x, int y,SDL_Color color = SDL_Color{0,0,0,255});
        void setTextCenter(TTF_Font *font,SDL_Texture* &t,SDL_Rect *rect, const char *text,SDL_Color color = SDL_Color{0,0,0,255});
    protected:
        bool _start, _hover;
        TTF_Font *_bigFont, *_nrmlFont;
        SDL_Texture *_backgroundPicture;
        SDL_Renderer *_renderer;
        Animation _anim;
        SDL_Rect _rectTitle, _rectChoice, _rectFini, _rectSuivant, _rectDead;
        SDL_Texture *_titleTexture, *_choiceTexture, *_finiTexture, *_suivantTexture, *_deadTexture;
};

#endif