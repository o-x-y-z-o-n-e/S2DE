COMPILER = g++
BIN = bin/S2DE
COMPILER_FLAGS = -w

ifeq ($(OS),Windows_NT)
    LINKER_FLAGS = -IS2DE/src -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
else
    LINKER_FLAGS = -IS2DE/src -lSDL2 -lSDL2_image
endif


DIR1_H = $(wildcard S2DE/src/*.h)
DIR2_H = $(wildcard Example/src/*.h)

DIR1_C = $(wildcard S2DE/src/*.cpp)
DIR2_C = $(wildcard Example/src/*.cpp)


OBJS = $(DIR1_C) $(DIR1_H) $(DIR2_C) $(DIR2_H)

all : $(OBJS)
	$(COMPILER) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN)
