CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lcrypt

all: main.x xmain.x

main.x: main.cpp passserver.cpp
	$(CXX) $(CXXFLAGS) -o main.x main.cpp passserver.cpp $(LIBS)

xmain.x: xmain.cpp passserver.cpp
	$(CXX) $(CXXFLAGS) -o xmain.x xmain.cpp passserver.cpp $(LIBS)

clean:
	rm -f main.x xmain.x
