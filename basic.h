//author: Boone Neligan
//
//class Basic : public Room - header file 

#ifndef BASIC_H
#define BASIC_H

#include "room.h"

#include <string>

using std::string;


class Basic : public Room {
protected:
	string text;
public:
	Basic(string, string);
	Room* roomAction(Person*);
};

#endif