#include "game.h"
using namespace std;

Game::Game():_window(NULL),_state(1),_renderer(NULL),_actuelFPS(FPS),_level(0),_endGame(0),_world(NULL),_menu(NULL){

    if(SDL_Init(SDL_INIT_VIDEO)<0)
        noticeError("problème de init()");

    if(TTF_Init()<0)
        noticeError("problème de initTTF()");

    if(SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&_window,&_renderer)<0);
        noticeError("problème de createRenderer()");

    _font = TTF_OpenFont("resources/pixel_font.ttf",20);

    init();

    //bug getCLicked

    SDL_SetRenderDrawBlendMode(_renderer,SDL_BLENDMODE_BLEND);
}
Game::~Game(){
    TTF_CloseFont(_font);
    delete _menu;
    delete _world;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    TTF_Quit();
    SDL_Quit();
}
void Game::init()
{
    delete _menu;
    _menu = new Menu(_renderer);

    _level = 0;
    _endGame = 0;
    _state = 1;

    loadMap("resources/levels");
    nextLevel();
}
void Game::nextLevel()
{  
    if(_listMap.size()>_level)
    {
        delete _world;
        _world = new World(_renderer,_listMap[_level].c_str());
        _menu->setText(_font,_levelTexture,&_rectLevel,(string("Level ")+to_string(_level+1)).c_str(),50,HEIGHT-30);
        _level++;
    }
    else
        SDL_Log("Plus de map!");
    
}
void Game::initLevel()
{
        delete _world;
        _world = new World(_renderer,_listMap[_level-1].c_str());
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
    //trie ordre alphabétique
    sort(_listMap.begin(),_listMap.end());
}
void Game::core(){
    while(_state==1)
    {
        _start = SDL_GetTicks();
        manageEvent();
        //keyboard events
        if(getClicked(SDLK_ESCAPE))
            quit();

        if(_world->isFinish()==0)
        {
            if(getKeydown(RIGHT_KEY))
                _world->getPerso()->turnRight(9,13);
            else if(getKeydown(LEFT_KEY))
                _world->getPerso()->turnLeft(9,13);
            if(getClicked(JUMP_KEY))
                _world->getPerso()->jump();
            if(!getKeydown(LEFT_KEY)&&!getKeydown(RIGHT_KEY))
                _world->getPerso()->stopMoving(0,3);
        }
        else if(getKeydown(SDLK_RETURN)&&_world->isFinish()==1&&_endGame==0)
                nextLevel();
        else if(getKeydown(SDLK_RETURN)&&_world->isFinish()==1&&_endGame==1)
                init();
        else if(getKeydown(SDLK_RETURN)&&_world->isFinish()==-1)
                initLevel();
        
        //check level
        if(_listMap.size()==_level)
            _endGame = 1;

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

    if(_menu->isStarted())
    {
        _world->draw(_actuelFPS);
        if(_world->isFinish()==1&&_endGame)
            _menu->drawEndGame();
        else if(_world->isFinish()==1)//reussi
            _menu->drawFinish();
        else if(_world->isFinish()==-1)//dead
            _menu->drawDead();
        else
            SDL_RenderCopy(_renderer,_levelTexture,NULL,&_rectLevel);
    }
    else
        _menu->drawStart();
    
    drawFps();

    SDL_RenderPresent(_renderer);
}
void Game::drawFps()
{
    SDL_Surface *texte = TTF_RenderText_Solid(_font,to_string(int(_actuelFPS)).c_str(),SDL_Color{0,0,0,255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer,texte);
    SDL_FreeSurface(texte);
    int w,h;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    SDL_Rect rect = {30,30,w,h};
    SDL_RenderCopy(_renderer,texture,NULL,&rect);
    SDL_DestroyTexture(texture);
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
        _menu->manageClick(_events);
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