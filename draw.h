#ifndef INCLUDE_DRAW
#define INCLUDE_DRAW

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point time_point;

class Animation
{
public:
    Animation(int ms);
    ~Animation();
    void addRenderer(SDL_Renderer *image);
    void draw();
protected:
    time_point _startTime;
    std::vector<SDL_Renderer*> _images;
    int _ms;
};
#endif
