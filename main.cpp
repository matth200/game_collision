#include <SDL2/SDL.h>
#include <iostream>

#include "src/game.h"

using namespace std;

int main(int argc, char *argv[])
{
  Game g;
  g.core();
  return g.getState();
}