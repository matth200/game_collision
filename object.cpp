#include "object.h"
using namespace std;

Object::Object(double x, double y, int w, int h):_x(x),_y(y),_w(w),_h(h),_cW(w),_cH(h),_forceX(0),_forceY(0),_id(0),_inMove(-1),_collisionState(-1)
{
    _centerCollision = {_cW/2.0,_cH/2.0};
}
Object::~Object()
{
}
void Object::move(double fps)
{
    //SDL_Log((to_string(_x)+" "+to_string(_y)).c_str());
    _x+=_forceX/fps;
    _y+=_forceY/fps;
}
void Object::centerCollision(int w, int h,SDL_Point *p)
{
    if(p!=NULL)
        _centerCollision = *p;
    _cW = w;
    _cH = h;
}
void Object::setCollision(char state)
{
    _collisionState = state;
}
bool Object::getStateCollision(char state)
{
    return _collisionState & state;
}
void Object::startMove()
{
    _inMove = 0;
}
void Object::backPixelX(double fps)
{
    double hypo = sqrt(pow(_forceX,2)+pow(_forceY,2));
    _x-=_forceX/hypo/fps;
}
void Object::backPixelY(double fps)
{
    double hypo = sqrt(pow(_forceX,2)+pow(_forceY,2));
    _y-=_forceY/hypo/fps;
}
void Object::frontPixelX(double fps)
{
    double hypo = sqrt(pow(_forceX,2)+pow(_forceY,2));
    _x+=_forceX/hypo/fps;
}
void Object::frontPixelY(double fps)
{
    double hypo = sqrt(pow(_forceX,2)+pow(_forceY,2));
    _y+=_forceY/hypo/fps;
}
bool Object::movePixel(double fps)
{
    double hypo = sqrt(pow(_forceX,2)+pow(_forceY,2));
    if(_inMove==-1||_inMove>=hypo)
    {
        _inMove=-1;
        return 0;
    }
    _inMove++;
    return 1;
}
void Object::endMove()
{
    _inMove = -1;
}
void Object::setId(int id)
{
    _id = id;
}
int Object::getId() const
{
    return _id;
}
void Object::setPos(double x,double y)
{
    _x = x;
    _y = y;
}
void Object::getSize(int &w, int &h)
{
    w = _w;
    h = _h;
}
void Object::setSize(int w, int h)
{
    _w = w;
    _h = h;
}
double Object::getPosX() const
{
    return _x;
}
double Object::getPosY() const
{
    return _y;
}
void Object::setForceX(double value)
{
    _forceX = value;
}
void Object::setForceY(double value)
{
    _forceY = value;
}
void Object::setForce(double angle, double value)
{
    _forceX = cos(angle/180.0*PI)*value;
    _forceY = -sin(angle/180.0*PI)*value;
}
void Object::addForce(double angle, double value)
{
    _forceX += cos(angle/180.0*PI)*value;
    _forceY += -sin(angle/180.0*PI)*value;
}
double Object::getForceX() const
{
    return _forceX;
}
double Object::getForceY() const
{
    return _forceY;
}
bool Object::getCollision(Object *b)
{
    SDL_Rect rect_src = {_x+_centerCollision.x-_cW/2.0,_y+_centerCollision.y-_cH/2.0,_cW,_cH};
    SDL_Rect rect_dst = {b->_x+b->_centerCollision.x-b->_cW/2.0,b->_y+b->_centerCollision.y-b->_cH/2.0,b->_cW,b->_cH};

    if(SDL_HasIntersection(&rect_src,&rect_dst))
        return 1;
    return 0;
}
void Object::drawCollision(SDL_Renderer *renderer)
{
    if(getStateCollision(MASK_BOTTOM))//sol
    {
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawLine(renderer,_x+_centerCollision.x-_cW/2.0,_y+_centerCollision.y-_cH/2.0+_cH,_x+_centerCollision.x-_cW/2.0+_cW,_y+_centerCollision.y-_cH/2.0+_cH);
    }
    if(getStateCollision(MASK_TOP))//plafond
    {
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawLine(renderer,_x+_centerCollision.x-_cW/2.0,_y+_centerCollision.y-_cH/2.0,_x+_centerCollision.x-_cW/2.0+_cW,_y+_centerCollision.y-_cH/2.0);
    }
    if(getStateCollision(MASK_LEFT))//cote gauche
    {
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawLine(renderer,_x+_centerCollision.x-_cW/2.0,_y+_centerCollision.y-_cH/2.0,_x+_centerCollision.x-_cW/2.0,_y+_centerCollision.y-_cH/2.0+_cH);
    }
    if(getStateCollision(MASK_RIGHT))//cote droit
    {
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawLine(renderer,_x+_centerCollision.x-_cW/2.0+_cW,_y+_centerCollision.y-_cH/2.0,_x+_centerCollision.x-_cW/2.0+_cW,_y+_centerCollision.y-_cH/2.0+_cH);
    }
}
void Object::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer,255,175,100,255);
    SDL_Rect rect = {_x,_y,_w,_h};
    SDL_RenderDrawRect(renderer,&rect);
}

Perso::Perso(double x,double y, int w, int h):_anim(0),_nbrJumpMax(2),_alive(1),_nbrJump(0),Object(x,y,w,h)
{
    _id = 1;
    _anim = new Animation();
}
Perso::~Perso()
{
    delete _anim;
}
void Perso::jump(double size)
{
    if(_nbrJump==0)
    {
        _anim->setCycle(14,21);
        _anim->start();
    }
    if(_nbrJump<_nbrJumpMax)
    {
        _forceY=-size*_h;
        _nbrJump++;
    }
}
void Perso::turnRight(int iMin, int iMax)
{
    if(_nbrJump==0)
    {
        _anim->setCycle(iMin,iMax);
        _anim->start();
    }
    _forceX=FORCE;
}
void Perso::turnLeft(int iMin, int iMax)
{
    if(_nbrJump==0)
    {
        _anim->setCycle(iMin,iMax);
        _anim->start();
    }
    _anim->addFlipHorizontal();
    _forceX=-FORCE;
}
void Perso::stopMoving(int iMin, int iMax)
{
    if(iMin==0&&iMax==0)
        _anim->stop();
    else if(_nbrJump==0){
        _anim->setCycle(iMin,iMax);
        _anim->start();
    }
    _forceX=0;
}
Animation* Perso::getAnimation()
{
    return _anim;
}
bool Perso::isAlive() const
{
    return _alive;
}
void Perso::draw(SDL_Renderer *renderer)
{
    if(_y>HEIGHT)//tombe
        _alive = 0;
    if(_collisionState & MASK_BOTTOM)
        _nbrJump = 0;

    _anim->draw(renderer,_x,_y,_w,_h);
    SDL_Rect rect = {int(_x),int(_y),_w,_h};
    //SDL_SetRenderDrawColor(renderer,255,100,100,255);
    //SDL_RenderDrawRect(renderer,&rect);
}