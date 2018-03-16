part:partition.cpp
	g++ -std=c++11 -fopenmp partition.cpp -o partition

check:checker.cpp
	g++ -std=c++11 -fopenmp checker.cpp -o checker