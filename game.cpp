#include "game.h"
using namespace std;

Game::Game():_window(NULL),_state(1),_renderer(NULL),_actuelFPS(0){

    if(SDL_Init(SDL_INIT_VIDEO)<0)
        noticeError("problème de init()");

    _window = SDL_CreateWindow("Test de fenêtre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if( _window == NULL)
        noticeError("problème de createWindow()");
    
    _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED);
    if(_renderer == NULL)
        noticeError("problème de createRenderer()");

    _perso = new Perso(50,50,40,50);
    _perso->getAnimation()->addImage(_renderer,"images/spaceman.png",10,2,63,76);
    _perso->getAnimation()->setTime(100);
    _perso->getAnimation()->setCycle(0,9);//cycle sur l'image

    SDL_SetRenderDrawBlendMode(_renderer,SDL_BLENDMODE_BLEND);
}
Game::~Game(){
    delete _perso;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::core(){
    while(_state==1)
    {
        _start = SDL_GetTicks();
        manageEvent();
        //keyboard events
        if(getClicked(SDLK_ESCAPE))
            quit();

        if(getClicked(SDLK_RIGHT))
        {
            _perso->getAnimation()->start();
            _perso->getAnimation()->setCycle(0,9);
        }
        else if(getClicked(SDLK_LEFT))
        {
            _perso->getAnimation()->start();
            _perso->getAnimation()->setCycle(10,19);
        }
        if(!getKeydown(SDLK_RIGHT)&&!getKeydown(SDLK_LEFT))
            _perso->getAnimation()->stop();
            
        draw();

        //bien mais pas trés précis refaire avec chrono::high_resolution_clock
        unsigned int timeEllapsed = SDL_GetTicks()-_start;
        if(timeEllapsed<1000.0/FPS)
            SDL_Delay(1000.0/FPS-timeEllapsed);
        //calcul des fps
        _actuelFPS = 1000.0/(SDL_GetTicks()-_start);
        //SDL_Log(to_string(_actuelFPS).c_str());
    }
}
void Game::draw()
{
    SDL_SetRenderDrawColor(_renderer,100,100,100,255);
    SDL_RenderClear(_renderer);

    _perso->draw(_renderer);

    SDL_RenderPresent(_renderer);
}
void Game::manageEvent()
{
    while(SDL_PollEvent(&_events))
    {
        switch (_events.type)
        {
            case SDL_QUIT:
                quit();
                break;
            case SDL_KEYDOWN:
                if(_keys[_events.key.keysym.sym]!=1)
                    _changeKeys[_events.key.keysym.sym] = 1;
                _keys[_events.key.keysym.sym] = 1;
                break;
            case SDL_KEYUP:
                if(_keys[_events.key.keysym.sym]!=0)
                    _changeKeys[_events.key.keysym.sym] = 1;
                _keys[_events.key.keysym.sym] = 0;
                break;
        }
    }
}
bool Game::getClicked(int key)
{
    bool clicked = 0;

    if(_keys[key]&&_changeKeys[key])
        clicked = 1;
        _changeKeys[key] = 0;

    return clicked;
}
bool Game::getKeydown(int key)
{
    bool clicked = 0;

    if(_keys[key])
        clicked = 1;

    return clicked;
}
void Game::noticeError(const char* msg)
{
    std::cout << "[ERREUR] " << msg << std::endl;
    quit(-1);
}