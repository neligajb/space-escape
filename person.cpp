//author: Boone Neligan
//
//class Person - implementation file 

#include "person.h"
#include "room.h"
#include "technical.h"

#include <iostream>
#include <thread>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;

//Constructor sets Player's name, sets theirs items to "empty", sets all game completion flags
//to false, and starts "game time" at 0.
Person::Person() {
	cout << endl;
	cout << "Enter a name for your character (no spaces): ";
	cin >> person_name;
	cout << endl;
	item1.name = "";
	item2.name = "";
	victim_burden = "";
	item_count = 0;
	completed = false;
	chef_death = false;
	martyrs = false;
	explosion = false;
	game_time = 0;
}


void Person::setItem1(Item i) {
	item1 = i;
	++item_count;
}


void Person::setItem2(Item i) {
	item2 = i;
	++item_count;
}


Item Person::getItem1() {
	return item1;
}


Item Person::getItem2() {
	return item2;
}


int Person::getItemCount() {
	return item_count;
}


void Person::incrementItemCount() {
	++item_count;
}


void Person::decrementItemCount() {
	--item_count;
}

//Only called when Utility Pounch is full, so 2 items are assumed to be present
//Takes input from the player to determine if they want to drop one item
//If so, returns true.  Else, returns false
bool Person::dropItem() {
	bool drop = false;
	int input;
	char choice;
	do {
		cin >> choice;
		if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "Drop an item? (y/n)... ";
		}
	} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

	if (choice == 'n' || choice == 'N') {
		return drop;
	}

	cout << endl;

	cout << "You are carrying:" << endl;
	cout << "*****************" << endl;
	cout << "1. " << item1.name << endl;
	cout << "2. " << item2.name << endl << endl;
	cout << "Enter 1 or 2 to drop the item, or 3 to keep these items: ";
	cin >> input;
	cout << endl;
	if (input == 1) {
		cout << "You dropped the " << item1.name << "," << endl;
		item1.location->setRoomItem(item1);
		item1 = item2;
		item2.name = "";			
		decrementItemCount();
		drop = true;
	}
	else if (input == 2) {
		cout << "You dropped the " << item2.name << ", " << endl;
		item2.location->setRoomItem(item2);
		item2.name = "";
		decrementItemCount();
		drop = true;
	}
	if (input == 1 || input == 2) {
		cout << "and it has become lost in the fray!" << endl;
		cout << "It's a good thing the crew stocks backups!" << endl << endl;
	}
	else {
		cout << "Items kept." << endl << endl;
	}
	return drop;
}

//Assumes Player has 1 or 2 items, will clear all regardless
//returns true if they clear the items from the ulitity pouch
//else returns false
bool Person::clearItems() {
	char input;
	do {
		cin >> input;
		if (input != 'y' && input != 'Y' && input != 'n' && input != 'N') {
			cout << "Invalid input. Drop all items? (y/n)... ";
		}
	} while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');

	if (input == 'y' || input == 'Y') {
		cout << endl;
		if (item_count == 1) {
			cout << "You dropped the " << item1.name << "," << endl;
			cout << "and it has become lost in the fray!" << endl;;
			cout << "It's a good thing the crew stocks backups!" << endl;
		
			item1.location->setRoomItem(item1);
			item1.name = "";
			decrementItemCount();
		}
		else if (item_count == 2) {
			cout << "You dropped the " << item1.name << " and the " << item2.name << ", " << endl;
			cout << "and they have become lost in the fray!" << endl;
			cout << "It's a good thing the crew stocks backups!" << endl;

			item1.location->setRoomItem(item1);
			item1.name = "";
			decrementItemCount();

			item2.location->setRoomItem(item2);
			item2.name = "";
			decrementItemCount();
		}
		cout << endl;
		return true;
	}
	cout << endl;
	return false;
}

