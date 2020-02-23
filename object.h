#include <SDL2/SDL.h>
#include <math.h>

#include "draw.h"
#define PI 3.14159265

class Object
{
    public:
        Object(double x,double y, int w, int h);
        ~Object();
        void setPos(double x,double y);
        void getSize(int &w, int &h);
        void setSize(int w, int h);
        double getPosX() const;
        double getPosY() const;
        void setForceX(double value);
        void setForceY(double value);
        void setForce(double angle, double value);
        void addForce(double angle, double value);
        double getForceX() const;
        double getForceY() const;
        bool getCollision(Object *b);
        void draw(SDL_Surface *screen);
    protected:
        double _x,_y;
        int _w,_h;
        double _forceX, _forceY;
};


class Perso : public Object
{
    public:
        Perso(double x,double y, int w, int h);
        ~Perso();
        void draw(SDL_Renderer *renderer);
        void jump(int size = 2);
        Animation* getAnimation();
    protected:
        Animation *_anim;
};