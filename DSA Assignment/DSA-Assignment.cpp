#include <iostream>
#include <fstream>
#include "Booking.h"
#include "List.h"

using namespace std;

void RetrieveRoomData(List& roomList);

int main() {
	List roomList;

	//Retreive Rooms Data
	RetrieveRoomData(roomList);

	int option = -1;
	while (option != 0) {
		cout << "\n==================================MENU=====================================" << endl;
		cout << "|[1] Check in a guest using the booking information                       |" << endl;
		cout << "|[2] Add and save a new booking for the hotel                             |" << endl;
		cout << "|[3] Display guests staying in the hotel on a particular date             |" << endl;
		cout << "|[4] Display for a particular month, the dates that each room is occupied |" << endl;
		cout << "|[0] Exit                                                                 |" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "|[69] Time Change                                                         |" << endl;
		cout << "===========================================================================" << endl;
		cout << "\nPlease enter an option: ";
		cin >> option;

		switch (option) {
		default:
			cout << "\nPlease enter a valid option!" << endl;
			break;
		case 0:
			// Exit
			cout << "\nExiting App Bye Bye" << endl;
			break;

		case 1:
			//Check in a guest using the booking information  
			break;

		case 2:
			// Add and save a new booking for the hotel   
			break;

		case 3:
			//Display guests staying in the hotel on a particular date
			break;

		case 4:
			//Display for a particular month, the dates that each room is occupied
			break;

		case 69:
			//Change time for simulation
			break;
		}
	}
}

void RetrieveRoomData(List& roomList) {
	fstream file;
	file.open("Rooms.csv");

	string roomNum;
	string roomType;
	string cost;
	//Skips first line, header row
	getline(file, roomNum);

	while (file.good()) {
		getline(file, roomNum, ',');

		//no more rows
		if (roomNum._Equal(""))
			break;
		
		getline(file, roomType, ',');
		getline(file, cost, '\n');

		int roomNo = stoi(roomNum.substr(5, 8));
		int costPerNight = stoi(cost);
		
		roomList.add(Room(roomNo, roomType, costPerNight));
	}
}

