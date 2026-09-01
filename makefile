CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: proj5.x

proj5.x: main.o passserver.o
	$(CXX) $(CXXFLAGS) -o proj5.x main.o passserver.o -lcrypt

xproj5.x: xmain.o passserver.o
	$(CXX) $(CXXFLAGS) -o xproj5.x xmain.o passserver.o -lcrypt

main.o: main.cpp passserver.h hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

xmain.o: xmain.cpp passserver.h hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -c xmain.cpp

passserver.o: passserver.cpp passserver.h hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -c passserver.cpp

clean:
	rm -f proj5.x xproj5.x main.o xmain.o passserver.o
