#include "menu.h"
using namespace std;

Menu::Menu(SDL_Renderer *renderer):_start(0),_backgroundPicture(NULL),_titleTexture(0),_choiceTexture(0),_hover(0)
{
    _renderer = renderer;
    _bigFont = TTF_OpenFont("resources/pixel_font.ttf",70);
    _nrmlFont = TTF_OpenFont("resources/pixel_font.ttf",20);

    //fini
    setTextCenter(_bigFont,_finiTexture,&_rectFini,"FINII!!");

    //Suivant
    setText(_nrmlFont,_suivantTexture,&_rectSuivant,"Appuyer sur ENTRER pour continuer...",WIDTH-500,HEIGHT-100,SDL_Color{100,0,100,255});

    //title
    setText(_bigFont,_titleTexture,&_rectTitle,"Ninja Game",50,50);

    //bouton choice
    setText(_nrmlFont,_choiceTexture,&_rectChoice,"Start the game",250,400,SDL_Color{250,100,100,255});

    //dead
    setTextCenter(_bigFont,_deadTexture,&_rectDead,"DEADDDDD",SDL_Color{255,100,100});

    //animation perso
    _anim.setTime(100);
    _anim.addImage(_renderer,"resources/images/adventurer-Sheet.png",7,11,50,37);
    _anim.setCycle(0,3);
}
Menu::~Menu()
{
    SDL_DestroyTexture(_suivantTexture);
    SDL_DestroyTexture(_finiTexture);
    SDL_DestroyTexture(_titleTexture);
    SDL_DestroyTexture(_choiceTexture);
    TTF_CloseFont(_bigFont);
    TTF_CloseFont(_nrmlFont);
}
void Menu::setText(TTF_Font *font,SDL_Texture* &t,SDL_Rect *rect, const char *text, int x, int y,SDL_Color color)
{
    SDL_Surface *texte = TTF_RenderText_Solid(font,text,color);
    t = SDL_CreateTextureFromSurface(_renderer,texte);
    SDL_FreeSurface(texte);
    int w,h;
    SDL_QueryTexture(t,NULL,NULL,&w,&h);
    *rect = {x,y,w,h};
}
void Menu::setTextCenter(TTF_Font *font,SDL_Texture* &t,SDL_Rect *rect, const char *text,SDL_Color color)
{
    SDL_Surface *texte = TTF_RenderText_Solid(font,text,color);
    t = SDL_CreateTextureFromSurface(_renderer,texte);
    SDL_FreeSurface(texte);
    int w,h;
    SDL_QueryTexture(t,NULL,NULL,&w,&h);
    *rect = {WIDTH/2.0-w/2.0,HEIGHT/2.0-h/2.0,w,h};
}
void Menu::drawFinish()
{
    SDL_RenderCopy(_renderer,_finiTexture,NULL,&_rectFini);
    SDL_RenderCopy(_renderer,_suivantTexture,NULL,&_rectSuivant);
}
void Menu::drawDead()
{
    SDL_RenderCopy(_renderer,_deadTexture,NULL,&_rectDead);
    SDL_RenderCopy(_renderer,_suivantTexture,NULL,&_rectSuivant);
}
void Menu::drawEndGame()
{
    
}
void Menu::drawStart()
{
    SDL_SetRenderDrawColor(_renderer,0,0,0,255);

    //title
    //SDL_RenderDrawRect(_renderer,&_rectTitle);
    SDL_RenderCopy(_renderer,_titleTexture,NULL,&_rectTitle);

    //choice
    SDL_Rect rect = {_rectChoice.x-10,_rectChoice.y-10,_rectChoice.w+20,_rectChoice.h+20};
    if(_hover)
        SDL_RenderFillRect(_renderer,&rect);
    else
        SDL_RenderDrawRect(_renderer,&rect);
    SDL_RenderCopy(_renderer,_choiceTexture,NULL,&_rectChoice);

    //animation
    _anim.draw(_renderer,700,100,400,450);
}
void Menu::manageClick(SDL_Event &event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_Rect rect = {event.button.x,event.button.y,1,1};
            if(SDL_HasIntersection(&rect,&_rectChoice))
            {
                _start = 1;
            }
        }
    }
    if(event.type == SDL_MOUSEMOTION)
    {
        SDL_Rect rect = {event.button.x,event.button.y,1,1};
        if(SDL_HasIntersection(&rect,&_rectChoice))
            _hover = 1;
        else
            _hover = 0;
        
    }
}
bool Menu::isStarted() const
{
    return _start;
}