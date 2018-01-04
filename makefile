#CC=g++
#CFLAGS=-I.
#
#COMMON_SOURCES = SimCell.cpp
#TARGET_SOURCES = main.cpp SimMatrix.cpp GameOfLife.cpp
#TEST_SOURCES = main_test.cpp SimCell_test.cpp 
#
#COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)
#TARGET_OBJECTS = $(TARGET_SOURCES:.cpp=.o)
#TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
#
#EXECUTABLE = GameOfLife
#TEST_EXECUTABLE = Test
#
#.PHONY: all target tests
#
#all: target tests
#
#target: $(EXECUTABLE)
#tests: $(TEST_EXECUTABLE)
#
#
#$(EXECUTABLE): $(COMMON_OBJECTS) $(TARGET_OBJECTS)
#	$(CC) $(LDFLAGS) $^ -o $@
#
#$(TEST_EXECUTABLE): $(COMMON_OBJECTS) $(TEST_OBJECTS)
#	$(CC) $(LDFLAGS) $^ -o $@
#
#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@
#


EXECUTABLE := GameOfLife
TEST_EXECUTABLE := Test

.PHONY: all target test

CXX := g++
CXXFLAGS := -Wall -g3
CXXFLAGS := -Wall -std=c++11

TARGET_SOURCES := $(shell find . -maxdepth 1 -name "*.cpp")
TARGET_OBJECTS := $(patsubst %.cpp, %.o, $(TARGET_SOURCES))

TEST_SOURCES := $(shell find . -maxdepth 1 -name "*.cpp")
TEST_OBJECTS := $(patsubst %.cpp, %.o, $(TARGET_SOURCES))

all: target test

target: $(EXECUTABLE)
test: $(TEST_EXECUTABLE)

$(EXECUTABLE): $(TARGET_OBJECTS)
	    $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(TARGET_OBJECTS) $(LDLIBS)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	    $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TEST_EXECUTABLE) $(TEST_OBJECTS) $(LDLIBS)

depend: .depend

.depend: $(TARGET_SOURCES)
	    rm -f ./.depend
	        $(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	    rm -f $(TARGET_OBJECTS)

dist-clean: clean
	   rm -f *~ .depend

include .depend
