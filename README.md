# GameOfLife
File contains usefull commands discovered during development process:

//For compiling whole project, notice "-lgtest" is for linking with gTest library which utilities are in GameOfLife source project files
g++ GameOfLife.cpp GameOfLife.h main.cpp -o GameOfLife SimCell.h SimCell.cpp SimMatrix.h SimMatrix.cpp -g -std=c++11 -lgtest

//For gTest test compilation, note including main.cpp results in "undefined reference to symbol '_ZN7testing4TestC2Ev'":
g++ -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread SimCell.h SimCell.cpp SimMatrix.h SimMatrix.cpp -std=c++11 -o tests
