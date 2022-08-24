.PHONY:all clean clean-all

OBJS=main.cpp game.cpp draw.cpp object.cpp maploader.cpp world.cpp menu.cpp
COMPILER=g++
LINKER_OPTS=--std=c++17
LINKER_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf
SRC_DIRECTORY=src
BIN_DIRECTORY=bin
OBJ_NAME=$(BIN_DIRECTORY)/app

all: $(OBJ_NAME)

$(OBJ_NAME): $(BIN_DIRECTORY)/main.o $(BIN_DIRECTORY)/game.o $(BIN_DIRECTORY)/draw.o $(BIN_DIRECTORY)/object.o $(BIN_DIRECTORY)/maploader.o $(BIN_DIRECTORY)/world.o $(BIN_DIRECTORY)/menu.o
	$(COMPILER) -o $@ $^ $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/game.o: $(SRC_DIRECTORY)/game.cpp $(SRC_DIRECTORY)/game.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/draw.o: $(SRC_DIRECTORY)/draw.cpp $(SRC_DIRECTORY)/draw.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/object.o: $(SRC_DIRECTORY)/object.cpp $(SRC_DIRECTORY)/object.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/maploader.o: $(SRC_DIRECTORY)/maploader.cpp $(SRC_DIRECTORY)/maploader.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/world.o: $(SRC_DIRECTORY)/world.cpp $(SRC_DIRECTORY)/world.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/menu.o: $(SRC_DIRECTORY)/menu.cpp $(SRC_DIRECTORY)/menu.h
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

$(BIN_DIRECTORY)/main.o: main.cpp
	$(COMPILER) -o $@ -c $< $(LINKER_OPTS) $(LINKER_FLAGS)

clean:
	rm -f $(BIN_DIRECTORY)/*.o

clean-all: clean
	rm -f $(OBJ_NAME)
