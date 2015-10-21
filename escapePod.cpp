//Final Project - Space Escape
//CS 162 - Fall 2014
//author: Boone Neligan
//
//class EscapePod : public Room - implementation file 

#include "room.h"
#include "escapePod.h"
#include "person.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;


//Takes a string as the room name, and sets starting values for other member vars
EscapePod::EscapePod(string room_name) : Room(room_name) {
	passenger1 = "";
	passenger2 = "";
	passenger_count = 0;
	electric_fixed = false;
	mechanical_fixed  = false;
	electric_msg = false;
	mechanical_msg = false;
}


//Takes a Person pointer, checks to see if the Person has the Key Card and returns bool
bool EscapePod::hasKey(Person* p) {
	string key = "Key Card";
	if (p->getItem1().name == key || p->getItem2().name == key) {
		return true;
	}
	else {
		return false;
	}
}


//Takes a Person pointer, checks to see if the Person has the Wrench and returns bool
bool EscapePod::hasWrench(Person* p) {
	string wrench = "Hydrokinetic Adjustable Wrench";
	if (p->getItem1().name == wrench || p->getItem2().name == wrench) {
		return true;
	}
	else {
		return false;
	}
}


//Takes a Person pointer, checks to see if the Person has the Sodering Iron and returns bool
bool EscapePod::hasIron(Person* p) {
	string iron = "Soldering Iron";
	if (p->getItem1().name == iron || p->getItem2().name == iron) {
		return true;
	}
	else {
		return false;
	}
}


//takes a string and stores it as the member var passenger1
void EscapePod::setPassenger1(string name) {
	passenger1 = name;
}


//takes a string and stores it as the member var passenger2
void EscapePod::setPassenger2(string name) {
	passenger2 = name;
}


//takes a string and then passes it to setPassenger1 or setPassenger2
//returns true if there is room on the pod and the drop-off is successful
//else, returns false
bool EscapePod::addPassenger(string name) {
	if (passenger_count == 0) {
		cout << "You have dropped off the " << name << " in the Escape Pod." << endl << endl;
		setPassenger1(name);
		++passenger_count;
		return true;
	}
	else if (passenger_count == 1) {
		cout << "You have dropped off the " << name << " in the Escape Pod." << endl << endl;		
		setPassenger2(name);
		++passenger_count;
		return true;
	}
	else if (passenger_count == 2) {
		cout << "The Escape Pod is full! (Save for your capsule.)" << endl;
		cout << "The passengers already loaded will definitely not be leaving!" << endl << endl;
		return false;
	}
}


//Takes a type Person pointer and returns true for a successful launch
//returns false for a failed launch
bool EscapePod::launchPod(Person* p) {
	cout << "Enter I in the control terminal to launch the Pod!" << endl;
	cout << "To delay the launch enter D." << endl << endl;
	char input;
	do {
		cout << "TERMINAL: ";
		cin >> input;
	} while (input != 'I' && input != 'i' && input != 'D' && input != 'd');

	if (input == 'D' || input == 'd') {
		cout << endl;
		cout << "LAUNCH DELAYED" << endl << endl;
		return false;
	}

	cout << endl;
  	cout << "COUNTDOWN TO LAUNCH:" << endl;;
  	cout << "********************";
  	cout << endl;
    for (int i = 5; i > 0; --i) {
    	cout << i << endl;
    	std::this_thread::sleep_for (std::chrono::seconds(1));
    	if (i == 3) {
    		if (!electric_fixed) {
    			cout << endl;
    			cout << "!!!" << endl << endl;
    			cout << "Sparks started flying from the panel and the countdown has stopped!";
    			cout << endl << endl;
    			cout << "You will need a tool to fix the wiring in the panel!" << endl;
    			cout << "To reach the electrical repair access panel," << endl;
    			cout << "you must re-enter the Escape Pod." << endl << endl;
    			cout << "You exit the Pod." << endl << endl;
    			electric_msg = true;
    			return false;
    		}
    	}
    }
    if (!mechanical_fixed) {
    	for (int i = 0; i < 2; ++i) {
    		cout << "..." << endl << endl;
    		std::this_thread::sleep_for (std::chrono::seconds(1));
    	}
    	cout << "LAUNCH FAILED" << endl << endl;
    	cout << "ERROR REPORT: IGNITION FIRING MECHANISM" << endl << endl << endl;
    	cout << "Cripes!! You will need to find a tool to adjust the firing mechanism!" << endl;
    	cout << "To reach the ignition repair access panel," << endl;
    	cout << "you must re-enter the Escape Pod." << endl << endl;
    	cout << "You exit the Pod." << endl << endl;
    	mechanical_msg = true;
    	return false;
    }
    cout << endl;
    cout << "BLAST OFF!" << endl << endl;
    return true;
}


//Overrides the virtual function in Room parent class
//Does nothing to effectively disable movement from the Escape Pod, which is 
//handled by warping (i.e. returning pointers to other rooms) 
Room* EscapePod::move() {} 


//Overrides the virtual function in Room parent class.  Takes a pointer
//to a type Person and returns a Room pointer (used primarily in warping cases)
Room* EscapePod::roomAction(Person* p) {
	if (!hasKey(p)) {
		cout << endl;
		cout << "You need the Key Card to open the Escape Pod hatch!" << endl << endl;
		return warp;
	}
	else {
		cout << endl;
		cout << "You are in the Escape Pod" << endl;
		cout << "*************************";
		if (passenger_count > 0) {
			cout << endl;
			cout << "The " << passenger1;
			if (passenger_count == 2) {
				cout << " and the " << passenger2 << " are ";
			}
			else {
				cout << " is ";
			}
			cout << "also on board.";
		}
		p->showItems();

		if (hasIron(p) && electric_msg) {
			electric_fixed = true;
			cout << "Nice! You used the Soldering Iron to fix the faulty wiring!" << endl << endl;
		}
		if (hasWrench(p) && mechanical_msg) {
			mechanical_fixed = true;
			cout << "Nice! You used the Hydrokinetic Adjustable Wrench" << endl;
			cout << "to calibrate the ignition firing mechanism!" << endl << endl;
		}
		
		if (!launchPod(p)) {
			cout << "You are in the Omega Corridor" << endl;
			cout << "*****************************";
			p->showItems();
			return warp;
		}
		else {
			string chef = "Chef";
			if (passenger1 == chef || passenger2 == chef) {
				p->setChefDeath();
			}
			else if (passenger_count < 2) {
				p->setMartyrs();
			}
			
			p->setCompleted();
			return end;
		}
	}
}


