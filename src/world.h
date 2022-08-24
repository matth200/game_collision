#ifndef INCLUDE_WORLD
#define INCLUDE_WORLD

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include "maploader.h"

struct VarCollision
{
    std::vector<Object*> liste;
};

class World
{
    public:
        World(SDL_Renderer *renderer,const char *fileMap);
        ~World();
        int isFinish() const;
        void setGravity(double value);
        bool getCollision(Object *b,bool activate=false);
        void manageGravity(double fps);
        void manageMouvement(Object *b, double fps);
        bool oneStep(Object *b, double fps);
        void manageMouvements(std::vector<Object*> *objects,double fps);
        Perso* getPerso();
        void draw(double fps);
    protected:
        Perso *_perso;
        int _uniteX, _uniteY;
        MapLoader *_map;
        std::vector<Object*> *_objects;
        std::map<Object*,VarCollision> _objectCollision;
        double _gravity;
        int _finished;
        SDL_Renderer *_renderer;
};


#endif