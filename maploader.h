#ifndef INCLUDE_MAP
#define INCLUDE_MAP

#include <SDL2/SDL.h>
#include <fstream>
#include <vector>
#include <regex>

#include <map>
#include <cstdlib>
#include <ctime>

#include "draw.h"
#include "object.h"

class MapLoader
{
    public:
        MapLoader(const char *filename);
        ~MapLoader();
        bool load(int square_w, int square_h);
        void loadObjects();
        bool isLoad();
        void getSize(int &nbrX, int &nbrY);
        void getPosToStart(int &x, int &y);
        void getPosEnd(int &x, int &y);
        std::vector<unsigned char>* getMap();
        std::vector<Object*>* getObjects();
        void drawMap(SDL_Renderer *renderer);
    protected:
        int _nbrX, _nbrY;
        int _square_w, _square_h;
        int _xStart, _yStart;
        int _xEnd, _yEnd;
        int _actualPage, _pageMax;
        //std::map<int,char> _backgroundMap;
        std::string _map_filename;
        std::vector<Object*> _objects;
        std::vector<unsigned char> _map;
};

#endif