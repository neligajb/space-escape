//author: Boone Neligan
//
//class EscapePod : public Room - header file 

#ifndef ESCAPEPOD_H
#define ESCAPEPOD_H

#include "room.h"

#include <string>

using std::string;


class EscapePod : public Room {
protected:
	string passenger1;
	string passenger2;
	int passenger_count;
	bool electric_fixed;
	bool mechanical_fixed;
	bool electric_msg;
	bool mechanical_msg;
public:
	EscapePod(string);
	bool hasKey(Person*);
	bool hasWrench(Person*);
	bool hasIron(Person*);
	void setPassenger1(string);
	void setPassenger2(string);
	bool addPassenger(string);
	bool launchPod(Person*);
	Room* move();
	Room* roomAction(Person*);
};

#endif