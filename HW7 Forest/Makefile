CXX = g++
CCFLAGS = -g -std=c++17 -Wall -Wextra -pedantic

forest: htree.o test_hforest.o hforest.o
	$(CXX) -o test_hforest test_hforest.o hforest.o htree.o
	
tree: htree.o test_htree.o
	$(CXX) -o test_htree test_htree.o htree.o

%.o : %.cpp
	$(CXX) $(CCFLAGS) -c $<
	
clean:
	rm -f *.o