#include "maploader.h"
using namespace std;

MapLoader::MapLoader(const char *filename):_nbrX(0),_nbrY(0),_square_w(0),_square_h(0),_map_filename(filename),_xStart(0),_yStart(0),_xEnd(0),_yEnd(0)
{
    srand(time(NULL));
}
MapLoader::~MapLoader()
{
}

bool MapLoader::load(int square_w, int square_h)
{ 
    ifstream mapFile(_map_filename);
    if(!mapFile.is_open())
    {
        SDL_Log("Fichier non trouvé");
        return 0;
    }
    else{
        smatch reps;
        string line;getline(mapFile,line);

        if(!regex_search(line,reps,regex("([0-9]+) ([0-9]+)")))
        {
            SDL_Log("fichier incorrect");
            return 0;
        }   
        _nbrX = stoi(reps[1]);
        _nbrY = stoi(reps[2]);
        SDL_Log((string("Taille de la carte : ")+to_string(_nbrX)+"*"+to_string(_nbrY)).c_str());

        getline(mapFile,line);
        int page = stoi(line);

        for(int i(0);i<_nbrY;i++)
        {
            getline(mapFile,line);
            if(line.size()!=_nbrX)
            {
                SDL_Log("largeur incohérente de la map");
                return 0;
            }

            for(auto c : line)
            {
                string t;t+=c;
                _map.push_back((unsigned char)(stoi(t)));
            }
        }
        if(_map.size()!=_nbrY*_nbrX)
        {
            SDL_Log("Erreur de taille de map");
            return 0;
        }
    }
    _square_w = square_w;
    _square_h = square_h;
    //get the start and end pos
    for(int i(0);i<_map.size();i++)
    {
        int x = (i%_nbrX)*_square_w, y = int(i/_nbrX)*_square_h;
        SDL_Rect rect = {x,y,_square_w,_square_h};
        switch(_map[i])
        {
            case 2:
                //SDL_Log((string("x:")+to_string(x)+" y:"+to_string(y)).c_str());
                _xStart = x;
                _yStart = y;
                break;
            case 3:
                _xEnd = x;
                _yEnd = y;
                break;
        }
    }
    return 1;
}
void MapLoader::getSize(int &nbrX, int &nbrY)
{
    nbrX = _nbrX;
    nbrY = _nbrY;
}
vector<unsigned char>* MapLoader::getMap()
{
    return &_map;
}
bool MapLoader::isLoad()
{
    return (_square_w!=0&&_square_h!=0&&_map.size()>0);
}
void MapLoader::getPosToStart(int &x, int &y)
{
    x = _xStart;
    y = _yStart;
}
void MapLoader::getPosEnd(int &x, int &y)
{
    x = _xEnd;
    y = _yEnd;
}
bool MapLoader::isFinish(int x, int y)
{
    SDL_Rect rect = {x,y,_square_w,_square_h};
    
    return 0;
}

void MapLoader::drawMap(SDL_Renderer *renderer)
{
    for(int i(0);i<_map.size();i++)
    {
        int x = (i%_nbrX)*_square_w, y = int(i/_nbrX)*_square_h;
        SDL_Rect rect = {x,y,_square_w,_square_h};
        switch(_map[i])
        {
            case 1:
                SDL_SetRenderDrawColor(renderer,150,100,150,255);
                SDL_RenderFillRect(renderer,&rect);
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer,10,10,10,255);
                SDL_RenderFillRect(renderer,&rect);
                break;
            case 4:
                SDL_SetRenderDrawColor(renderer,0,255,255,255);
                SDL_RenderFillRect(renderer,&rect);
                break;
        }
    }
}