//Displays warning messages to Player based on elapsed game time
//
void Person::incrementGameTime() {
	game_time++;
	if (game_time == 10) {
		cout << endl << endl;
		cout << "#####################################" << endl;
		cout << "# The Flames are Spreading Quickly! #" << endl;
		cout << "#####################################" << endl << endl;
	}
	else if (game_time == 20) {
		cout << endl << endl;
		cout << "###################################################" << endl;
		cout << "# The Flames are Creeping Toward the Fuel Center! #" << endl;
		cout << "#                     Hurry!                      #" << endl;
		cout << "###################################################" << endl << endl;
	}
	else if (game_time == 25) {
		cout << endl << endl;
		cout << "###############################################" << endl;
		cout << "# The Secondardy Fuel Cells Have Caught Fire! #" << endl;
		cout << "#            Get to the Escape Pod!           #" << endl;
		cout << "###############################################" << endl << endl;
	}
	else if (game_time == 28) {
		cout << endl << endl;
		cout << "###################################" << endl;
		cout << "# Total Destruction is Imminent!! #" << endl;
		cout << "###################################" << endl << endl;
	}
	else if (game_time == 31) {
		explosion = true;
	}
}


int Person::getGameTime() {
	return game_time;
}


void Person::setCompleted() {
	completed = true;
}


bool Person::getCompleted() {
	return completed;
}


bool Person::getExplosion() {
	return explosion;
}


void Person::setChefDeath() {
	chef_death = true;
}


void Person::setMartyrs() {
	martyrs = true;
}


void Person::setExplosion() {
	explosion = true;
}


void Person::showItems() {
	cout << endl << endl;
	cout << "Utility Pouch Contents:" << endl;
	if (item_count == 0) {
		cout << "	(empty)" << endl << endl;
		return;
	}
	if (item_count > 0) {
		cout << "	1. " << item1.name << endl;
	}
	if (item_count == 2) {
		cout << "	2. " << item2.name << endl;
	}
	cout << endl << endl;
}

//Displays menu so that Player may select to show hints, or start a new game.
//Returns false until player selects a new game (spins a while-loop in main)
bool Person::intro() {
	int input;
	cout << "Welcome, Lt. " << person_name << endl;
	for (int i = 0; i < person_name.length() + 13; i++) {
		cout << "*";
	}
	cout << endl;
	cout << "1. New Game" << endl;
	cout << "2. Show Hints" << endl;
	do {
		cout << endl;
		cout << "Choose an option (1-2)... ";
		cin >> input;
	} while (input != 1 && input != 2); 
	if (input == 1) {
		cout << endl;
		cout << "ABOARD THE SS PARALUS... " << endl;
		cout << "########################" << endl << endl;
		cout << "First Lieutenant " << person_name << "," << endl;
		cout << "The damage to your ship is catastrophic!!" << endl << endl;
		cout << "An unexpectedly dense asteroid field has ruptured the rear hull," << endl;
		cout << "and two fuel lines have caught fire. It is only a matter of time" << endl;
		cout << "before the flames reach the fuel supply!" << endl << endl;
		cout << "Three other crew members have survived the explosions, but" << endl;
		cout << "before the intercoms went out they all reported serious injuries!" << endl;
		cout << "Communication went down beore they could report their locations." << endl;
		cout << "Sadly, there is only room for three on the Escape Pod --" << endl;
		cout << "you and two others." << endl << endl;
		cout << "Typically, you and your fellow crew members can use a thumb print" << endl;
		cout << "reader to access the Escape Pod, but your thumbs are so badly" << endl;
		cout << "burned that they will not scan!" << endl << endl;
		cout << "Your fellow crew should be able to access the Pod with their" << endl;
		cout << "thumb prints, but if you are alone you will need another form" << endl;
		cout << "of verification." << endl << endl;
		cout << "You have strapped on your skin tight heat resistant suit," << endl;
		cout << "so you will need the heat resistant Utility Pouch to carry" << endl;
		cout << "any items you may require. It's small and will only hold a couple" << endl;
		cout << "of items at a time." << endl << endl;
		cout << "Help your crew mates and get off the ship!" << endl << endl;
		cout << "There isn't much time! ..." << endl << endl << endl;
		return true;
	}
	else {
		cout << endl << endl;
		cout << "The scanned map will be very helpful." << endl;
		cout << "Picking up a victim will require emptying your utility pouch." << endl;
		cout << "For the \"best\" outcome, first put the Captain and the" << endl;
		cout << "Biologist on the Escape Pod (the Chef will murder you)," << endl;
		cout << "then bring the Sodering Iron and Key Card to the Pod," << endl;
		cout << "and finally the Wrench and the Key Card." << endl << endl << endl;
		return false;
	}
}

