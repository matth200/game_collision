#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>

#define WIDTH 1280
#define HEIGHT 720

#define FPS 30.0

class Game
 {
    public:
        Game();
        ~Game();
        void core();
        void manageKeyboard();
        bool getClicked(int key);
        void noticeError(const char* msg);
        bool getState()const {return _state;}
    protected:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _events;
        std::map<int,bool> _keys;
        bool _state;
 };

#endif