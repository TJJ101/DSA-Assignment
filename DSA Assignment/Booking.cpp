#include "Booking.h"

Booking::Booking() {}
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

int	Booking::getID() { return bookingID; }

void Booking::setID(int id) { bookingID = id;}

tm Booking::getBookingDate() { return bookingDate; }

void Booking::setBookingDate(tm bookingDate) { bookingDate = bookingDate; }

string Booking::getGuestName() { return guestName; }

void Booking::setGuestName(string name) { guestName = name; }

int	Booking::getRoomNo() { return roomNo; }

void Booking::setRoomNo(int num) { roomNo = num; }

string Booking::getRoomType() { return roomType; }

void Booking::setRoomType(string type) { roomType = type; }

int Booking::getStatus() { return status; }

void Booking::setStatus(int s) { status = s; }

tm Booking::getCheckInDate() { return checkInDate; }

void Booking::setCheckInDate(tm date) { checkInDate = date; }

tm Booking::getCheckOutDate() { return checkOutDate; }

void Booking::setCheckOutDate(tm date) { checkOutDate = date; }

int Booking::getNumofGuest() { return numOfGuest; }

void Booking::setNumOfGuest(int num) { numOfGuest = num; }

string Booking::getSpecialRequest() { return spRequest; }

void Booking::setSpecialRequest(string req) { spRequest = req; }