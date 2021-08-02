COMPILER = g++
BIN = bin/S2DE
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image

DIR1_H = $(wildcard S2DE/src/*.h)
DIR2_H = $(wildcard S2DE/src/Test/*.h)

DIR1_C = $(wildcard S2DE/src/*.cpp)
DIR2_C = $(wildcard S2DE/src/Test/*.cpp)


OBJS = $(DIR1_C) $(DIR1_H) $(DIR2_C) $(DIR2_H)

all : $(OBJS)
	$(COMPILER) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN)
