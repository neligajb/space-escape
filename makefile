#makefile for Space Escape

exec: game.cpp person.h person.cpp room.h room.cpp technical.h technical.cpp quarters.cpp quarters.h escapePod.cpp escapePod.h basic.cpp basic.h
	g++ -std=c++0x -D_GLIBCXX_USE_NANOSLEEP game.cpp room.cpp person.cpp technical.cpp quarters.cpp escapePod.cpp basic.cpp -o game