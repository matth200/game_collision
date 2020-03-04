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
bool World::getCollision(Object *b,bool activate)
{
    bool collision = 0;
    //objects
    for(auto ob : *_objects)
    {
        if(ob!=b)
        {
            if(ob->getCollision(b)&&ob->getId()!=3)//bloc normal et bloc dynamique
            {
                if(activate)
                    ob->addDebugSquare();
                else
                    ob->noDebugSquare();
                _objectCollision[b].liste.push_back(ob);
                collision = 1;
            }
            if(ob->getCollision(b)&&ob->getId()==3&&b->getId()==1)//bloc final et joueur
                _finished = 1;
        }
    }
    //perso
    if(_perso!=b)
    {       
            if(_perso->getCollision(b)&&b->getId()!=3)//bloc normal et bloc dynamique
            {
                if(activate)
                    _perso->addDebugSquare();
                else
                    _perso->noDebugSquare();
                _objectCollision[b].liste.push_back(_perso);
                collision = 1;
            }
    }
    return collision;
}
void World::manageMouvement(Object *b, double fps)
{
    b->startMove();
    _objectCollision[b].liste.clear();
    bool collisionX = 0, collisionY = 0;
    bool vertical = 0, horizontal = 0;
    bool onceX = 1, onceY = 1;
    while(b->movePixel(fps))
    {
        collisionX = 0;
        collisionY = 0;

        b->frontPixelX(fps);
        if(getCollision(b,false))
        {
            collisionX = 1;
            b->backPixelX(fps);
        }

        b->frontPixelY(fps);
        if(getCollision(b,false))
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
bool World::oneStep(Object *b, double fps)
{
    bool collisionX = 0, collisionY = 0;
    bool vertical = 0, horizontal = 0;
    bool onceX = 1, onceY = 1;
    
    bool continuer = b->movePixel(fps);
    if(continuer){
        collisionX = 0;
        collisionY = 0;

        b->frontPixelX(fps);
        if(getCollision(b,false))
        {
            collisionX = 1;
            b->backPixelX(fps);
        }

        b->frontPixelY(fps);
        if(getCollision(b,false))
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
    if(!onceX||!onceY)
    {
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
    return continuer;
}
void World::manageMouvements(vector<Object*> *objects,double fps)
{
    //on lance les mouvements
    for( auto b : (*objects)){
        b->startMove();
        _objectCollision[b].liste.clear();
    }

    bool allFinished = 0;
    while(!allFinished)
    {
        allFinished = 1; //fini
        for(int i(0);i<objects->size();i++)
        {
            if(oneStep((*objects)[i],fps))
                allFinished = 0; //si besoin de relancer on dit que ce n'est pas terminé
        }
    }
}
void World::manageGravity(double fps)
{
    vector<Object*> objects;
    //perso
    _perso->addForce(-90,_gravity*_uniteY/fps);
    //verification de collision précise pixel par pixel
    manageMouvement(_perso,fps);
    //objects.push_back(_perso);

    for(int i(0);i<_objects->size();i++)
    {
        if((*_objects)[i]->getId()==4)//bloc dynamique
        {
            //ajout de la gravite
            (*_objects)[i]->addForce(-90,_gravity*_uniteY/fps);
            //on gere le mouvement
            objects.push_back((*_objects)[i]);
            //manageMouvement((*_objects)[i],fps);
        }
        else if((*_objects)[i]->getId()==5)//bloc dynamique
        {
            //ajout de la gravite
            (*_objects)[i]->setForce(-180,_gravity*_uniteY/fps);
            //on gere le mouvement
            objects.push_back((*_objects)[i]);
            //manageMouvement((*_objects)[i],fps);
        }
    }
    manageMouvements(&objects,fps);

    //Debug
    for( auto b : (*_objects))
        b->noDebugSquare();
    for(map<Object*,VarCollision>::iterator it(_objectCollision.begin());it!=_objectCollision.end();++it){
        Object *b = it->first;
        if(it->second.liste.size()>0)
        {
            b->addDebugSquare();
            for(auto b2 : it->second.liste)
            {
                b2->addDebugSquare();
            }
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