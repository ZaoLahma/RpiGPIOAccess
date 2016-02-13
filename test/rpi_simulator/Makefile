CCOMMAND = g++
CFLAGS = -Wall -c -Wextra --std=c++11 
LINKARGS = -lpthread
SRC_FILES = ./src/*.cpp ../../src/*.cpp
TEST_FILES = ./test/*.cpp
INC_DIRS = -I./inc -I../../inc
EXE_NAME = gpio_sim_test

all: test link

test: compile
	$(CCOMMAND) $(CFLAGS) $(INC_DIRS) $(TEST_FILES)

compile:
	$(CCOMMAND) $(CFLAGS) $(INC_DIRS) $(SRC_FILES)
	
link:
	$(CCOMMAND) -o $(EXE_NAME) ./*.o $(LINKARGS)
	
clean:
	rm -rf ./*.o
	rm ./$(EXE_NAME)