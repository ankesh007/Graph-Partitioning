LIBS=-std=c++11 -fopenmp
SRCS=coarsening.cpp global_header.cpp partition.cpp gggp.cpp
HEADER=global_header.h
LIBS=-std=c++11 -fopenmp

# naive_partition:partition.cpp $(HEADER)
# 	g++	$(LIBS) -I . partition.cpp -o $@

checker:checker.cpp $(HEADER)
	g++ $(LIBS) checker.cpp -o $@

partition:$(SRCS) $(HEADER)
	g++ $(LIBS) -I . $(SRCS) -o $@

complete_mac:$(SRCS) $(HEADER)
	g++-7 $(LIBS) -I . $(SRCS) -o partition