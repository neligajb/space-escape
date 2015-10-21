//Final Project - Space Escape
//CS 162 - Fall 2014
//author: Boone Neligan
//
//class Basic : public Room - implementation file 

#include "room.h"
#include "basic.h"
#include "person.h"

#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


//Basic constructor sets the name and a string of room "text".
//Member "text" goes unused in the current implemention
Basic::Basic(string room_name, string room_text) : Room(room_name) {
	text = room_text;
}


//Overrides the virtual function in Room parent class.  Takes a pointer
//to a type Person and returns a Room pointer (used primarily in warping cases)
Room* Basic::roomAction(Person* p) {
	if (!p->getCompleted()) {
		cout << endl;
		cout << "You are in the " << room_name << endl;
		cout << "***************";
		for (int i = 0; i < room_name.length(); i++) {
			cout << "*";
		} 
		p->showItems();
	}
	else {
		cout << text;
	}
	return this;
}