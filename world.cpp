#include "world.h"
using namespace std;

World::World(SDL_Renderer *renderer)
{
    _renderer = renderer;
    _map = new MapLoader("levels/0.level");
    _map->load(40,40);

    int x,y;
    _map->getPosToStart(x,y);

    _perso = new Perso(x,y,40,50);
    _perso->getAnimation()->addImage(_renderer,"images/spaceman.png",10,2,63,76);
    _perso->getAnimation()->setTime(100);
    _perso->getAnimation()->setCycle(0,9);//cycle sur l'image

}
World::~World()
{
    delete _perso;
    for( auto ob : _objects)
        delete ob;
}
Perso* World::getPerso()
{
    return _perso;
}
void World::setGravity(double value)
{
    _gravity = value;
}
void World::manageCollision()
{

}
void World::draw(double FPS)
{
    _map->drawMap(_renderer);
    _perso->draw(_renderer);
}