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


    _perso.addImage(_renderer,"images/Ninjas.png",10,6,90,135);
    _perso.setCycle(52,60);//mourir

    SDL_SetRenderDrawBlendMode(_renderer,SDL_BLENDMODE_BLEND);
}
Game::~Game(){
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
    SDL_SetRenderDrawColor(_renderer,255,255,255,0);
    SDL_RenderClear(_renderer);

    _perso.draw(_renderer,50,50);

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
                _keys[_events.key.keysym.sym] = 1;
                break;
            case SDL_KEYUP:
                _keys[_events.key.keysym.sym] = 0;
                break;
        }
    }
}
bool Game::getClicked(int key)
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