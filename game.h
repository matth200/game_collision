#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <map>
#include <filesystem>

#include "menu.h"
#include "draw.h"
#include "world.h"

#define RIGHT_KEY SDLK_d
#define LEFT_KEY SDLK_q
#define JUMP_KEY SDLK_SPACE

#define FPS 30.0

class Game
 {
    public:
        Game();
        ~Game();
        void init();
        void core();
        void quit(int state=0){_state=state;}

        void loadMap(const char* folder);
        void manageEvent();
        void nextLevel();
        void initLevel();
        void draw();
        void drawFps();
        void drawLevelIndication();
        bool getClicked(int key);
        bool getKeydown(int key);
        void noticeError(const char* msg);
        bool getState()const {return _state;}
    protected:
        World *_world;
        Menu *_menu;

        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _events;
        unsigned int _start;
        std::map<int,bool> _keys, _changeKeys;
        std::vector<std::string> _listMap;
        double _actuelFPS;
        bool _state;
        TTF_Font *_font;
        int _level;
        bool _endGame;

        SDL_Texture *_levelTexture;
        SDL_Rect _rectLevel;
 };

#endif