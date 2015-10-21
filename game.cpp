//Final Project - Space Escape
//CS 162 - Fall 2014
//author: Boone Neligan
//
//Main 

#include "room.h"
#include "person.h"
#include "technical.h"
#include "quarters.h"
#include "escapePod.h"
#include "basic.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool replay();


int main() {
	do {
		Room* bridge = new Basic("Bridge", "");
		Room* mechanical = new Technical("Mechanical Room", "Hydrokinetic Adjustable Wrench");
		Room* storage = new Technical("Storage Closet", "Key Card");
		Room* corridor1 = new Basic("Alpha Corridor", "");
		Room* electrical = new Technical("Work Shop", "Soldering Iron");
		Room* galley = new Quarters("Galley", "Chef", "gruff yet formidable");
		Room* corridor2 = new Basic("Omega Corridor", "");
		Room* chamber1 = new Quarters("Upper Crew Chamber", "Captain", "demanding and irksome");
		Room* chamber2 = new Quarters("Lower Crew Chamber", "Biologist", "feeble and whiny");
		EscapePod* escape_pod = new EscapePod("Escape Pod");
		Room* end = new Basic("", "");

		bridge->setConnected(mechanical, corridor1, NULL, storage, corridor2, escape_pod, end);
		mechanical->setConnected(NULL, bridge, chamber1, storage, corridor2, escape_pod, end);
		storage->setConnected(mechanical, galley, bridge, NULL, corridor2, escape_pod, end);
		corridor1->setConnected(electrical, galley, corridor2, bridge, corridor2, escape_pod, end);
		electrical->setConnected(NULL, corridor1, chamber1, NULL, corridor2, escape_pod, end);
		galley->setConnected(corridor1, NULL, chamber2, storage, corridor2, escape_pod, end);
		corridor2->setConnected(chamber1, chamber2, escape_pod, corridor1, corridor2, escape_pod, end);
		chamber1->setConnected(mechanical, corridor2, NULL, electrical, corridor2, escape_pod, end);
		chamber2->setConnected(corridor2, NULL, NULL, galley, corridor2, escape_pod, end);
		escape_pod->setConnected(NULL, NULL, NULL, NULL, corridor2, escape_pod, end);

		cout << endl;
		cout << "			##########################" << endl;
		cout << "			#                        #" << endl;
		cout << "			#      SPACE ESCAPE      #" << endl;
		cout << "			#                        #" << endl;
		cout << "			##########################" << endl << endl << endl;

		Person* player1 = new Person();

		while (!player1->intro()) {}

		Room* cur = bridge;

		while (!player1->getCompleted() && !player1->getExplosion()) {
			cur = cur->roomAction(player1);
			if (player1->getCompleted()) {
				break;
			}
			cur = cur->move();
			player1->incrementGameTime();
		}

		player1->finale();	
	} while (replay());

	cout << endl;
	return 0;
}

bool replay() {
	char input;
	cout << "Play again? (y/n)... ";
	do {
		cin >> input;
		if (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
			cout << "Invalid input. Play again? (y/n)... ";
		}
	} while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');

	if (input == 'y' || input == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

