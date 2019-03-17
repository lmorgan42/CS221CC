CXX = g++
CCFLAGS = -g -std=c++17

all: test_tree.o Tree.o
	$(CXX) -o test_tree test_tree.o Tree.o

%.o : %.cpp
	$(CXX) $(CCFLAGS) -c $<
	
clean:
	rm -f *.o