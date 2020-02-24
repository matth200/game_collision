#include "game.h"
using namespace std;

Game::Game():_window(NULL),_state(1),_renderer(NULL),_actuelFPS(FPS){

    if(SDL_Init(SDL_INIT_VIDEO)<0)
        noticeError("problème de init()");

    if(TTF_Init()<0)
        noticeError("problème de initTTF()");

    _window = SDL_CreateWindow("Test de fenêtre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if( _window == NULL)
        noticeError("problème de createWindow()");
    
    _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED);
    if(_renderer == NULL)
        noticeError("problème de createRenderer()");

    loadMap("levels");
    _world = new World(_renderer,_listMap[1].c_str());

    SDL_SetRenderDrawBlendMode(_renderer,SDL_BLENDMODE_BLEND);
}
Game::~Game(){
    delete _world;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    TTF_Quit();
    SDL_Quit();
}
void Game::loadMap(const char *folder)
{
    std::filesystem::directory_iterator folderPath(folder);

    _listMap.clear();
    _listMap.resize(0);
    for( auto& file : folderPath)
    {
        _listMap.push_back(string(file.path()));
        SDL_Log((string("file:")+string(file.path())).c_str());
    }
}
void Game::core(){
    while(_state==1)
    {
        _start = SDL_GetTicks();
        manageEvent();
        //keyboard events
        if(getClicked(SDLK_ESCAPE))
            quit();

        if(getKeydown(RIGHT_KEY))
            _world->getPerso()->turnRight(9,13);
        else if(getKeydown(LEFT_KEY))
            _world->getPerso()->turnLeft(9,13);
        if(getClicked(JUMP_KEY))
            _world->getPerso()->jump();
        if(!getKeydown(LEFT_KEY)&&!getKeydown(RIGHT_KEY))
            _world->getPerso()->stopMoving(0,3);
            
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

    _world->draw(_actuelFPS);

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