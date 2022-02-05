#pragma once
#include <string>

using namespace std;

class Room {
private:
	int roomNo;
	string roomType;
	int costPerNight;

public:
	Room();
	Room(int roomNum, string type, int cost);
	int getRoomNo();
	string getRoomType();
	int getCostPerNight();
};

