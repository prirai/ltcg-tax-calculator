CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20
DEBUGFLAGS = -g
OPTFLAGS = -O2

all: ltcg_debug ltcg_optimized

ltcg_debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $@ $<

ltcg_optimized: main.cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $<

clean:
	rm -f ltcg_debug ltcg_optimized

.PHONY: all clean
