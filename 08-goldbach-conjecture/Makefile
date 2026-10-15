CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall
PROGS = goldbach verifica cometa

all: $(PROGS)

%: %.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)

.PHONY: all clean
