CXX=g++
CXXFLAGS=-std=c++2a -pedantic -Wall -Wextra -Wshadow -O3

.PHONY: all clean

all: icomp_benchmark test_icomp test

%.o: %.cpp Makefile
	$(CXX) $< -c $(CXXFLAGS) -isystem ../../../lib/benchmark/include -isystem ../../../lib/benchmark/googletest/googletest/include -o $@

icomp_benchmark: main.o icomp.hpp
	$(CXX) $< $(CXXFLAGS) -L ../../../lib/benchmark/build/src -lbenchmark_main -lbenchmark -pthread -o $@

test_icomp: test_icomp.o icomp.hpp
	$(CXX) $< $(CXXFLAGS) -L../../../lib/benchmark/build/lib -lgtest -pthread -o $@

test: test_icomp
	@./test_icomp

clean:
	@rm -f *.o test_icomp icomp_benchmark