//End of game sequence. Outcome is based on which Player flags were set in the Escape Pod
void Person::finale() {
	if (chef_death) {
		for (int i = 0; i < 3; ++i) {
			if (i == 0)
    			cout << "    *   " << endl;
    		if (i == 1)  
    			cout << "*       " << endl;
    		if (i == 2)
    			cout << "       *" << endl; 
    		std::this_thread::sleep_for(std::chrono::seconds(1));
    	}
    	cout << endl;
		cout << "As you sail into the starry afterglow," << endl;
		cout << "you sense something isn't right..." << endl << endl;
		cout << "Suddenly the chef lunges at you and presses his filet knife" << endl;
		cout << "against your throat!" << endl << endl;
		cout << "\"You shouldn't have complained about my salisbury steak!\" he roars," << endl;
		cout << "just before gruesomely ending your mission... for good." << endl << endl;
	}
	else if (martyrs) {
		for (int i = 0; i < 3; ++i) {
			if (i == 0)
				cout << "    *   " << endl;
			if (i == 1)  
				cout << "*       " << endl;
			if (i == 2)
				cout << "       *" << endl; 
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
    	cout << endl;
		cout << "As you sail into the starry afterglow," << endl;
		cout << "you sense something isn't right..." << endl << endl;
		cout << "Suddenly, it dawns on you --" << endl;
		cout << "There are empty capsules on the Escape Pod!" << endl;
		cout << "Some of your crew mates are perishing needlessly on the ship!" << endl << endl;
		cout << "You wonder how you will ever live with this guilt..." << endl << endl;
	}
	else if (explosion) {
		for (int i = 0; i < 3; ++i) {
			cout << " ..." << endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		cout << endl << endl;
		cout << "        _.-^^---....,,--        " << endl;
		cout << "    _--                  --_    " << endl;
		cout << "   <                        >)  " << endl;
		cout << "   |                         |  " << endl;
		cout << "    \\._                   _./  " << endl;
		cout << "       ```--. . , ; .--'''      " << endl;
		cout << "             | |   |            " << endl;
		cout << "          .-=||  | |=-.         " << endl;
		cout << "          `-=#$%&%$#=-'         " << endl;
		cout << "             | ;  :|            " << endl;
		cout << "    _____.,-#%&$@%#&#~,._____   " << endl << endl << endl;
		cout << "... the primary fuel cell was breached by the flames ..." << endl << endl;
		cout << "You and your crew mates have perished in the inferno." << endl << endl;
	}
	else {
		for (int i = 0; i < 3; ++i) {
			if (i == 0)
				cout << "    *   " << endl;
			if (i == 1)  
				cout << "*       " << endl;
			if (i == 2)
				cout << "       *" << endl; 
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
    	cout << endl;
		cout << "As you and your crew mates sail into the starry afterglow," << endl;
		cout << "you look back through the viewports to watch the Paralus" << endl;
		cout << "erupt in a magnificent explosion." << endl << endl;
		cout << "For now, all is calm, and your thoughts drift" << endl;
		cout << "to the next mission that awaits..." << endl << endl;
	}

	cout << "	   	***********" << endl;
	cout << "		* THE END *" << endl;
	cout << "		***********" << endl << endl << endl;
}


