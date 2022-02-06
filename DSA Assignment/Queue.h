// Queue.h - Specification of Queue ADT (Pointer-based)
// TAN JUN JIE S10194512D
#pragma once
#include<string>
#include<iostream>
#include "Booking.h"
using namespace std;

typedef Booking ItemType3;

class Queue
{
private:
	struct Node
	{
		ItemType3 item;	// item
		Node* next;	// pointer pointing to next item
	};

	Node* frontNode;	// point to the first item
	Node* backNode;	// point to the first item


public:
	// constructor
	Queue();

	~Queue();

	// enqueue (add) item at the back of queue
	bool enqueue(ItemType3 item);

	// dequeue (remove) item from front of queue
	bool dequeue();

	// dequeue (remove) and retrieve item from front of queue
	bool dequeue(ItemType3& item);

	// retrieve (get) item from front of queue
	void getFront(ItemType3& item);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	void displayItems();
};


