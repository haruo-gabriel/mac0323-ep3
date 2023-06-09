CXX = g++
CXXFLAGS = -std=c++11 -Wall

main: main.cpp lib.cpp lib.h
	$(CXX) $(CXXFLAGS) -o main main.cpp lib.cpp

clean:
	rm -f main
