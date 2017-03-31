test: test/main_test.cpp test/SimCell_test.cpp src/SimCell.h src/SimCell.cpp
	g++ test/main_test.cpp test/SimCell_test.cpp src/SimCell.h src/SimCell.cpp -I $GTEST_HOME/include -L $GTEST_HOME/lib -lgtest -lgtest_main -lpthread -std=c++11 -o Test

