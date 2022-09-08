CXX=clang++
INCLUDES=-Iincludes/ -Ilib/ -Iutilities/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++14 -g -fstandalone-debug

exec: src/main.cpp src/parser.cpp src/searches/BFS.cpp src/searches/IDDFS.cpp src/searches/BeFS.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o exec

tests: tests/tests.cpp tests/catch/catchmain.cpp src/parser.cpp src/searches/BFS.cpp src/searches/IDDFS.cpp src/searches/BeFS.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o test

benchmark: tests/benchmarks.cpp src/parser.cpp src/searches/BFS.cpp src/searches/IDDFS.cpp src/searches/BeFS.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o benchmark

.DEFAULT_GOAL := exec
.PHONY: clean exec tests benchmark

clean:
	rm -rf obj/* exec test benchmark