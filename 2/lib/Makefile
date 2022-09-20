SRC=cartesian.cpp
OBJ=$(SRC:.cpp=.o)
FLAG1=-c -Wall -g
FLAG2=-lstdc++
FLAG3=rc
LIB=cartesian
CC=g++

all: lib
	ranlib lib$(LIB).a
	

lib: $(OBJ)
	ar $(FLAG3) lib$(LIB).a $(OBJ)

.cpp.o:
	$(CC) $(FLAG1) $< -o $@

clean:
	rm -rf $(OBJ)