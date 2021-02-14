// Hash Table ADT
// Created by Zeyu Zhao
// Modified by: Jiayan Dong
// IDE: MSVS 2019
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include"List.h"
#include <string>

template <class T>
class HashTable
{
    List<T>* array;
    // hash function borrowed from: Thomas Wang https://gist.github.com/badboy/6267743
    int hash(string key) const
    {
        int TKey = stoi(key);
        int c2 = 0x27d4eb2d; // a prime or an odd constant
        TKey = (TKey ^ 61) ^ (TKey >> 16);
        TKey = TKey + (TKey << 3);
        TKey = TKey ^ (TKey >> 4);
        TKey = TKey * c2;
        TKey = TKey ^ (TKey >> 15);
        return TKey % size;
    }
	int size;
    int count; // number of values stored in the hash table
public:
	HashTable() { size = 100; count = 0; array = new List<T>[size]; }
	HashTable(int s) { size = s; count = 0; array = new List<T>[size]; }
	~HashTable() { delete[] array; }

	void setSize(int s);

    bool insert(T value, string get(T&), int compare(T&, T&));//insert new node to linked list
    bool remove(T value, string get(T&), int compare(T&, T&));//remove a node from hash table
    bool search(T value, T& returnvalue, string get(T&), int compare(T&, T&));//return true if found

	void saveTable(ofstream&, void save(ofstream&, T&));
    void printTable(void visit(T&)) const;

	int getSize() const { return size; }
	int getCount() const {return count;}
	int getCollisions() const;
	double getLoadFactor() const;
};

template <class T>
void HashTable<T>::setSize(int s)
{
	delete[] array;
	count = 0;
	size = s;
	array = new List<T>[s];
}


template <class T>
bool HashTable<T>::insert(T item, string get(T&), int compare(T&, T&))
{
	string key = get(item);
	int hashValue = hash(key);
	if (array[hashValue].insertNode(item, compare))
	{
		count++;
		return true;
	}
	else
		return false;
}

template <class T>
bool HashTable<T>::remove(T item, string get(T&), int compare(T&, T&))
{
	string key = get(item);
	int hashValue = hash(key);
	if (array[hashValue].deleteNode(item, compare))
	{
		count--;
		return true;
	}
	else
		return false;
}

template <class T>
bool HashTable<T>::search(T item, T& returnValue, string get(T&), int compare(T&, T&))
{
	string key = get(item);
	int hashValue = hash(key);
	if (array[hashValue].searchList(item, returnValue, compare))
		return true;
	else
		return false;
}

template <class T>
void HashTable<T>::saveTable(ofstream& s, void visit(ofstream&, T&))
{
	for (int i = 0; i < size; i++)
		array[i].saveList(s, visit);
}

template <class T>
void HashTable<T>::printTable(void visit(T&)) const
{
	for (int i = 0; i < size; i++)
		array[i].printList(visit);
}

template <class T>
int HashTable<T>::getCollisions() const
{
	int collision = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i].getCount() > 1)
			collision += array[i].getCount() - 1;
	}
	return collision;
}

template <class T>
double HashTable<T>::getLoadFactor() const
{
	double load = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i].getCount() > 0)
			load++;
	}
	return load / size;
}
#endif
