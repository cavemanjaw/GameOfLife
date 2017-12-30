# GameOfLife
File contains usefull commands discovered during development process:

//For compiling whole project, notice "-lgtest" is for linking with gTest library which utilities are in GameOfLife source project files
g++ GameOfLife.cpp GameOfLife.h main.cpp -o GameOfLife SimCell.h SimCell.cpp SimMatrix.h SimMatrix.cpp -g -std=c++11 -lgtest

//For gTest test compilation, note including main.cpp results in "undefined reference to symbol '_ZN7testing4TestC2Ev'":
//Can be fixed with placing test.cpp or other source files after g++
g++ -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread SimCell.h SimCell.cpp SimMatrix.h SimMatrix.cpp -std=c++11 -o tests

Should the test be addded to the repository?
The test should be added in some way to exclude them from repository?
Moduularise the tests!

"src" and "test" folder

make some script for building the application!

script for building and check for correctness of build command

TODO:
BUG in SetCellStatus(), fix it and set filling simulation setup rules for resprawning and killing cells
design GUI
design textual interface, invoking with specific options
BUG: Current bug that manifests in not correnct vaues of cells in simulation is propably because we are working on copy and not setting proper cell status in SetCellStatus
due to the fact, that functions that deal with state increase statistyics, such as the respawnCounter, but 
or it is not so...
