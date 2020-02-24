#include "object.h"
using namespace std;

Object::Object(double x, double y, int w, int h):_x(x),_y(y),_w(w),_h(h),_forceX(0),_forceY(0),_id(0),_inMove(-1)
{
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
    SDL_Rect rect_src = {_x,_y,_w,_h};
    SDL_Rect rect_dst = {b->_x,b->_y,b->_w,b->_h};

    if(SDL_HasIntersection(&rect_src,&rect_dst))
        return 1;
    return 0;
}
void Object::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer,255,175,100,255);
    SDL_Rect rect = {_x,_y,_w,_h};
    SDL_RenderDrawRect(renderer,&rect);
}

Perso::Perso(double x,double y, int w, int h):_anim(0),_nbrJumpMax(2),Object(x,y,w,h)
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
    _forceY-=size*_h;
}
void Perso::turnRight(int iMin, int iMax)
{
    _anim->setCycle(iMin,iMax);
    _anim->start();
    _forceX=FORCE;
}
void Perso::turnLeft(int iMin, int iMax)
{
    _anim->setCycle(iMin,iMax);
    _anim->start();
    _forceX=-FORCE;
}
void Perso::stopMoving()
{
    _anim->stop();
    _forceX=0;
}
Animation* Perso::getAnimation()
{
    return _anim;
}
void Perso::draw(SDL_Renderer *renderer)
{
    _anim->draw(renderer,_x,_y,_w,_h);
    SDL_Rect rect = {int(_x),int(_y),_w,_h};
    //SDL_SetRenderDrawColor(renderer,255,100,100,255);
    //SDL_RenderDrawRect(renderer,&rect);
}