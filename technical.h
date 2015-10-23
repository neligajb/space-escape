//author: Boone Neligan

#ifndef TECHNICAL_H
#define TECHNICAL_H

#include "room.h"

#include <string>

using std::string;


class Technical : public Room {
protected:
	Item room_item;
public:
	Technical(string, string);
	Item getRoomItem();
	void setRoomItem(Item);
	bool grabRoomItem();
	Room* roomAction(Person*);
};

#endif