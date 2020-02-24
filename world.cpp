#include "world.h"
using namespace std;

World::World(SDL_Renderer *renderer):_uniteX(40),_uniteY(40),_gravity(9.81)
{
    _renderer = renderer;
    _map = new MapLoader("levels/0.level");
    _map->load(_uniteX,_uniteY);

    int x,y;
    _map->getPosToStart(x,y);

    //add map inside _objects
    vector<unsigned char>* mapChar = _map->getMap();
    int nbrX,nbrY;
    _map->getSize(nbrX,nbrY);
    for(int i(0);i<mapChar->size();i++)
    {
        int x = (i%nbrX)*_uniteX, y = int(i/nbrX)*_uniteY;
        Object *ob = NULL;
        switch((*mapChar)[i])
        {
            case 1://bloc normal
                ob = new Object(x,y,_uniteX,_uniteY);
                _objects.push_back(ob);
                break;
            case 3://bloc de fin
                ob = new Object(x,y,_uniteX,_uniteY);
                ob->setId(2);
                _objects.push_back(ob);
                break;
        }
    }

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
bool World::getCollision(Object *b)
{
    for(auto ob : _objects)
    {
        if(ob!=b)
        {
            if(ob->getCollision(b)&&ob->getId()==0)
                return 1;
        }
    }
    return 0;
}
void World::manageMouvement(Object *b, double fps)
{
    b->startMove();
    bool collisionX = 0, collisionY = 0;
    bool vertical = 0, horizontal = 0;
    bool onceX = 1, onceY = 1;
    while(b->movePixel(fps))
    {
        collisionX = 0;
        collisionY = 0;

        b->frontPixelX(fps);
        if(getCollision(b))
        {
            collisionX = 1;
            b->backPixelX(fps);
        }

        b->frontPixelY(fps);
        if(getCollision(b))
        {
            collisionY = 1;
            b->backPixelY(fps);
        }

        //test de collision
        if(collisionX&&b->getForceX()>=0&&onceX)//cote droit
        {
            horizontal = 0;
            onceX = 0;
        }
        if(collisionX&&b->getForceX()<0&&onceX)//cote gauche
        {
            horizontal = 1;
            onceX = 0;
        }
        if(collisionY&&b->getForceY()>=0&&onceY)//bas
        {
            vertical = 1;
            onceY = 0;
        }
        if(collisionY&&b->getForceY()<0&&onceY)//haut
        {
            vertical = 0;
            onceY = 0;
        }
        //on enleve les forces si collision
        if(collisionX)
            b->setForceX(0);
        if(collisionY)
            b->setForceY(0);

        if(collisionX&&collisionY)
            b->endMove();
    }
    //recuperer quel cote de l'objet est touche
    char collision = 0;
    if(!onceX&&horizontal==0)//cote droit
        collision = collision | MASK_RIGHT;
    if(!onceX&&horizontal==1)//cote gauche
        collision = collision | MASK_LEFT;
    if(!onceY&&vertical==1)//bas
        collision = collision | MASK_BOTTOM;
    if(!onceY&&vertical==0)//haut
        collision = collision | MASK_TOP;

    b->setCollision(collision);
}
void World::draw(double fps)
{
    //gravity
    _perso->addForce(-90,_gravity*_uniteY/fps);
    
    //verification de collision précise pixel par pixel
    manageMouvement(_perso,fps);

    //Affichage
    _map->drawMap(_renderer);
    _perso->draw(_renderer);
     if(_perso->getStateCollision(MASK_BOTTOM))
    {
        SDL_SetRenderDrawColor(_renderer,255,0,0,255);
        int x = _perso->getPosX(),y = _perso->getPosY();
        int w,h;
        _perso->getSize(w,h);
        SDL_RenderDrawLine(_renderer,x,y+h,x+w,y+h);
    }
}