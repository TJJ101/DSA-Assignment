#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <cTime>
#include <chrono>
#include "List.h"
#include "Dictionary.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;
using namespace std::chrono;

void RetrieveRoomData(List& roomList);
void RetrieveBookingData(Dictionary& bookingData, Stack& bookedOutStack, Queue& bookingQueue, Queue& checkedInQueue);
tm convertStringToTM(string date);
bool BookingQueueExist(Queue bookingQueue, Booking data);

int main() {
	List roomList;
	Dictionary bookingData;
	Stack bookedOutStack;
	Queue bookingQueue;
	Queue checkInQueue;
	//Retreive Rooms Data
	RetrieveRoomData(roomList);
	RetrieveBookingData(bookingData, bookedOutStack, bookingQueue, checkInQueue);

	// to set current date
	tm currentDate;
	auto date = system_clock::now();
	time_t t = system_clock::to_time_t(date);
	localtime_s(&currentDate,&t);
	currentDate.tm_mon += 1;
	currentDate.tm_year += 1900;
	
	bookingQueue.displayItems();
	cout << "\n\n";

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
		{
			string name;
			cout << "Enter a name: ";
			cin.ignore();
			getline(cin, name);
			if (!name.empty()) {
				Booking booking = bookingData.get(name);
				cout << BookingQueueExist(bookingQueue, booking) << endl;
				if (booking.getGuestName() != name)
				{
					cout << name << " currently has no booking.\n";
					break;
				}
				else if (BookingQueueExist(bookingQueue, booking) != true)
				{
					cout << name << " currently has no booking.\n";
					break;
				}
				else
				{
					tm checkin = booking.getCheckInDate();
					tm checkout = booking.getCheckOutDate();
					cout << "Guest Name: " << booking.getGuestName() << endl;
					cout << "Checkin: " << checkin.tm_mday << "/" << checkin.tm_mon << "/" << checkin.tm_year << endl;
					cout << "Checkin: " << checkout.tm_mday << "/" << checkout.tm_mon<< "/" << checkout.tm_year << endl;
				}
				
			}
			else
			{
				cout << "Invalid Input\n";
			}
			break;
		}
		case 2:
			// Add and save a new booking for the hotel   
			break;

		case 3:
			//Display guests staying in the hotel on a particular date
		{
			string date;
			string delimiter = "/";

			cout << "Enter a date(e.g. 1/1/2002): ";
			cin >> date;
			string date2 = date;
			string day = date2.substr(0, date2.find(delimiter));
			date2.erase(0, date2.find(delimiter) + delimiter.length());
			string month = date2.substr(0, date2.find(delimiter));
			date2.erase(0, date2.find(delimiter) + delimiter.length());
			string year = date2.substr(0, date2.find(delimiter));
			date2.erase(0, date2.find(delimiter) + delimiter.length());

			cout << "Day: " << day;
			cout << "Month: " << month;
			cout << "Year: " << year;
			break;
		}


		case 4:
			//Display for a particular month, the dates that each room is occupied
			break;

		case 69:
		{
			//Change time for simulation
			string date;
			tm dateInput;
			cout << "Current Date: " << currentDate.tm_mday << "/" << currentDate.tm_mon << "/" << currentDate.tm_year << endl;
			cout << "---------------------------------------------------------\n";
			cout << "Enter Date to change to (e.g. 30/1/2002): ";
			cin >> date;
			dateInput = convertStringToTM(date);
			break;
		}
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

void RetrieveBookingData(Dictionary& bookingData, Stack& bookedOutStack, Queue& bookingQueue,Queue& checkedInQueue) {
	fstream file;
	file.open("Bookings.csv");

	string bookID;
	string bookDate = "";
	string guestName;
	string roomNum;
	string roomType;
	string status;
	string checkIn;
	string checkOut;
	string guestNo;
	string specialRequest;

	//Skips first line, header row
	getline(file, roomNum);

	while (file.good()) {
		getline(file, bookID, ',');

		//read finish empty row
		if (bookID._Equal(""))
			break;

		getline(file, bookDate, ',');
		getline(file, guestName, ',');
		getline(file, roomNum, ',');
		getline(file, roomType, ',');
		getline(file, status, ',');
		getline(file, checkIn, ',');
		getline(file, checkOut, ',');
		getline(file, guestNo, ',');
		getline(file, specialRequest, '\n');

		int bookingID = stoi(bookID);   
		tm bookingDate = convertStringToTM(bookDate);
		
		int roomNo = -1;
		if (!roomNum._Equal(" ") && !roomNum._Equal("") && !roomNum.empty() && roomNum.size() != 0) {
			roomNo = stoi(roomNum.substr(5, 8));
		}

		int statusCode;
		if (status == "Checked Out")
			statusCode = 0;
		else if (status == "Checked In")
			statusCode = 1;
		else
			statusCode = 2;
		tm checkInDate = convertStringToTM(checkIn);
		tm checkOutDate = convertStringToTM(checkOut);
		int guestAmt = stoi(guestNo);

		bookingData.add(guestName,Booking(bookingID, bookingDate, guestName, roomNo, roomType, statusCode, checkInDate, checkOutDate, guestAmt, specialRequest));
		
		// Add those with status "Booked" into queue
		if (statusCode == 0)
		{
			bookedOutStack.push(Booking(bookingID, bookingDate, guestName, roomNo, roomType, statusCode, checkInDate, checkOutDate, guestAmt, specialRequest));
		}
		else if (statusCode == 2) 
		{
			bookingQueue.enqueue(Booking(bookingID, bookingDate, guestName, roomNo, roomType, statusCode, checkInDate, checkOutDate, guestAmt, specialRequest));
		}
		else if (statusCode == 1)
		{
			checkedInQueue.enqueue(Booking(bookingID, bookingDate, guestName, roomNo, roomType, statusCode, checkInDate, checkOutDate, guestAmt, specialRequest));
		}
	}

	cout << bookingData.getLength() << endl;

}

tm convertStringToTM(string date) 
{
	tm result;

	char arr[17];
	strcpy_s(arr, 17, date.c_str());

	sscanf_s(arr, "%d/%d/%4d  %d:%d:%d",
		&result.tm_mday, &result.tm_mon, &result.tm_year, &result.tm_hour, &result.tm_min, &result.tm_sec);
	return result;
}

bool BookingQueueExist(Queue bookingQueue, Booking data)
{
	Booking temp;
	while (!bookingQueue.isEmpty())
	{
		bookingQueue.dequeue(temp);
		if (temp.getGuestName() == data.getGuestName()) {
			return true;
		}
	}
	return false;
}

