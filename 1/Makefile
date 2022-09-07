SRC=main.cpp vector.cpp matrix.cpp
OBJ=$(SRC:.cpp=.o)
FLAG1=-c -Wall -g
FLAG2=-lstdc++
EXE=run
CC=g++

all: $(OBJ)
	$(CC) $(OBJ) $(FLAG2) -o $(EXE)

.cpp.o:
	$(CC) $(FLAG1) $< -o $@

clean:
	rm -rf $(OBJ) $(EXE) vgcore*