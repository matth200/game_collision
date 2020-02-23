#include "object.h"
using namespace std;

Object::Object(double x, double y, int w, int h):_x(x),_y(y),_w(w),_h(h),_forceX(0),_forceY(0)
{
}
Object::~Object()
{
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
    return 0;
}
void Object::draw(SDL_Surface *screen)
{

}

Perso::Perso(double x,double y, int w, int h):_anim(0),Object(x,y,w,h)
{
    _anim = new Animation();
}
Perso::~Perso()
{
    delete _anim;
}
Animation* Perso::getAnimation()
{
    return _anim;
}
void Perso::draw(SDL_Renderer *renderer)
{
    _anim->draw(renderer,_x,_y,_w,_h);
    SDL_Rect rect = {int(_x),int(_y),_w,_h};
    SDL_SetRenderDrawColor(renderer,255,100,100,255);
    SDL_RenderDrawRect(renderer,&rect);
}