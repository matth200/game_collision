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
        void manageCollision();
        Perso* getPerso();
        void draw(double FPS);
    protected:
        Perso *_perso;
        MapLoader *_map;
        std::vector<Object*> _objects;
        double _gravity;
        SDL_Renderer *_renderer;
};


#endif