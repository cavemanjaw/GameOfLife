CC=g++
CFLAGS=-I.

COMMON_SOURCES = SimCell.cpp
TARGET_SOURCES = main.cpp SimMatrix.cpp GameOfLife.cpp
TEST_SOURCES = main_test.cpp SimCell_test.cpp 

COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)
TARGET_OBJECTS = $(TARGET_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

EXECUTABLE = GameOfLife
TEST_EXECUTABLE = Test

.PHONY: all target tests

all: target tests

target: $(EXECUTABLE)
tests: $(TEST_EXECUTABLE)


$(EXECUTABLE): $(COMMON_OBJECTS) $(TARGET_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TEST_EXECUTABLE): $(COMMON_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


