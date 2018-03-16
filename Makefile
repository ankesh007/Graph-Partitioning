part:partition.cpp
	g++ -std=c++11 -fopenmp partition.cpp -o partition

check:checker.cpp
	g++ -std=c++11 -fopenmp checker.cpp -o checker

complete:global_header.cpp partition.cpp global_header.h coarsening.cpp
	g++ -std=c++11 -fopenmp -I . global_header.cpp partition.cpp coarsening.cpp -o partition


complete_mac:global_header.cpp partition.cpp global_header.h coarsening.cpp
	g++-7 -std=c++11 -fopenmp -I . global_header.cpp partition.cpp coarsening.cpp -o partition
