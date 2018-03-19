HEADER_DIR=.
OBJDIR=obj
LIBS=-std=c++11 -fopenmp
SRCS=coarsening.cpp global_header.cpp partition.cpp gggp.cpp decoarseningSet.cpp
DEPS = $(wildcard $(HEADER_DIR)/*.h)
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))

checker:checker.cpp $(DEPS)
	g++ $(LIBS) checker.cpp -o $@ -O3

$(OBJDIR)/%.o: %.cpp $(DEPS) | $(OBJDIR)
	g++ $(LIBS) -c -I . -o $@ $< -O3

partition: $(OBJS) 
	g++ $(LIBS) -I . $^ -o $@ -O3

complete_mac:$(SRCS) $(DEPS)
	g++-7 $(LIBS) -I . $(SRCS) -o partition -O3

clean:
	rm -rf ./$(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

# naive_partition:partition.cpp $(DEPS)
# 	g++	$(LIBS) -I . partition.cpp -o $@