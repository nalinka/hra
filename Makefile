main: main.cpp ship.h ship.cpp world.h world.cpp ship_ai.h ship_ai.cpp
	g++ main.cpp world.cpp ship.cpp -o main -O3 -std=c++0x
