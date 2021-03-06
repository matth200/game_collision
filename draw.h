#ifndef INCLUDE_DRAW
#define INCLUDE_DRAW

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 1280
#define HEIGHT 720

#include <chrono>
typedef std::chrono::high_resolution_clock::time_point time_point;

class Animation
{
public:
    Animation(int ms=200);
    ~Animation();
    void setTime(int ms);
    void start();
    void stop();
    void addFlipHorizontal();
    void addImage(SDL_Renderer *renderer, const char* filename,int nbrX, int nbrY, int w, int h);
    void setCycle(int indexFirst, int indexLast);
    void draw(SDL_Renderer *renderer, int x, int y, int w, int h);
protected:
    unsigned int _startTime;
    SDL_Texture *_texture;
    int _w, _h, _nbrX, _nbrY;
    int _indexMin, _indexMax;
    int _targetTexture;
    unsigned int _ms;
    bool _flipHorizontal;
    bool _continuer;
};

//draw functions
void drawFillRect(SDL_Renderer *renderer, int x, int y, int w, int h);

#endif
