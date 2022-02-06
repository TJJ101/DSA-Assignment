#include "Queue.h"
#include <string>
// constructor
Queue::Queue() 
{
	frontNode = NULL;
	backNode = NULL;
}

Queue::~Queue() {}

// enqueue (add) item at the back of queue
bool Queue::enqueue(ItemType3 item)
{
	// create new node
	Node* temp = new Node();
	temp->item = item;
	temp->next = NULL;

	if (isEmpty())
	{
		// set front node (pointer) to point to new node
		frontNode = temp;
		backNode = temp;
	}
	else
		// set back node's next pointer to point to new node
		backNode->next = temp;

	// set back node (pointer) to point to new node
	backNode = temp;
	return true;
}

// dequeue (remove) item from front of queue
bool Queue::dequeue() 
{
	if (frontNode == backNode)
	{
		frontNode = NULL;
		backNode = NULL;

	}
	else
	{
		Node* temp = frontNode;
		frontNode = frontNode->next;
		temp->next = NULL;
		delete(temp);
	}
	return true;
}

// dequeue (remove) and retrieve item from front of queue
bool Queue::dequeue(ItemType3& item) 
{
	if (frontNode == backNode)
	{
		item = frontNode->item;
		frontNode = NULL;
		backNode = NULL;

	}
	else
	{
		Node* temp = frontNode;
		frontNode = frontNode->next;
		temp->next = NULL;
		item = temp->item;
		delete(temp);
	}
	return true;
}

// retrieve (get) item from front of queue
void Queue::getFront(ItemType3& item) 
{
	if (!isEmpty())
		item = frontNode->item;
}

// check if the queue is empty
bool Queue::isEmpty() 
{
	if (frontNode != NULL and backNode != NULL)
		return false;
	else
		return true;
}

// display items in queue from front to back
void Queue::displayItems() 
{
	cout << "Id       Booking Date       Guest Name       Room #       Room Type       Status       Check in       Check out       Guests #       Special Requests\n";
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	if (!isEmpty()) // check if check is emepty
	{
		if (frontNode == backNode) // if there is only 1 item in queue
		{
			cout << frontNode->item.getID() << "       ";
			cout << frontNode->item.getBookingDate().tm_mday << "/" << frontNode->item.getBookingDate().tm_mon << "/" << frontNode->item.getBookingDate().tm_year << "       ";
			cout << frontNode->item.getGuestName() << "       ";
			if (frontNode->item.getRoomNo() == -1)
			{
				cout << "-       ";
			}
			else
			{
				cout << "Room " << frontNode->item.getRoomNo() << "       ";
			}
			cout << frontNode->item.getRoomType() << "       ";
			cout << frontNode->item.getStatus() << "       ";
			cout << frontNode->item.getCheckInDate().tm_mday << "/" << frontNode->item.getCheckInDate().tm_mon << "/" << frontNode->item.getCheckInDate().tm_year << "       ";
			cout << frontNode->item.getCheckOutDate().tm_mday << "/" << frontNode->item.getCheckOutDate().tm_mon << "/" << frontNode->item.getCheckOutDate().tm_year << "       ";
			cout << frontNode->item.getNumofGuest() << "       ";
			cout << frontNode->item.getSpecialRequest() << "       \n";
		}
		else
		{
			Node* temp = frontNode;
			while (temp != NULL)
			{
				cout << temp->item.getID() << "       ";
				cout << temp->item.getBookingDate().tm_mday << "/" << temp->item.getBookingDate().tm_mon << "/" << temp->item.getBookingDate().tm_year << "       ";
				cout << temp->item.getGuestName() << "       ";
				if (temp->item.getRoomNo() == -1)
				{
					cout << "-       ";
				}
				else
				{
					cout << "Room " << temp->item.getRoomNo() << "       ";
				}
				cout << temp->item.getRoomType() << "       ";
				cout << temp->item.getStatus() << "       ";
				cout << temp->item.getCheckInDate().tm_mday << "/" << temp->item.getCheckInDate().tm_mon << "/" << temp->item.getCheckInDate().tm_year << "       ";
				cout << temp->item.getCheckOutDate().tm_mday << "/" << temp->item.getCheckOutDate().tm_mon << "/" << temp->item.getCheckOutDate().tm_year << "       ";
				cout << temp->item.getNumofGuest() << "       ";
				cout << temp->item.getSpecialRequest() << "       \n";
				temp = temp->next;
			}
		}
	}
}
