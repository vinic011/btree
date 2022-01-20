SRC := $(shell find . -name '*.cpp')
HEADER := $(shell find . -name '*.hpp')

CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lm

all: program

run: program
	./program

program: $(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(SRC)
