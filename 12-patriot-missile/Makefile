CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall
PROGS = patriot

all: $(PROGS)

%: %.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)

.PHONY: all clean
