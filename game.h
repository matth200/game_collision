#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <SDL2/SDL.h>
#include <iostream>
#include <map>

#include "draw.h"
#include "object.h"

#define WIDTH 1280
#define HEIGHT 720

#define FPS 60.0

class Game
 {
    public:
        Game();
        ~Game();
        void core();
        void quit(int state=0){_state=state;}

        void manageEvent();
        void draw();
        bool getClicked(int key);
        bool getKeydown(int key);
        void noticeError(const char* msg);
        bool getState()const {return _state;}
    protected:
        Perso *_perso;

        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _events;
        unsigned int _start;
        std::map<int,bool> _keys, _changeKeys;
        double _actuelFPS;
        bool _state;
 };

#endif