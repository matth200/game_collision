#include <SDL2/SDL.h>
#include <cmath>
#include <string>

#include "draw.h"
#define PI 3.14159265
#define FORCE 40*3

#define MASK_RIGHT (1<<0)
#define MASK_LEFT (1<<1)
#define MASK_BOTTOM (1<<2)
#define MASK_TOP (1<<3)

class Object
{
    public:
        Object(double x,double y, int w, int h);
        ~Object();
        void setCollision(char state);
        void centerCollision(int w, int h,SDL_Point *p=NULL);
        void addTopCollision(int value);
        bool getStateCollision(char state);
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
        void drawCollision(SDL_Renderer *renderer);
        bool getCollision(Object *b);
        void draw(SDL_Renderer *renderer);
    protected:
        double _x,_y;
        int _id;
        int _w,_h;
        int _inMove;
        double _forceX, _forceY;
        char _collisionState;
        int _cW, _cH;
        int _topAdjustement;
        SDL_Point _centerCollision;
};


class Perso : public Object
{
    public:
        Perso(double x,double y, int w, int h);
        ~Perso();
        void draw(SDL_Renderer *renderer);
        bool isAlive() const;
        void turnRight(int iMin, int iMax);
        void turnLeft(int iMin, int iMax);
        void stopMoving(int iMin=0, int iMax=0);
        void jump(double size = 4.5);
        Animation* getAnimation();
    protected:
        Animation *_anim;
        bool _alive;
        int _nbrJumpMax,_nbrJump;
        
};