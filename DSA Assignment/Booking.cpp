#include "Booking.h"

Booking::Booking(int id, tm bookDate, string name, int rmNo, string rmType, int statusCode, tm checkIn, tm checkout,
	int guestNo, string spReq) {
	bookingID = id;
	bookingDate = bookDate;
	guestName = name;
	roomNo = rmNo;
	roomType = rmType;
	status = statusCode;
	checkInDate = checkIn;
	checkOutDate = checkout;
	numOfGuest = guestNo;
	spRequest = spReq;
}

int	Booking::getID() { return this->bookingID; }

void Booking::setID(int id) { this->bookingID = id;}

tm Booking::getBookingDate() { return bookingDate; }

void Booking::setBookingDate(tm bookingDate) { this->bookingDate = bookingDate; }

string Booking::getGuestName() { return this->guestName; }

void Booking::setGuestName(string name) { this->guestName = name; }

int	Booking::getRoomNo() { return this->roomNo; }

void Booking::setRoomNo(int num) { this->roomNo = num; }

string Booking::getRoomType() { return this->roomType; }

void Booking::setRoomType(string type) { this->roomType = type; }

int Booking::getStatus() { return this->status; }

void Booking::setStatus(int status) { this->status = status; }

tm Booking::getCheckInDate() { return this->checkInDate; }

void Booking::setCheckInDate(tm date) { this->checkInDate = date; }

tm Booking::getCheckOutDate() { return this->checkOutDate; }

void Booking::setCheckOutDate(tm date) { this->checkOutDate = date; }

int Booking::getNumofGuest() { return this->numOfGuest; }

void Booking::setNumOfGuest(int num) { this->numOfGuest = num; }

string Booking::getSpecialRequest() { return this->spRequest; }

void Booking::setSpecialRequest(string req) { this->spRequest = req; }