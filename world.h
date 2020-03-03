#ifndef INCLUDE_WORLD
#define INCLUDE_WORLD

#include <SDL2/SDL.h>
#include <vector>
#include "maploader.h"

class World
{
    public:
        World(SDL_Renderer *renderer,const char *fileMap);
        ~World();
        int isFinish() const;
        void setGravity(double value);
        bool getCollision(Object *b);
        void manageGravity(double fps);
        void manageMouvement(Object *b, double fps);
        Perso* getPerso();
        void draw(double fps);
    protected:
        Perso *_perso;
        int _uniteX, _uniteY;
        MapLoader *_map;
        std::vector<Object*> *_objects;
        double _gravity;
        int _finished;
        SDL_Renderer *_renderer;
};


#endif