SRC=main.cpp input.cpp
OBJ=$(SRC:.cpp=.o)
FLAG1=-c -Wall -g
FLAG2=-lstdc++ -L../lib -lcartesian
EXE=run
CC=g++

all: $(OBJ)
	$(CC) $(OBJ) $(FLAG2) -o $(EXE)

.cpp.o:
	$(CC) $(FLAG1) $< -o $@

clean:
	rm -rf $(OBJ) $(EXE) vgcore*