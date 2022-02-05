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


int Dictionary::hash(KeyType key){
	return key % MAX_SIZE;
}

// add a new item with the specified key to the Dictionary
// pre : none
// post: new item is added to the Dictionary
//       size of Dictionary is increased by 1
bool Dictionary::add(KeyType newKey, ItemType newItem){
	int index = hash(newKey);
	if (items[index] == NULL) {
		Node *newNode = new Node();
		newNode->item = newItem;
		newNode->key = newKey;
		newNode->next = NULL;

		items[index] = newNode;
	}
	else {
		Node* current = items[index];
		if (current->key == newKey) {
			return false;
		}
		while (current->next != NULL)
		{
			current = current->next;
			if (current->key == newKey) {
				return false;
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
ItemType Dictionary::get(KeyType key) {
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

// void Dictionary::replace(KeyType key, ItemType item){}
// bool Dictionary::contains(KeyType key){}
