#include "Room.h"

Room::Room(int roomNum, string type, int cost){
	roomNo = roomNum;
	roomType = type;
	costPerNight = cost;
}

int Room::getRoomNo() { return roomNo; }
string Room::getRoomType() { return roomType; }
int Room::getCostPerNight() { return costPerNight; }