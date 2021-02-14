// Specification file for the List class
// Written By: Jiayan Dong
// IDE: MSVS 2019

#ifndef LIST_H
#define LIST_H

using namespace std;

template <class T>
class List
{
private:
    struct ListNode{
        T value;
        ListNode *next;
    };
    ListNode *head;
    int count;
    
public:
    //Constructor
	List() { head = new ListNode; head->next = head; count = 0; }
    
    // Linked list operations
	//Compare function return -1 is left < right, return 1 is left > right, return 0 is left = right
    bool insertNode(T, int compare(T&, T&));
	bool deleteNode(T, int compare(T&, T&));
	bool searchList( T, T&, int compare(T&, T&));

	void saveList(ofstream&, void save(ofstream&, T&));
	void printList(void visit(T&));
    int getCount() {return count;}
    
    //Destructor
	~List();
};

template <class T>
List<T>::~List()
{
	ListNode* currNode, * nextNode;

	currNode = head->next;

	while (currNode != head && currNode != NULL)
	{
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	delete head;
}

template <class T>
bool List<T>::insertNode(T item, int compare(T&, T&))
{	
	ListNode *currNode, *preNode;
	preNode = head;
	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		if (compare(item, currNode->value) == 0)
			return false;
		preNode = currNode;
		currNode = currNode->next;
	}

	ListNode* newNode = new ListNode;
	newNode->value = item;
	newNode->next = NULL;
	if (currNode == head)
		head->next = newNode;
	else
		preNode->next = newNode;
	count++;

	return true;
}

template <class T>
bool List<T>::deleteNode(T item, int compare(T&, T&))
{
	ListNode* currNode, * preNode;

	preNode = head;
	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		if (compare(item, currNode->value) == 0)
		{
			preNode->next = currNode->next;
			delete currNode;
			count--;
			return true;
		}
		preNode = currNode;
		currNode = currNode->next;
	}

	return false;
}

template <class T>
bool List<T>::searchList( T item, T& returnItem, int compare(T&, T&))
{
	ListNode* currNode, * preNode;

	preNode = head;
	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		if (compare(item, currNode->value) == 0)
		{
			returnItem = currNode->value;
			return true;
		}
		preNode = currNode;
		currNode = currNode->next;
	}
	return false;
}

template <class T>
void List<T>::saveList(ofstream& s, void save(ofstream&, T&))
{
	ListNode* currNode;

	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		T item = currNode->value;
		save(s, item);
		currNode = currNode->next;
	}
}

template <class T>
void List<T>::printList(void visit(T&))
{
	ListNode* currNode;

	currNode = head->next;
	while (currNode != head && currNode != NULL)
	{
		T item = currNode->value;
		visit(item);
		currNode = currNode->next;
	}
}
#endif
