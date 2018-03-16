part:partition.cpp
	g++ -std=c++11 -fopenmp partition.cpp -o partition

check:checker.cpp
	g++ -std=c++11 -fopenmp checker.cpp -o checker

complete:global_header.cpp partition.cpp global_header.h
	g++ -std=c++11 -fopenmp -I . global_header.cpp partition.cpp -o partition