#ifndef INCLUDE_WORLD
#define INCLUDE_WORLD

#include <SDL2/SDL.h>
#include "object.h"

class World
{
    public:
        World();
        ~World();

        void manageCollision();
        void draw(SDL_Renderer *renderer);
    protected:
        Perso _perso;
}:


#endif