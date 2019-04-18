CXX=g++-8
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O3 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

random: cities.o tsp.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o