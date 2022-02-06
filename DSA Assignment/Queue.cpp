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
	{
		// set back node's next pointer to point to new node
		backNode->next = temp;
		// set back node (pointer) to point to new node
		backNode = temp;
	}

	return true;
}

// enqueue (add) item at the back of queue based on Check in date
bool Queue::enqueueBooking(ItemType3 data)
{
	// create new node
	Node* temp = new Node();
	temp->item = data;
	temp->next = NULL;
	Queue tempQ = Queue();

	if (isEmpty())
	{
		enqueue(data);
	}
	else
	{
		struct tm temCheckInDate = backNode->item.getCheckInDate();
		struct tm temInputtedDate = data.getCheckInDate();
		tm* tempCheckInDate = &(temCheckInDate);
		tm* tempInputtedDate = &temInputtedDate;

		tempCheckInDate->tm_year -= 1900;
		tempCheckInDate->tm_mon -= 1;
		tempCheckInDate->tm_hour = 0;
		tempCheckInDate->tm_min = 0;
		tempCheckInDate->tm_sec = 0;
		tempCheckInDate->tm_isdst = -1;

		tempInputtedDate->tm_year -= 1900;
		tempInputtedDate->tm_mon -= 1;
		tempInputtedDate->tm_hour = 0;
		tempInputtedDate->tm_min = 0;
		tempInputtedDate->tm_sec = 0;
		tempInputtedDate->tm_isdst = -1;

		time_t tCheckInDate = mktime(tempCheckInDate);
		time_t tInputtedDate = mktime(tempInputtedDate);

		if (difftime(tCheckInDate, tInputtedDate) <= 0)
		{
			enqueue(data);
		}
		else
		{
			bool inserted = false;
			while (!isEmpty())
			{
				Booking temp2 = Booking();
				struct tm temCHECKDATE = frontNode->item.getCheckInDate();
				tm* tempCHECKDATE = &temCHECKDATE;

				tempCHECKDATE->tm_year -= 1900;
				tempCHECKDATE->tm_mon -= 1;
				tempCHECKDATE->tm_hour = 0;
				tempCHECKDATE->tm_min = 0;
				tempCHECKDATE->tm_sec = 0;
				tempCHECKDATE->tm_isdst = -1;

				time_t tCHECKDATE = mktime(tempCHECKDATE);

				if (difftime(tCHECKDATE, tInputtedDate) >= 0 && inserted == false) {
					tempQ.enqueue(data);
					inserted = true;
				}
				dequeue(temp2);
				tempQ.enqueue(temp2);
			}
			while (!tempQ.isEmpty())
			{
				Booking temp2 = Booking();
				tempQ.dequeue(temp2);
				enqueue(temp2);
			}

		}
	}
	return true;
}

// enqueue (add) item at the back of queue based on Check out date
bool Queue::enqueueCheckIn(ItemType3 data)
{
	// create new node
	Node* temp = new Node();
	temp->item = data;
	temp->next = NULL;
	Queue tempQ = Queue();

	if (isEmpty())
	{
		enqueue(data);
	}
	else
	{
		struct tm temCheckOutDate = backNode->item.getCheckOutDate();
		struct tm temInputtedDate = data.getCheckOutDate();
		tm* tempCheckOutDate = &(temCheckOutDate);
		tm* tempInputtedDate = &temInputtedDate;

		tempCheckOutDate->tm_year -= 1900;
		tempCheckOutDate->tm_mon -= 1;
		tempCheckOutDate->tm_hour = 0;
		tempCheckOutDate->tm_min = 0;
		tempCheckOutDate->tm_sec = 0;
		tempCheckOutDate->tm_isdst = -1;

		tempInputtedDate->tm_year -= 1900;
		tempInputtedDate->tm_mon -= 1;
		tempInputtedDate->tm_hour = 0;
		tempInputtedDate->tm_min = 0;
		tempInputtedDate->tm_sec = 0;
		tempInputtedDate->tm_isdst = -1;

		time_t tCheckOutDate = mktime(tempCheckOutDate);
		time_t tInputtedDate = mktime(tempInputtedDate);

		if (difftime(tCheckOutDate, tInputtedDate) <= 0)
		{
			enqueue(data);
		}
		else
		{
			bool inserted = false;
			while (!isEmpty())
			{
				Booking temp2 = Booking();
				struct tm temCHECKDATE = frontNode->item.getCheckOutDate();
				tm* tempCHECKDATE = &temCHECKDATE;

				tempCHECKDATE->tm_year -= 1900;
				tempCHECKDATE->tm_mon -= 1;
				tempCHECKDATE->tm_hour = 0;
				tempCHECKDATE->tm_min = 0;
				tempCHECKDATE->tm_sec = 0;
				tempCHECKDATE->tm_isdst = -1;

				time_t tCHECKDATE = mktime(tempCHECKDATE);

				if (difftime(tCHECKDATE, tInputtedDate) >= 0 && inserted == false) {
					tempQ.enqueue(data);
					inserted = true;
				}
				dequeue(temp2);
				tempQ.enqueue(temp2);
			}
			while(!tempQ.isEmpty())
			{
				Booking temp2 = Booking();
				tempQ.dequeue(temp2);
				enqueue(temp2);
			}

		}
	}
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
	cout << "Id     Booking Date       Guest Name       Room #       Room Type           Status       Check in       Check out       Guests #       Special Requests\n";
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	if (!isEmpty()) // check if check is emepty
	{
		if (frontNode == backNode) // if there is only 1 item in queue
		{
			cout << frontNode->item.getID() << "    ";
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
			cout << frontNode->item.getRoomType() << "           ";
			if (frontNode->item.getStatus() == 0) { cout << "Checked Out       "; }
			else if (frontNode->item.getStatus() == 1) { cout << "Checked In       "; }
			else if (frontNode->item.getStatus() == 2) { cout << "Booked       "; }
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
				cout << temp->item.getID() << "  ";
				cout << temp->item.getBookingDate().tm_mday << "/" << temp->item.getBookingDate().tm_mon << "/" << temp->item.getBookingDate().tm_year << "       ";
				cout << temp->item.getGuestName() << "       ";
				if (temp->item.getRoomNo() == -1) { cout << "-       "; }
				else
				{
					cout << "Room " << temp->item.getRoomNo() << "       ";
				}
				cout << temp->item.getRoomType() << "          ";
				if (temp->item.getStatus() == 0) { cout << "Checked Out       "; }
				else if (temp->item.getStatus() == 1) { cout << "Checked In       "; }
				else if (temp->item.getStatus() == 2) { cout << "Booked       "; }
				cout << temp->item.getCheckInDate().tm_mday << "/" << temp->item.getCheckInDate().tm_mon << "/" << temp->item.getCheckInDate().tm_year << "       ";
				cout << temp->item.getCheckOutDate().tm_mday << "/" << temp->item.getCheckOutDate().tm_mon << "/" << temp->item.getCheckOutDate().tm_year << "       ";
				cout << temp->item.getNumofGuest() << "       ";
				cout << temp->item.getSpecialRequest() << "       \n";
				temp = temp->next;
			}
		}
	}
}
