CXX = g++
CXXFLAGS = -std=c++11 -Wall

main: main.cpp lib.cpp lib.h
	$(CXX) $(CXXFLAGS) -o main.cpp lib.cpp a.out

clean:
	rm -f a.out
