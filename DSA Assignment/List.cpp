#include "List.h"

// constructor
List::List(){size = 0;}

// destructor
List::~List(){}

// add an item to the back of the list (append)
bool List::add(ItemType item){
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	if (firstNode == NULL){
		firstNode = newNode;
	}
	else {
		Node* temp = firstNode;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}

	size++;
	return true;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, ItemType item){
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

// remove an item at a specified position in the list
void List::remove(int index){
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
		cout << "List is empty!" << endl;
	}
}

// get an item at a specified position of the list (retrieve)
ItemType List::get(int index){
	Node* current = firstNode;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->item;
}

// check if the list is empty
bool List::isEmpty(){	
	return size == 0;
}

// check the size of the list
int List::getLength(){
	return size;
}

// display all the items in the list
void List::print(){
	Node* temp = firstNode;
	ItemType item;
	while (temp != NULL)
	{
		item = temp->item;
		cout << item.getRoomNo() << " ";
		cout << item.getRoomType() << " ";
		cout << item.getCostPerNight() << endl;
		temp = temp->next;
	}
}