#include "maploader.h"
using namespace std;

MapLoader::MapLoader(const char *filename):_nbrX(0),_nbrY(0),_square_w(0),_square_h(0),_map_filename(filename),_xStart(0),_yStart(0),_xEnd(0),_yEnd(0)
{
    srand(time(NULL));
    _pageMax = 0;
    _actualPage = 0;


}
MapLoader::~MapLoader()
{
    for( auto ob : _objects)
        delete ob;
}

std::vector<Object*>* MapLoader::getObjects()
{
    return &_objects;
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
        string line = "";
        getline(mapFile,line);

        if(!regex_search(line,reps,regex("([0-9]+) ([0-9]+) ([0-9]+)")))
        {
            SDL_Log("fichier incorrect");
            return 0;
        }   
        _nbrX = stoi(reps[1]);
        _nbrY = stoi(reps[2]);
        _pageMax = stoi(reps[3]);
        SDL_Log((string("Taille de la carte : ")+to_string(_nbrX)+"*"+to_string(_nbrY)).c_str());
        

        //lecture de une page
        line = "";
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

    loadObjects();

    return 1;
}
void MapLoader::loadObjects()
{
    //add map inside _objects
    for(int i(0);i<_map.size();i++)
    {
        int x = (i%_nbrX)*_square_w, y = int(i/_nbrX)*_square_h;
        Object *ob = NULL;
        switch(_map[i])
        {
            case 1://bloc normal
                ob = new Object(x,y,_square_w,_square_h);
                ob->setId(1);
                _objects.push_back(ob);
                break;
            case 3://bloc de fin
                ob = new Object(x,y,_square_w,_square_h);
                ob->setId(3);
                _objects.push_back(ob);
                break;
            case 4://bloc dynamique
                ob = new Object(x,y,_square_w,_square_h);
                ob->setId(4);
                _objects.push_back(ob);
                break;
            case 5://bloc dynamique
                ob = new Object(x,y,_square_w,_square_h);
                ob->setId(5);
                _objects.push_back(ob);
                break;

        }
    }
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
void MapLoader::drawMap(SDL_Renderer *renderer)
{
    for(int i(0);i<_objects.size();i++)
    {
        int x = _objects[i]->getPosX(), y = _objects[i]->getPosY();
        if(x+_square_w<0||x>WIDTH||y+_square_h<0||y>HEIGHT)//Stop mouvement because he is out of screen
            _objects[i]->setOutOfScreen(1);
        SDL_Rect rect = {x,y,_square_w,_square_h};
        if(_objects[i]->getOutOfScreen()==0)
        {
            switch(_objects[i]->getId())
            {
                case 1:
                    _objects[i]->draw(renderer,150,100,150);
                    break;
                case 3:
                    _objects[i]->draw(renderer,10,10,10);
                    break;
                case 4:
                    _objects[i]->draw(renderer,0,255,255);
                    break;
                case 5:
                    _objects[i]->draw(renderer,255,255,0);
                    break;
            }
        }
    }
}