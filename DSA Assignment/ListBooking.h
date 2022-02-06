// ListBooking.h - - Specification of ListBooking ADT
// CHOW YUN CONG

#include<string>
#include<iostream>
#include "Booking.h"

using namespace std;

typedef Booking Type;

class ListBooking {
private:
	struct Node {
		Type item;	// data item
		Node* next;	// pointer pointing to next item
	};

	Node* firstNode;	// point to the first item
	int  size;			// number of items in the ListBooking

public:

	// constructor
	ListBooking();

	//deconstructor
	~ListBooking();

	// add a new item to the back of the ListBooking (append)
	// pre : size < MAX_SIZE
	// post: new item is added to the back of the ListBooking
	//       size of ListBooking is increased by 1
	bool add(Type newItem);

	// add a new item at a specified position in the ListBooking (insert)
	// pre : 1 <= index <= size+1
	// post: new item is added to the specified position in the ListBooking
	//       items after the position are shifted back by 1 position
	//       size of ListBooking is increased by 1
	bool add(int index, Type newItem);

	// remove an item at a specified position in the ListBooking
	// pre : 1 <= index <= size
	// post: item is removed the specified position in the ListBooking
	//       items after the position are shifted forward by 1 position
	//       size of ListBooking is decreased by 1
	void remove(int index);

	// get an item at a specified position of the ListBooking (retrieve)
	// pre : 1 <= index <= size
	// post: none
	// return the item in the specified index of the ListBooking
	Type get(int index);

	// check if the ListBooking is empty
	// pre : none
	// post: none
	// return true if the ListBooking is empty; otherwise returns false
	bool isEmpty();

	// check the size of the ListBooking
	// pre : none
	// post: none
	// return the number of items in the ListBooking
	int getLength();

	// display the items in the ListBooking
	void print();

	void printInfo();
};
