OBJS=main.cpp game.cpp draw.cpp object.cpp maploader.cpp world.cpp
OBJ_NAME=app
COMPILER=g++
LINKER_OPTS=
LINKER_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image

all: $(OBJS)
	$(COMPILER) -o $(OBJ_NAME) $(OBJS) $(LINKER_OPTS) $(LINKER_FLAGS)
