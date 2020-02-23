OBJS=main.cpp game.cpp draw.cpp object.cpp
OBJ_NAME=app
COMPILER=g++
LINKER_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image

all: $(OBJS)
	$(COMPILER) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)
