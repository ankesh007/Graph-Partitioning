HEADER_DIR=.
OBJDIR=obj
LIBS=-std=c++11 -fopenmp
SRCS=coarsening.cpp global_header.cpp partition.cpp gggp.cpp decoarsening.cpp
DEPS = $(wildcard $(HEADER_DIR)/*.h)
# OBJ =coarsening.o global_header.o partition.o gggp.o decoarsening.o
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

checker:checker.cpp $(DEPS)
	g++ $(LIBS) checker.cpp -o $@

$(OBJDIR)/%.o: %.cpp $(DEPS) | $(OBJDIR)
	g++ $(LIBS) -c -I . -o $@ $< 

partition: $(OBJS) 
	g++ $(LIBS) -I . $^ -o $@

complete_mac:$(SRCS) $(DEPS)
	g++-7 $(LIBS) -I . $(SRCS) -o partition

clean:
	rm -rf ./$(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

# naive_partition:partition.cpp $(DEPS)
# 	g++	$(LIBS) -I . partition.cpp -o $@