#ifndef INCLUDE_DRAW
#define INCLUDE_DRAW

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <chrono>
typedef std::chrono::high_resolution_clock::time_point time_point;

class Animation
{
public:
    Animation(int ms=200);
    ~Animation();
    void addImage(SDL_Renderer *renderer, const char* filename,int nbrX, int nbrY, int w, int h);
    void setCycle(int indexFirst, int indexLast);
    void draw(SDL_Renderer *renderer, int x, int y);
protected:
    unsigned int _startTime;
    SDL_Texture *_texture;
    int _w, _h, _nbrX, _nbrY;
    int _indexMin, _indexMax;
    int _targetTexture;
    unsigned int _ms;
};

//draw functions
void drawFillRect(SDL_Renderer *renderer, int x, int y, int w, int h);

#endif
