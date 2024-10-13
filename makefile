CXX = g++
CXXFLAGS = -g -Wall -std=c++11

all: mt-collatz

mt-collatz: mt-collatz.cpp
    $(CXX) $(CXXFLAGS) -o mt-collatz mt-collatz.cpp

clean:
    rm -f mt-collatz

