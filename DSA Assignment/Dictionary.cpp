// CHOW YUN CONG
#include "Dictionary.h"

// constructor
Dictionary::Dictionary(){
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = NULL;
	}
	size = 0;
}

// destructor is to remove dynamic memory
//static memory is destroyed when program ends but no dynamic memory
//programmer does not call destructor, auto called by program when it ends
Dictionary::~Dictionary(){
	for (int i = 0; i < MAX_SIZE; i++) {
		if (items[i] != NULL) {
			Node* temp = items[i];
			while (temp != NULL)
			{
				items[i] = temp->next;
				temp->next = NULL;
				delete temp;
				temp = items[i];
			}
		}
	}
}


int charvalue(char c) {
	if (isalpha(c)) {
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}


int Dictionary::hash(KeyType key) {
	int total = charvalue(key[0]);
	for (int i = 1; i < key.size(); i++) {
		total = total * 52 + charvalue(key[i]);
		total %= MAX_SIZE;
	}
	return total;
}

// add a new item with the specified key to the Dictionary
// pre : none
// post: new item is added to the Dictionary
//       size of Dictionary is increased by 1
bool Dictionary::add(KeyType newKey, ItemType2 newItem){
	int index = hash(newKey);
	if (items[index] == NULL) {
		Node *newNode = new Node();
		newNode->item = newItem;
		newNode->key = newKey;
		newNode->next = NULL;
		newNode->altNode = NULL;
		items[index] = newNode;
		size++;
		return true;
	}
	else {
		Node* current = items[index];
		if (current->key == newKey) {
			if (current->altNode == NULL) {
				Node* newNode = new Node();
				newNode->item = newItem;
				newNode->key = newKey;
				newNode->next = NULL;
				newNode->altNode = NULL;
				current->altNode = newNode;
				size++;
				return true;
			}
			else {
				current = current->altNode;
				while (current->next != NULL) {
					current = current->next;
				}
				Node* newNode = new Node();
				newNode->item = newItem;
				newNode->key = newKey;
				newNode->next = NULL;
				current->next = newNode;
				size++;
				return true;
			}
		}
		while (current->next != NULL)
		{
			current = current->next;
			if (current->key == newKey) {
				// checks alternate node
				if (current->altNode == NULL) {
					Node* newNode = new Node();
					newNode->item = newItem;
					newNode->key = newKey;
					newNode->next = NULL;
					newNode->altNode = NULL;
					current->altNode = newNode;
					size++;
					return true;
				}
				else {
					current = current->altNode;
					while (current->next != NULL) {
						current = current->next;
					}
					Node* newNode = new Node();
					newNode->item = newItem;
					newNode->key = newKey;
					newNode->next = NULL;
					newNode->altNode = NULL;
					current->next = newNode;
					size++;
					return true;
				}
			}
		}

		Node* newNode = new Node();
		newNode->item = newItem;
		newNode->key = newKey;
		newNode->next = NULL;
		current->next = newNode;
		size++;
		return true;
	}
	
}

// remove an item with the specified key in the Dictionary
// pre : key must exist in the Dictionary
// post: item is removed from the Dictionary
//       size of Dictionary is decreased by 1
void Dictionary::remove(KeyType key){
	int index = hash(key);
	Node* currentNode = items[index];
	if (currentNode != NULL) {
		if (currentNode->key == key) {
			if (currentNode->next == NULL) {
				items[index] = NULL;
				delete currentNode;
				size--;
				return;
			}
			else {
				Node* temp = currentNode;
				items[index] = currentNode->next;
				currentNode->next = NULL;
				delete currentNode;
				size--;
				return;
			}
		}
		else if (currentNode->next != NULL) {
			while (currentNode != NULL) {
				Node* PrevNode = currentNode;
				currentNode = currentNode->next;
				if (currentNode->key == key) {
					PrevNode->next = currentNode->next;
					currentNode->next = NULL;
					delete currentNode;
					size--;
					return;
				}
			}
		}
	}
	cout << "Key does not exist!" << endl;
	
}


// get an item with the specified key in the Dictionary (retrieve)
// pre : key must exist in the dictionary
// post: none
// return the item with the specified key from the Dictionary
ItemType2 Dictionary::get(KeyType key) {
	int index = hash(key);
	if (items[index] != NULL) {
		Node* currentNode = items[index];
		if (currentNode->key == key)
			return currentNode->item;
		else {
			while (currentNode != NULL) {
				currentNode = currentNode->next;
				if (currentNode->key == key)
					return currentNode->item;
			}
		}
	}
	return Booking();
}

// check if the Dictionary is empty
// pre : none
// post: none
// return true if the Dictionary is empty{} otherwise returns false
bool Dictionary::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

// check the size of the Dictionary
// pre : none
// post: none
// return the number of items in the Dictionary
int Dictionary::getLength() { return size; }

//------------------- Other useful functions -----------------

// display the items in the Dictionary
void Dictionary::print(){
	if (size != 0) {
		for (int i = 0; i < MAX_SIZE; i++) {
			if (items[i] != NULL) {

				cout << items[i]->key << "  " << items[i]->item.getGuestName() << endl;
				if (items[i]->next != NULL) {
					Node* current = items[i];
					while (current->next != NULL)
					{
						cout << current->key << "  " << current->item.getGuestName() << endl;
						current = current->next;
					}
				}
			}
		}
	}
	else {
		cout << "Empty" << endl;
	}
}

//Params name of guest as key, and List to append data to
//Finds all bookings with booked status
void Dictionary::GetBookedBookingsByName(string name, ListBooking& list) {
	int index = hash(name);
	Node* currentNode = items[index];
	if (currentNode->key == name) {
		// if first node is the correct one
		if (currentNode->item.getStatus() == 2)
			// checked is booked or not
			list.add(currentNode->item);
		//check if have more bookings under this person
		if (currentNode->altNode != NULL) {
			currentNode = currentNode->altNode;
			if (currentNode->item.getStatus() == 2)
				list.add(currentNode->item);
			while (currentNode->next != NULL) {
				currentNode = currentNode->next;
				if (currentNode->item.getStatus() == 2)
					list.add(currentNode->item);
			}
		}
	}
	else {
		//go through until find name
		while (currentNode->key != name && currentNode->next != NULL) {
			currentNode = currentNode->next;
		}
		// if found
		if (currentNode->key == name) {
			// if first node is the correct one
			if (currentNode->item.getStatus() == 2)
				// checked is booked or not
				list.add(currentNode->item);
			//check if have more bookings under this person
			if (currentNode->altNode != NULL) {
				currentNode = currentNode->altNode;
				if (currentNode->item.getStatus() == 2)
					list.add(currentNode->item);
				while (currentNode->next != NULL) {
					currentNode = currentNode->next;
					if (currentNode->item.getStatus() == 2)
						list.add(currentNode->item);
				}
			}
		}
	}
}

//params: name as key, and Booking object
//Changes value of a booking obj in dictionary
bool Dictionary::ChangeValueOfBooking(string key, Booking booking) {
	int index = hash(key);
	Node* currentNode = items[index];
	//first node is the wanted person
	if (currentNode->key == key) {
		// if first node is the wanted booking
		if (currentNode->item.getID() == booking.getID()) {
			currentNode->item = booking;
			return true;
		}
		else {
			//checking if person has no other bookings
			if (currentNode->altNode == NULL) { return false; }
			// other person has other bookings
			else {
				currentNode = currentNode->altNode;
				if (currentNode->item.getID() == booking.getID()) { 
					currentNode->item = booking;
					return true;
				}
				else {
					if (currentNode->next != NULL) {
						while (currentNode != NULL) {
							currentNode = currentNode->next;
							if (currentNode->item.getID() == booking.getID()) {
								currentNode->item = booking;
								return true;
							}
						}
					}
				}
			}
		}
	}
	
	// if first node is not wanted person
	if (currentNode->next != NULL) {
		while (currentNode != NULL && currentNode->next != NULL) {
			currentNode = currentNode->next;
			//key found
			if (currentNode->key == key) { break; }
		}
		//should be wanted person
		if (currentNode->item.getID() == booking.getID()) {
			currentNode->item = booking;
			return true;
		}
		else {
			//checking if person has no other bookings
			if (currentNode->altNode == NULL) { return false; }
			// other person has other bookings
			else {
				currentNode = currentNode->altNode;
				if (currentNode->item.getID() == booking.getID()) {
					currentNode->item = booking;
					return true;
				}
				else {
					if (currentNode->next != NULL) {
						while (currentNode != NULL) {
							currentNode = currentNode->next;
							if (currentNode->item.getID() == booking.getID()) {
								currentNode->item = booking;
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

//params int monthNo, bookingList to append data to
//Gets all the occupied rooms in a particular month
void Dictionary::GetAllOccupiedRoomByMonth(int monthNo,int yearNo, ListBooking& bookingList) {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* currentNode = items[i];
		if (currentNode != NULL) {
			//checking for 1st node 
			if ( currentNode->item.getCheckInDate().tm_year == yearNo 
				&& currentNode->item.getCheckInDate().tm_mon == monthNo) { bookingList.add(currentNode->item); }
			//checking if node has other bookings
			if (currentNode->altNode != NULL) {
				Node* altNode = currentNode->altNode;
				if ( altNode->item.getCheckInDate().tm_year == yearNo
					&& altNode->item.getCheckInDate().tm_mon == monthNo) { bookingList.add(altNode->item); }
				while (altNode->next != NULL) {
					altNode = altNode->next;
					if (altNode->item.getCheckInDate().tm_year == yearNo 
						&& altNode->item.getCheckInDate().tm_mon == monthNo) { bookingList.add(altNode->item); }
				}
			}
			// resets currentNode to first in index
			//checking other node
			while (currentNode->next != NULL) {
				currentNode = currentNode->next;
				if (currentNode->item.getCheckInDate().tm_year == yearNo
					&& currentNode->item.getCheckInDate().tm_mon == monthNo) { bookingList.add(currentNode->item); }
				//checking if node has other bookings
				if (currentNode->altNode != NULL) {
					Node* altNode = currentNode->altNode;
					if (altNode->item.getCheckInDate().tm_year == yearNo 
						&& altNode->item.getCheckInDate().tm_mon == monthNo) { bookingList.add(altNode->item); }
					while (altNode->next != NULL) {
						altNode = altNode->next;
						if (altNode->item.getCheckInDate().tm_year == yearNo 
							&& altNode->item.getCheckInDate().tm_mon == monthNo) { bookingList.add(altNode->item); }
					}
				}
			}
		}
	}
}
//gets popular roomtype
void Dictionary::getPopularRoomType(string& popular) {
	int standardView = 0;
	int deluxeView = 0;
	int executiveView = 0;
	int presidentView = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* currentNode = items[i];
		if (currentNode != NULL) {
			//checking for 1st node 
			if (currentNode->item.getRoomType() == "Standard City View") {	standardView ++; }
			else if (currentNode->item.getRoomType() == "Deluxe City View") { deluxeView ++; }
			else if (currentNode->item.getRoomType() == "Executive Sea View") { executiveView ++; }
			else { presidentView ++; }
			//checking if node has other bookings
			if (currentNode->altNode != NULL) {
				Node* altNode = currentNode->altNode;
				if (altNode->item.getRoomType() == "Standard City View") { standardView ++; }
				else if (altNode->item.getRoomType() == "Deluxe City View") { deluxeView ++; }
				else if (altNode->item.getRoomType() == "Executive Sea View") { executiveView ++; }
				else { presidentView ++; }
				while (altNode->next != NULL) {
					altNode = altNode->next;
					if (altNode->item.getRoomType() == "Standard City View") { standardView ++; }
					else if (altNode->item.getRoomType() == "Deluxe City View") { deluxeView ++; }
					else if (altNode->item.getRoomType() == "Executive Sea View") { executiveView ++; }
					else { presidentView ++; }
				}
			}
			// resets currentNode to first in index
			//checking other node
			while (currentNode->next != NULL) {
				currentNode = currentNode->next;
				if (currentNode->item.getRoomType() == "Standard City View") { standardView ++; }
				else if (currentNode->item.getRoomType() == "Deluxe City View") { deluxeView ++; }
				else if (currentNode->item.getRoomType() == "Executive Sea View") { executiveView ++; }
				else { presidentView ++; }
				//checking if node has other bookings
				if (currentNode->altNode != NULL) {
					Node* altNode = currentNode->altNode;
					if (altNode->item.getRoomType() == "Standard City View") { standardView ++; }
					else if (altNode->item.getRoomType() == "Deluxe City View") { deluxeView ++; }
					else if (altNode->item.getRoomType() == "Executive Sea View") { executiveView ++; }
					else { presidentView ++; }
				}
			}
		}
	}
	if (standardView > deluxeView && standardView > executiveView && standardView > presidentView) { popular = "Standard City View"; }
	else if (deluxeView > standardView && deluxeView > executiveView && deluxeView > presidentView) { popular = "Deluxe City View"; }
	else if (executiveView > standardView && executiveView > deluxeView && executiveView > presidentView) { popular = "Executive Sea View"; }
	else { popular = "President Suite"; }
}

// void Dictionary::replace(KeyType key, ItemType2 item){}
// bool Dictionary::contains(KeyType key){}

