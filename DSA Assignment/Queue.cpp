#include "Queue.h"
// constructor
Queue::Queue() 
{
	frontNode = NULL;
	backNode = NULL;
}

Queue::~Queue() {}

// enqueue (add) item at the back of queue
bool Queue::enqueue(ItemType item)
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
bool Queue::dequeue(ItemType& item) 
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
void Queue::getFront(ItemType& item) 
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
	if (!isEmpty()) // check if check is emepty
	{
		if (frontNode == backNode) // if there is only 1 item in queue
			cout << frontNode->item << endl;
		else
		{
			Node* temp = frontNode;
			while (temp != NULL)
			{
				cout << temp->item << endl;
				temp = temp->next;
			}
		}
	}
}
