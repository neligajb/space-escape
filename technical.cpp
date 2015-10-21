//Final Project - Space Escape
//CS 162 - Fall 2014
//author: Boone Neligan
//
//class Technical : public Room - implementation file 

#include "room.h"
#include "technical.h"
#include "person.h"

#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


//Takes a string for the Room name and the item name
//sets item location to a pointer to the calling object
Technical::Technical(string room_name, string item_name) : Room(room_name) {
	room_item.name = item_name;
	room_item.location = this;
}


Item Technical::getRoomItem() {
	return room_item;
}


void Technical::setRoomItem(Item i) {
	room_item = i;
}


//returns true if the user decides to pick up a room item
//esle, returns false
bool Technical::grabRoomItem() {
	char input;
	do {
		cin >> input;
		if (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
			cout << "Invalid input.  Grab item? (y/n)... ";
		}
	} while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');

	cout << endl;

	if (input == 'y' || input == 'Y') {
		return true;
	}
	else {
		return false;
	}
}


//Overrides the virtual function in Room parent class.  Takes a pointer
//to a type Person and returns a Room pointer (used primarily in warping cases)
Room* Technical::roomAction(Person* p) {
	cout << endl;
	cout << "You are in the " << room_name << endl;
	cout << "***************";
	for (int i = 0; i < room_name.length(); i++) {
		cout << "*";
	} 
	p->showItems();
	cout << "You take a quick look around..." << endl << endl;
	if ((room_item.name).empty()) {
		cout << "There is nothing here." << endl;
	}
	else {
		cout << "You see an interesting item, a " << room_item.name << "." << endl;
		cout << "Put it in your utility pouch? (y/n)... ";
		if (grabRoomItem()) {
			bool grab = true;
			if (p->getItemCount() == 2) {
				cout << "Your utility pouch is full!" << endl;
				cout << "Drop an item? (y/n)... ";
				grab = p->dropItem();
			}
			if (p->getItemCount() == 1 && grab) {
				cout << "You picked up the " << room_item.name << "." << endl;
				p->setItem2(room_item);
				room_item.name = "";
			}
			else if (p->getItemCount() == 0 && grab) {
				cout << "You picked up the " << room_item.name << "." << endl;
				p->setItem1(room_item);
				room_item.name = "";
			}
		}
	}
	cout << endl;

	return this;
}


