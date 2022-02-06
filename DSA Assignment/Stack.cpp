#include "Stack.h"
//Default constructor
Stack::Stack() { topNode = NULL; }
//Destructor
Stack::~Stack() {}

//check if the stack is empty
bool Stack::isEmpty() { return topNode == NULL; }

//push item on top of the stack
bool Stack::push(ItemType4 item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = topNode;
	topNode = newNode;
	return true;
}

//pop item from top of stack
bool Stack::pop()
{
	if (!isEmpty())
	{
		Node* temp = topNode;
		topNode = topNode->next;
		temp->next = NULL;
		delete temp;
		return true;
	}
	else
	{
		return false;
	}
}

//retrieve and pop item from top of stack
bool Stack::pop(ItemType4& item)
{
	if (!isEmpty())
	{
		Node* temp = topNode;
		topNode = topNode->next;
		temp->next = NULL;
		item = temp->item; // Store the value in item to be passed back through paremeter
		delete temp;
		return true;
	}
	else
	{
		return false;
	}
}

//retrieve item from top of stack
void Stack::getTop(ItemType4& item)
{
	if (!isEmpty())
	{
		item = topNode->item;
	}
}

//display items in stack in order - the stack should not change, don't create a temp and use a temp->next to move
void Stack::displayInOrder()
{
	ItemType4 item;
	Stack tempStack;
	if (!isEmpty())
	{
		cout << "Id       Booking Date       Guest Name       Room #       Room Type       Status       Check in       Check out       Guests #       Special Requests\n";
		while (!isEmpty())  // the stack is popped until it is empty.
		{					// original stackc has 1, 2, 3 with 3 being the
			getTop(item);	// tempStack will have 3, 2, 1 and original stack is empty
			cout << item.getID() << "       ";
			cout << item.getBookingDate().tm_mday << "/" << item.getBookingDate().tm_mon << "/" << item.getBookingDate().tm_year << "       ";
			cout << item.getGuestName() << "       ";
			if (item.getRoomNo() == -1)
			{
				cout << "-       ";
			}
			else
			{
				cout << "Room " << item.getRoomNo() << "       ";
			}
			cout << item.getRoomType() << "       ";
			cout << item.getStatus() << "       ";
			cout << item.getCheckInDate().tm_mday << "/" << item.getCheckInDate().tm_mon << "/" << item.getCheckInDate().tm_year << "       ";
			cout << item.getCheckOutDate().tm_mday << "/" << item.getCheckOutDate().tm_mon << "/" << item.getCheckOutDate().tm_year << "       ";
			cout << item.getNumofGuest() << "       ";
			cout << item.getSpecialRequest() << "       \n";
			tempStack.push(item); // push totempStack
			pop();
		}
		// restore the orignal stack
		while (!tempStack.isEmpty())
		{
			tempStack.getTop(item);
			push(item);
			tempStack.pop();
		}
	}
	else
	{
		cout << "The Stack is empty.\m";
	}
}

//display items in stack in order of insertion
void Stack::displayInOrderOfInsertion()
{
	ItemType4 item;
	Stack tempStack;
	if (!isEmpty())
	{
		cout << "Id       Booking Date       Guest Name       Room #       Room Type       Status       Check in       Check out       Guests #       Special Requests\n";
		cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		while (!isEmpty())  // the stack is popped until it is empty.
		{					// original stackc has 1, 2, 3 with 3 being the
			getTop(item);	// tempStack will have 3, 2, 1 and original stack is empty
			tempStack.push(item); // push totempStack
			pop();
		}
		// restore the orignal stack
		while (!tempStack.isEmpty())
		{
			tempStack.getTop(item);
			cout << item.getID() << "       ";
			cout << item.getBookingDate().tm_mday << "/" << item.getBookingDate().tm_mon << "/" << item.getBookingDate().tm_year << "       ";
			cout << item.getGuestName() << "       ";
			if (item.getRoomNo() == -1)
			{
				cout << "-       ";
			}
			else
			{
				cout << "Room " << item.getRoomNo() << "       ";
			}
			cout << item.getRoomType() << "       ";
			cout << item.getStatus() << "       ";
			cout << item.getCheckInDate().tm_mday << "/" << item.getCheckInDate().tm_mon << "/" << item.getCheckInDate().tm_year << "       ";
			cout << item.getCheckOutDate().tm_mday << "/" << item.getCheckOutDate().tm_mon << "/" << item.getCheckOutDate().tm_year << "       ";
			cout << item.getNumofGuest() << "       ";
			cout << item.getSpecialRequest() << "       \n";
			push(item);
			tempStack.pop();
		}
	}
	else
	{
		cout << "The Stack is empty.\m";
	}
}