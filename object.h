#include <SDL/SDL.h>

struct Pos
{
    int x;
    int y;
};

class Object
{
    public:
        Object(int x,int y);
        ~Object();
        void setPos(int x,int y);
        bool getCollision(Object *a, Object *b);
        void draw(SDL_Surface *screen);
    protected:
        double _x,_y;
        int _w,_h;
        double _forceX, _forceY;

};