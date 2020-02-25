#include "draw.h"
using namespace std;

Animation::Animation(int ms):_ms(ms),_targetTexture(0),_w(0),_h(0), _nbrX(0), _nbrY(0), _indexMin(0), _indexMax(0)
{
    _startTime = SDL_GetTicks();
    _continuer = 1;
    _flipHorizontal = 0;
}
Animation::~Animation()
{
    SDL_DestroyTexture(_texture);
}
void Animation::start()
{
    _continuer = 1;
}
void Animation::stop()
{
    _continuer = 0;
}
void Animation::addFlipHorizontal()
{
    _flipHorizontal = 1;
}
void Animation::addImage(SDL_Renderer *renderer, const char* filename,int nbrX, int nbrY, int w, int h)
{
    _nbrX = nbrX;
    _nbrY = nbrY;
    _w = w;
    _h = h;
    SDL_Surface *image = NULL;
    image = IMG_Load(filename);
    if(image==NULL)
        SDL_Log("problème de récupération de l'image");

    _texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_FreeSurface(image);
}
void Animation::setTime(int ms)
{
    _ms = ms;
}
void Animation::setCycle(int indexFirst, int indexLast)
{
    if(_indexMin!=indexFirst&&_indexMax!=indexLast)
        _targetTexture = indexFirst;

    _indexMin = indexFirst;
    _indexMax = indexLast;

    //init flipVertical
    _flipHorizontal = 0;
}
void Animation::draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    if(_texture!=NULL)
    {
        uint32_t ellapsed = SDL_GetTicks()-_startTime;
        if(ellapsed>=_ms)
        {
            //changement de la texture à afficher
            if(_continuer)
                _targetTexture++;
            if(_targetTexture>_indexMax)
                _targetTexture = _indexMin;
                
            _startTime += int(ellapsed/_ms)*_ms;
        }
        //affichage de la texture en question
        SDL_Rect srcRect = {_targetTexture%_nbrX*_w,int(_targetTexture/_nbrX)*_h,_w,_h}, dstRect = {x,y,w,h};
        SDL_Point center = {w/2.0,h/2.0};
        if(_flipHorizontal)
            SDL_RenderCopyEx(renderer,_texture,&srcRect,&dstRect,0,&center,static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL));
        else
            SDL_RenderCopyEx(renderer,_texture,&srcRect,&dstRect,0,&center,static_cast<SDL_RendererFlip>(SDL_FLIP_NONE));
    }
    else
        SDL_Log("Il n'y a pas de texture à afficher");
}


void drawFillRect(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    for(int i(0);i<w;i++)
    {
        for(int a(0);a<h;a++)
            SDL_RenderDrawPoint(renderer,x+i,y+a);
    }
}