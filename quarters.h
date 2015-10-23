//author: Boone Neligan
//
//class Quarters : public Room - implementation file 

#ifndef QUARTERS_H
#define QUARTERS_H

#include "room.h"

#include <string>

using std::string;


class Quarters : public Room {
protected:
	string victim;
	string traits;
public:
	Quarters(string, string, string);
	bool pickupVictim();
	Room* roomAction(Person*);
};

#endif