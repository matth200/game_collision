#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <SDL2/SDL.h>

class Game
 {
    public:
        Game():_window(NULL){
            _state = 1;
            if(SDL_Init(SDL_INIT_VIDEO)<0)
                noticeError("problème de init()");
            _window = SDL_CreateWindow("Test de fenétre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,400,SDL_WINDOW_SHOWN);
            if( _window == NULL)
                noticeError("problème de createWindow()");
        }
        ~Game(){
            SDL_DestroyWindow(_window);
            SDL_Quit();
        }
        void core(){
            while(_state==1)
            {
                SDL_WaitEvent(&_events);
                if(_events.type == SDL_QUIT)
                    _state = 0;
            }
        }
        void noticeError(const char* msg)
        {
            cout << "[ERREUR] " << msg << endl;
            _state = -1;
        }
        bool getState()const {return _state;}
    protected:
        SDL_Window *_window;
        SDL_Event _events;
        bool _state;
 };

#endif