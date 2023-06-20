CXX = g++
CXXFLAGS = -std=c++11 -Wall

main: main.cpp lib.h
	$(CXX) $(CXXFLAGS) -o main.cpp a.out

clean:
	rm -f a.out
