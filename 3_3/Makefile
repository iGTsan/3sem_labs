APP_SRC=app/app.cpp
LIB_SRC=lib/words.cpp lib/input.cpp
TEST_SRC=test/test.cpp
LIB_OBJ=$(LIB_SRC:.cpp=.o)
APP_OBJ=$(APP_SRC:.cpp=.o)
TEST_OBJ=$(TEST_SRC:.cpp=.o)
FLAG_O=-c -Wall -g
FLAG_C=-lstdc++ -lgtest
APP=run
TEST=run_test
CC=g++

all: app test
	@echo build all

test: $(TEST_OBJ) $(LIB_OBJ)
	$(CC) $(TEST_OBJ) $(LIB_OBJ) -o $(TEST) $(FLAG_C)

app: $(APP_OBJ) $(LIB_OBJ)
	$(CC) $(APP_OBJ) $(LIB_OBJ) -o $(APP) $(FLAG_C)

.cpp.o:
	$(CC) $(FLAG_O) $< -o $@

clean:
	rm -rf $(LIB_OBJ) $(TEST_OBJ) $(APP_OBJ) $(EXE) vgcore*