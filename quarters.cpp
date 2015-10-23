//author: Boone Neligan
//
//class Quarters : public Room - implementation file 

#include "room.h"
#include "quarters.h"
#include "person.h"
#include "escapePod.h"

#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


//Takes a string for the Room name, the room victim's name, and the victim's traits
Quarters::Quarters(string room_name, string victim_name, string vic_traits) : Room(room_name) {
	victim = victim_name;
	traits = vic_traits;
}


//Returns true if Player decides to pick up the victim
//Esle, returns false
bool Quarters::pickupVictim() {
	char input;
	do {
		cin >> input;
		if (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
			cout << "Invalid input. Pick up the " << victim << "? (y/n)... ";
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
Room* Quarters::roomAction(Person* p) {
	cout << endl;
	cout << "You are in the " << room_name << endl;
	cout << "***************";
	for (int i = 0; i < room_name.length(); i++) {
		cout << "*";
	} 
	p->showItems();
	cout << "Amidst the blazes, you see... ";
	if (victim.empty()) {
		cout << "nothing." << endl << endl;
	}
	else {
		cout << "the " << traits << " " << victim << "!" << endl;
		cout << "He is injured! Will you pick him up and carry him to the escape pod? (y/n)... ";

		if (pickupVictim()) {
			bool clear = true;
			if (p->getItemCount() > 0) {
				cout << "Your utility bag is too heavy to also carry the " << victim << "!" << endl;
				cout << "Drop all items and pick up the " << victim << "? (y/n)... "; 
				clear = p->clearItems();
			}
			if (clear) {
				if (escape_pod->addPassenger(victim)) {
					victim = "";
					cout << endl;
					cout << "You are now just West of the Pod, in the Omega Corridor" << endl;
					cout << "*******************************************************";
					p->showItems();
					return warp;
				}
			}
		}
		cout << "You have left the " << victim << " to face his destiny!" << endl;
		cout << "Will you go back for him?" << endl << endl;
	}
	return this;
}

