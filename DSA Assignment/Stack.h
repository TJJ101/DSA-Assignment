// Stack.h (Pointer-based implementation)
#pragma once
#include <iostream>
#include "Booking.h"
using namespace std;

typedef Booking ItemType4;

class Stack
{
private:
	struct Node
	{
		ItemType4 item;
		Node* next;
	};

	Node* topNode;

public:
	//Default constructor
	Stack();
	//Destructor
	~Stack();

	//check if the stack is empty
	bool isEmpty();

	//push item on top of the stack
	bool push(ItemType4 item);

	//pop item from top of stack
	bool pop();

	//retrieve and pop item from top of stack
	bool pop(ItemType4& item);

	//retrieve item from top of stack
	void getTop(ItemType4& item);

	//display items in stack in order
	void displayInOrder();

	//display items in stack in order of insertion
	void displayInOrderOfInsertion();
};
