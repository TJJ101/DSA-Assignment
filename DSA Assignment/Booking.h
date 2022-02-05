#pragma once

#include <string>

using namespace std;

class Booking {
private:
	int bookingID;
	tm bookingDate;
	string guestName;
	int roomNo;
	string roomType;
	//status 0 = out 1 = in 2 = Booked
	int status;
	tm checkInDate;
	tm checkOutDate;
	int numOfGuest;
	string spRequest;

public:
	Booking(int id, tm bookDate, string name, int roomNo, string rmType, int status, tm checkIn, tm checkout,
		int guestNo, string spReq);
	int getID();
	void setID(int id);
	tm getBookingDate();
	void setBookingDate(tm bookingDate);
	string getGuestName();
	void setGuestName(string name);
	int getRoomNo();
	void setRoomNo(int num);
	string getRoomType();
	void setRoomType(string type);
	int getStatus();
	void setStatus(int status);
	tm getCheckInDate();
	void setCheckInDate(tm date);
	tm getCheckOutDate();
	void setCheckOutDate(tm date);
	int getNumofGuest();
	void setNumOfGuest(int num);
	string getSpecialRequest();
	void setSpecialRequest(string req);
};

