//Final Project - Space Escape
//CS 162 - Fall 2014
//author: Boone Neligan
//
//class Room - header file 

#ifndef ROOM_H
#define ROOM_H

#include "person.h"

#include <string>

using std::string;

struct Item;
class Person;
class EscapePod;

class Room {
protected:
	Room* N;
	Room* S;
	Room* E;
	Room* W;
	Room* warp;
	EscapePod* escape_pod;
	Room* end;
	string room_name;
public:
	Room(string);
	void setConnected(Room*, Room*, Room*, Room*, Room*, EscapePod*, Room*);
	virtual Room* move();
	virtual Room* roomAction(Person*) = 0;
};


#endif