#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <cTime>
#include <chrono>
#include <format>
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
void getCurrentDateTime(tm& dateTime);
void AddBooking(Dictionary& bookingData);
void AddToBookingCSV(Booking& booking);
void TmToString(string& date, tm tmDate);

int main() {
	List roomList;
	Dictionary bookingData;
	Stack bookedOutStack;
	Queue bookingQueue;
	Queue checkInQueue;
	//Retreive Rooms Data
	RetrieveRoomData(roomList);
	RetrieveBookingData(bookingData, bookedOutStack, bookingQueue, checkInQueue);

	// to set current date----------------------------------
	tm currentDate;
	getCurrentDateTime(currentDate);
	//----------------------------------------------------
	bookingQueue.displayItems();
	cout << "\n\n";

	Booking data;
	bookingQueue.getFront(data);
	cout << data.getGuestName() << "\n\n";

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
			cin.clear();
			cin.ignore();
			getline(cin, name);
			Booking booking = bookingData.get(name);
			ListBooking bookDupList;
			if (booking.getGuestName() == name) 
			{
				bookingData.GetBookedBookingsByName(name, bookDupList);
				if (bookDupList.getLength() > 0) 
				{
					if (bookDupList.getLength() > 1)
					{
						int choice = 0;
						cout << name << " currently has " << bookDupList.getLength() << " bookings.\n\n";
						cout << "    Room Type                Check In       Check Out       Guest #       Special Requests    \n";
						cout << "--------------------------------------------------------------------------------------\n";
						for (int i = 0; i < bookDupList.getLength(); i++)
						{
							cout << i << "   " << bookDupList.get(i).getRoomType() << "         " << bookDupList.get(i).getCheckInDate().tm_mday << "/"
								<< bookDupList.get(i).getCheckInDate().tm_mon << "/" << bookDupList.get(i).getCheckInDate().tm_year << "         "
								<< bookDupList.get(i).getCheckOutDate().tm_mday << "/" << bookDupList.get(i).getCheckOutDate().tm_mon << "/"
								<< bookDupList.get(i).getCheckOutDate().tm_year << "         " << bookDupList.get(i).getNumofGuest() << "         "
								<< bookDupList.get(i).getSpecialRequest() << endl;
						}
						cout << "\nChoose which booking to check in (0 to exit): ";
						cin >> choice;
						if (choice == 0)
						{
							cout << "Back to Main Menu\n";
						}
						else if (choice > bookDupList.getLength() || choice < bookDupList.getLength())
						{
							cout << "Invalid Choice\n";
						}
						else
						{

						}
					}
					else
					{
						Booking booking = bookDupList.get(0);
						if (booking.getStatus() == 2)
						{
							tm checkin = booking.getCheckInDate();
							tm checkout = booking.getCheckOutDate();
							cout << "Guest Name: " << booking.getGuestName() << endl;
							cout << "Checkin: " << checkin.tm_mday << "/" << checkin.tm_mon << "/" << checkin.tm_year << endl;
							cout << "Checkin: " << checkout.tm_mday << "/" << checkout.tm_mon << "/" << checkout.tm_year << endl;
						}
						else if (booking.getStatus() == 2)
						{
							cout << name << " currently has no booking.\n";
							break;
						}
					}
				}
				else
				{
					cout << name << " currently has no booking.\n";
				}
			}
			else
			{
				cout << name << " currently has no booking.\n";
				break;
			}

			// CLear the Booking Duplicate List
			break;
		}
		case 2:
			// Add and save a new booking for the hotel   
			AddBooking(bookingData);
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
	Queue tempQ;
	Stack tempS;

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

	file.close();

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

void AddBooking(Dictionary& bookingData) {
	string input = "";
	while (true) {
		// get Guest name
		cout << "\nPlease enter your name or enter 0 to exit: ";
		cin.ignore();
		getline(cin, input);
		if (input == "0")
			break;
		string guestName = input;

		//Get room type
		string roomType;
		bool selected = false;
		while (!selected) {
			cout << "\n[1] Standard City View" << endl;
			cout << "[2] Deluxe City View" << endl;
			cout << "[3] Executive Sea View" << endl;
			cout << "[4] President Suite" << endl;
			cout << "\nPlease choose your room type or enter 0 to exit: ";
			cin >> input;
			switch (stoi(input)) {
			default:
				cout << "\nPlease select a valid option" << endl;
				break;
			case 1:
				roomType = "Standard City View";
				selected = true;
				break;
			case 2:
				roomType = "Deluxe Sea View";
				selected = true;
				break;
			case 3:
				roomType = "Executive Sea View";
				selected = true;
				break;
			case 4:
				roomType = "President Suite";
				selected = true;
				break;
			case 0 :
				return;
			}
		}

		//get check in date;
		tm checkIndateInput;
		cout << "Enter Check in Date to (e.g. 30/1/2002) or enter 0 to exit: ";
		cin >> input;
		if (input._Equal("0"))
			return;
		checkIndateInput = convertStringToTM(input);
		
		//get check out date
		tm checkOutdateInput;
		cout << "Enter Check out Date to (e.g. 30/1/2002) or enter 0 to exit: ";
		cin >> input;
		if (input._Equal("0"))
			return;
		checkOutdateInput = convertStringToTM(input);
		
		// get guest amount
		int guestAmt;
		cout << "Enter amount of guest: ";
		if (input._Equal("0"))
			return;
		cin >> input;
		guestAmt = stoi(input);
		
		cout << "Enter any special request you have or leave it blank or enter 0 to exit: ";
		cin.ignore();
		getline(cin, input);
		if (input._Equal("0"))
			return;
		


		//creating new booking object
		Booking booking;

		tm tmDate;
		getCurrentDateTime(tmDate);

		booking.setNumOfGuest(guestAmt);
		booking.setBookingDate(tmDate);
		booking.setID(bookingData.getLength() + 1);
		booking.setGuestName(guestName);
		booking.setRoomType(roomType);
		booking.setStatus(2);
		booking.setCheckInDate(checkIndateInput);
		booking.setCheckOutDate(checkOutdateInput);
		booking.setSpecialRequest(input);
		bookingData.add(booking.getGuestName(),booking);
		AddToBookingCSV(booking);

		cout << "\nSuccesfully booked" << endl;
		break;
		return;
	}
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


void getCurrentDateTime(tm& tmDate) {
	auto date = system_clock::now();
	time_t t = system_clock::to_time_t(date);
	localtime_s(&tmDate, &t);
	tmDate.tm_mon += 1;
	tmDate.tm_year += 1900;
}

void AddToBookingCSV(Booking& booking) {
	fstream file("Bookings.csv", ios::app);
	tm nowTime;
	getCurrentDateTime(nowTime);

	string bookingDate = to_string(nowTime.tm_mday) + "/" + to_string(nowTime.tm_mon) +
		"/" + to_string(nowTime.tm_year) + " " + to_string(nowTime.tm_hour) + ":" +
		to_string(nowTime.tm_min);
	string checkInDate, checkOutDate;
	TmToString(checkInDate, booking.getCheckInDate());
	TmToString(checkOutDate, booking.getCheckOutDate());
	file << booking.getID() << "," + bookingDate + "," + booking.getGuestName() + ",," + booking.getRoomType()
		+ "," + "Booked," + checkInDate + "," + checkOutDate + "," + to_string(booking.getNumofGuest()) + ","
		+ booking.getSpecialRequest() << endl;

	file.close();
}

void TmToString(string& date, tm tmDate) {
	date = to_string(tmDate.tm_mday) + "/" + to_string(tmDate.tm_mon) + "/" + to_string(tmDate.tm_year);
}


