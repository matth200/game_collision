OBJS=main.cpp game.cpp
OBJ_NAME=app
COMPILER=g++
LINKER_FLAGS=`sdl2-config --cflags --libs`

all: $(OBJS)
	$(COMPILER) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)
