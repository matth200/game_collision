#include "game.h"
using namespace std;

Game::Game():_window(NULL),_state(1),_renderer(NULL){

    if(SDL_Init(SDL_INIT_VIDEO)<0)
        noticeError("problème de init()");

    _window = SDL_CreateWindow("Test de fenêtre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if( _window == NULL)
        noticeError("problème de createWindow()");
    
    _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED);
    if(_renderer == NULL)
        noticeError("problème de createRenderer()");

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
        manageKeyboard();
        if(getClicked(SDLK_RETURN))
            SDL_Log("Appuye sur enter");

        
        SDL_SetRenderDrawColor(_renderer,255,255,255,0);
        SDL_RenderClear(_renderer);

        SDL_RenderPresent(_renderer);
    }
}
void Game::manageKeyboard()
{
    SDL_WaitEvent(&_events);
    switch (_events.type)
    {
        case SDL_QUIT:
            _state = 0;
            break;
        case SDL_KEYDOWN:
            _keys[_events.key.keysym.sym] = 1;
            break;
        case SDL_KEYUP:
            _keys[_events.key.keysym.sym] = 0;
            break;
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
    _state = -1;
}