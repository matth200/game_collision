#ifndef INCLUDE_WORLD
#define INCLUDE_WORLD

#include <SDL2/SDL.h>
#include "object.h"
#include "maploader.h"
#include <vector>

class World
{
    public:
        World(SDL_Renderer *renderer);
        ~World();
        void setGravity(double value);
        bool getCollision(Object *b);
        void manageMouvement(Object *b, double fps);
        Perso* getPerso();
        void draw(double fps);
    protected:
        Perso *_perso;
        int _uniteX, _uniteY;
        MapLoader *_map;
        std::vector<Object*> _objects;
        double _gravity;
        SDL_Renderer *_renderer;
};


#endif