OBJS=main.cpp game.cpp draw.cpp object.cpp maploader.cpp world.cpp menu.cpp
OBJ_NAME=app
COMPILER=g++
LINKER_OPTS=--std=c++17
LINKER_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

all: $(OBJ_NAME)

$(OBJ_NAME): main.o game.o draw.o object.o maploader.o world.o menu.o
	$(COMPILER) -o $@ $^ $(LINKER_OPTS) $(LINKER_FLAGS)

game.o: game.cpp game.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

draw.o: draw.cpp draw.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

object.o: object.cpp object.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

maploader.o: maploader.cpp maploader.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

world.o: world.cpp world.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

menu.o: menu.cpp menu.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(OBJ_NAME)
