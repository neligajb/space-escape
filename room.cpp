//author: Boone Neligan
//
//class Room - implementation file 

#include "room.h"
#include "person.h"

#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


//Constructor takes a string for the Room name, and sets it's basic movement pointers to NUll
Room::Room(string n) {
	room_name = n;
	N = NULL;
	S = NULL;
	E = NULL;
	W = NULL;
}


//this function could have pretty easily been rolled into the constructor, but the code was already
//in place by the time this dawned on me.
//It "maps" each room, and sets a few special pointers in the final 3 parameters.
void Room::setConnected(Room* N, Room* S, Room* E, Room* W, Room* warp, EscapePod* escape_pod, Room* end) {
	this->N = N;
	this->S = S;
	this->E = E;
	this->W = W;
	this->warp = warp;
	this->escape_pod = escape_pod;
	this->end = end;
}


//Called by a room obect and returns pointer to the room moved into
//moving into a NULL pointer continues the loop in this function
Room* Room::move() {
	char direction;
	bool dead_end;

	do {
		dead_end = false;
		cout << "Which direction would you like to go from the ";
		cout << room_name << "?" << endl;
		cout << "(N, S, E, W)... ";

		do {
			cin >> direction;
			if (direction != 'N' && direction != 'n' && direction != 'S' && direction != 's' && 
			    direction != 'E' && direction != 'e' && direction != 'W' && direction != 'w') {
				cout << "Invalid input. (N, S, E, W)... ";
			}
		} while (direction != 'N' && direction != 'n' && direction != 'S' && direction != 's' && 
			     direction != 'E' && direction != 'e' && direction != 'W' && direction != 'w');

		if (direction == 'E' || direction == 'e') {
			if (E == NULL) {
				cout << endl;
				cout << "You cannot go that way." << endl << endl;
				dead_end = true;
			}
			else {
				cout << endl;
				return E;
			}
		}
		else if (direction == 'W' || direction == 'w') {
			if (W == NULL) {
				cout << endl;
				cout << "You cannot go that way." << endl << endl;
				dead_end = true;
			}
			else {
				cout << endl;
				return W;
			}
		}
		else if (direction == 'N' || direction == 'n') {
			if (N == NULL) {
				cout << endl;
				cout << "You cannot go that way." << endl << endl;
				dead_end = true;
			}
			else {
				cout << endl;
				return N;
			}
		}
		else if (direction == 'S' || direction == 's') {
			if (S == NULL) {
				cout << endl;
				cout << "You cannot go that way." << endl << endl;
				dead_end = true;
			}
			else {
				cout << endl;
				return S;
			}
		}
	} while (dead_end);
}




