//Final Project - Space Escape
//CS 162 - Fall 2014
//author: Boone Neligan
//
//class Person - header file 

#ifndef PERSON_H
#define PERSON_H

#include "room.h"
#include <string>

using std::string;

//Forward declarations
class Room;
class Technical;

//struct Item store a name and a pointer to indicate it's orignal location
//this way it can be returned to its starting point if neccessary
struct Item {
	string name;
	Technical* location;
};


class Person {
protected:
	string person_name;
	Item item1;
	Item item2;
	string victim_burden;
	int item_count;
	bool completed;
	bool chef_death;
	bool martyrs;
	bool explosion;
	int game_time;
public:
	Person();
	bool intro();
	void setItem1(Item);
	void setItem2(Item);
	Item getItem1();
	Item getItem2();
	int getItemCount();
	void incrementItemCount();
	void decrementItemCount();
	bool dropItem();
	bool clearItems();
	void setCompleted();
	bool getCompleted();
	void setChefDeath();
	void setMartyrs();
	void setExplosion();
	bool getExplosion();
	void incrementGameTime();
	int getGameTime();
	void showItems(); 
	void finale();
};

#endif