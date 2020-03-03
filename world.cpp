#include "world.h"
using namespace std;

World::World(SDL_Renderer *renderer,const char *fileMap):_uniteX(40),_uniteY(40),_finished(0),_gravity(16)//gravite terrestre
{
    _renderer = renderer;
    _map = new MapLoader(fileMap);
    _map->load(_uniteX,_uniteY);

    int x,y;
    _map->getPosToStart(x,y);

    //add map inside _objects
    _objects = _map->getObjects();

    _perso = new Perso(x,y,70,70);
    _perso->getAnimation()->addImage(_renderer,"resources/images/adventurer-Sheet.png",7,11,50,37);
    _perso->centerCollision(30,70);
    _perso->addTopCollision(-10);
    _perso->getAnimation()->setTime(100);
    _perso->getAnimation()->setCycle(0,3);//cycle sur l'image

}
World::~World()
{
    delete _perso;
    for( auto ob : *_objects)
        delete ob;
}
int World::isFinish() const
{
    return _finished;
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
    //objects
    for(auto ob : *_objects)
    {
        if(ob!=b)
        {
            if(ob->getCollision(b)&&(ob->getId()==1||ob->getId()==4))//bloc normal et bloc dynamique
                return 1;
            if(ob->getCollision(b)&&ob->getId()==3)//bloc fini
            {
                _finished = 1;
            }
        }
    }
    //perso
    if(_perso!=b)
    {       
            if(_perso->getCollision(b)&&(_perso->getId()==1||_perso->getId()==4))//bloc normal et bloc dynamique
                return 1;
            if(_perso->getCollision(b)&&_perso->getId()==3)//bloc fini
            {
                _finished = 1;
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
void World::manageGravity(double fps)
{
        //perso
        _perso->addForce(-90,_gravity*_uniteY/fps);
        //verification de collision précise pixel par pixel
        manageMouvement(_perso,fps);

        for(int i(0);i<_objects->size();i++)
        {
            if((*_objects)[i]->getId()==4)//bloc dynamique
            {
                //ajout de la gravite
                (*_objects)[i]->addForce(-90,_gravity*_uniteY/fps);
                //on gere le mouvement
                manageMouvement((*_objects)[i],fps);
            }
        }
}
void World::draw(double fps)
{
    //pendant le jeu on gere les mouvements, la gravite et les collisions
    if(!isFinish())
        manageGravity(fps);

    //Affichage
    if(isFinish())
    {
        _perso->setForce(0,0);
        _perso->getAnimation()->stop();
    }
    _map->drawMap(_renderer);
    _perso->draw(_renderer);
    
    //affichage des collision
    //_perso->drawCollision(_renderer);
    
    if(!_perso->isAlive())
        _finished = -1;
}