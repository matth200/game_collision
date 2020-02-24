#include <SDL2/SDL.h>
#include <cmath>
#include <string>

#include "draw.h"
#define PI 3.14159265
#define FORCE 40*3

class Object
{
    public:
        Object(double x,double y, int w, int h);
        ~Object();
        void move(double fps);
        void setPos(double x,double y);
        void getSize(int &w, int &h);
        void setSize(int w, int h);
        double getPosX() const;
        double getPosY() const;
        void setForceX(double value);
        void setForceY(double value);
        void setForce(double angle, double value);
        void addForce(double angle, double value);
        void setId(int id);
        int getId() const;
        double getForceX() const;
        double getForceY() const;
        void startMove();
        bool movePixel(double fps);
        void backPixelX(double fps);
        void backPixelY(double fps);
        void frontPixelX(double fps);
        void frontPixelY(double fps);
        void endMove();
        bool getCollision(Object *b);
        void draw(SDL_Renderer *renderer);
    protected:
        double _x,_y;
        int _id;
        int _w,_h;
        int _inMove;
        double _forceX, _forceY;
};


class Perso : public Object
{
    public:
        Perso(double x,double y, int w, int h);
        ~Perso();
        void draw(SDL_Renderer *renderer);
        void turnRight(int iMin, int iMax);
        void turnLeft(int iMin, int iMax);
        void stopMoving();
        void jump(double size = 4);
        Animation* getAnimation();
    protected:
        Animation *_anim;
        int _nbrJumpMax;
        
};