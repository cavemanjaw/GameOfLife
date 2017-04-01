CC=g++
CFLAGS=-I.

COMMON_SOURCES = 
TARGET_SOURCES = 
TEST_SOURCES = 

EXECUTABLE = GameOfLife
TEST_EXECUTABLE = Test

.PHONY: all target tests

all: target tests

target: $(EXECUTABLE)
tests: $(TEST_EXECUTABLE)

test: test/main_test.cpp test/SimCell_test.cpp src/SimCell.h src/SimCell.cpp
	g++ test/main_test.cpp test/SimCell_test.cpp src/SimCell.h src/SimCell.cpp -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread -std=c++11 -o Test

