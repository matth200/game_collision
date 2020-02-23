#ifndef INCLUDE_MAP
#define INCLUDE_MAP

#include <SDL2/SDL.h>
#include <fstream>
#include <vector>

class MapLoader
{
    public:
        MapLoader(const char *filename);
        ~MapLoader();
        void drawMap(SDL_Renderer *renderer,int x, int y);
    protected:
        int _w, _h;
        std::vector<char> _map;
};

#endif