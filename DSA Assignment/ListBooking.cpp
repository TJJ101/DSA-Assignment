// CHOW YUN CONG
#include "ListBooking.h"

// constructor
ListBooking::ListBooking() { size = 0; }

// destructor
ListBooking::~ListBooking() {}

// add an item to the back of the ListBooking (append)
bool ListBooking::add(Type item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	if (firstNode == NULL) {
		firstNode = newNode;
	}
	else {
		Node* temp = firstNode;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}

	size++;
	return true;
}

// add an item at a specified position in the ListBooking (insert)
bool ListBooking::add(int index, Type item) {
	if (index > 0 && index <= size) {
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;

		if (index == 0) {
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else {
			Node* current = firstNode;
			for (int i = 1; i < index - 1; i++) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}

		size++;
		return true;
	}
	else {
		return false;
	}
}

// remove an item at a specified position in the ListBooking
void ListBooking::remove(int index) {
	if (index > 0 && index <= size) {
		if (index == 1) {
			firstNode = firstNode->next;
		}
		else {
			Node* previous = firstNode;
			Node* current = previous->next;
			for (int i = 1; i < index - 1; i++) {
				previous = current;
				current = current->next;
			}
			previous->next = current->next;
			current = current->next;
			delete current;
		}
		size--;
	}
	else {
		//cout << "ListBooking is empty!" << endl;
	}
}

// get an item at a specified position of the ListBooking (retrieve)
Type ListBooking::get(int index) {
	Node* current = firstNode;
	for (int i = 1; i < index; i++) {
		current = current->next;
	}
	return current->item;
}

// check if the ListBooking is empty
bool ListBooking::isEmpty() {
	return size == 0;
}

// check the size of the ListBooking
int ListBooking::getLength() {
	return size;
}

// display all the items in the ListBooking
void ListBooking::print() {
	Node* temp = firstNode;
	Type item;
	while (temp != NULL) {
		item = temp->item;
		cout << item.getGuestName() << " ";
		cout << item.getRoomType() << " ";
		cout << item.getStatus() << endl;
		temp = temp->next;
	}
}