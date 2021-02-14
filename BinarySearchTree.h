// Binary Search Tree ADT
// Created by Jooyul Yoon
// Modified by: Jiayan Dong
// IDE: MSVS 2019
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int compare(ItemType&, ItemType&));
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr,  ItemType target, bool & success, int compare(ItemType&, ItemType&));
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* nodePtr,  ItemType & target, int compare(ItemType&, ItemType&)) const;

	// find the smallest node, called by internal find smallest
	BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr) const;

	// find the largest node, called by internal find largest
	BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr) const;

	// Find all nodes that are same as the target node and then visit them.
	void _findVisit(BinaryNode<ItemType>* nodePtr, ItemType& target, int compare(ItemType&, ItemType&), void visit(ItemType&)) const;
   
public:  
	// insert a node at the correct location
    bool insert( ItemType & newEntry, int compare(ItemType&, ItemType&));
	// remove a node if found
	bool remove( ItemType & anEntry, int compare(ItemType&, ItemType&));
	// find a target node
	bool getEntry( ItemType & target, ItemType & returnedItem, int compare(ItemType&, ItemType&)) const;
	// find the smallest
	bool findSmallest(ItemType& returnedItem) const;
	// find the largest
	bool findLargest(ItemType& returnedItem) const;
	// Find all nodes that are same as the target node and then visit them.
	void findVisit(ItemType& anEntry, int compare(ItemType&, ItemType&), void visit(ItemType&)) { _findVisit(this->rootPtr, anEntry, compare, visit); }

};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert( ItemType & newEntry, int compare(ItemType&, ItemType&))
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
	this->count++;
	return true;
}  

//Removing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove( ItemType & target, int compare(ItemType&, ItemType&))
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful, compare);
	if (isSuccessful)
		this->count--;
	return isSuccessful; 
}  

//Finding entries within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry( ItemType& anEntry, ItemType & returnedItem, int compare(ItemType&, ItemType&)) const
{
	BinaryNode<ItemType>* nodePtr = findNode(this->rootPtr, anEntry, compare);
	if (nodePtr)
	{
		returnedItem = nodePtr->getItem();
		return true;
	}
	return false;
}  

// Finding the smallest within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType& returnedItem) const
{
	BinaryNode<ItemType>* nodePtr = _findSmallest(this->rootPtr);
	if (nodePtr)
	{
		returnedItem = nodePtr->getItem();
		return true;
	}
	return false;
}

// Finding the largest within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType& returnedItem) const
{
	BinaryNode<ItemType>* nodePtr = _findLargest(this->rootPtr);
	if (nodePtr)
	{
		returnedItem = nodePtr->getItem();
		return true;
	}
	return false;
}


//////////////////////////// private functions ////////////////////////////////////////////
//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr, int compare(ItemType&, ItemType&))
{
	if (!nodePtr)
		nodePtr = newNodePtr;
	else
	{
		ItemType newItem = newNodePtr->getItem();
		ItemType item = nodePtr->getItem();
		if (compare(newItem, item) == -1)
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, compare));
		else
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, compare));
	}
	return nodePtr;
}  

//Implementation of the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                           ItemType target,
                                                          bool & success, int compare(ItemType&, ItemType&))
{
	if (!nodePtr)                   
	{
		success = false;
		return 0;
	}
	ItemType item = nodePtr->getItem();
	if (compare(item, target) == 1)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, compare));
	else if (compare(item, target) == -1)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  
//Implementation of the delete operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  
//Implementation to remove the left leaf
template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

//Implementation for the search operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           ItemType & target, int compare(ItemType&, ItemType&)) const
{
	BinaryNode<ItemType>* found = 0;
	BinaryNode<ItemType>* pWalk = nodePtr;
	while (pWalk != 0 && !found)
	{
		ItemType item = pWalk->getItem();
		if (compare(target, item) == -1)
			pWalk = pWalk->getLeftPtr();
		else
		{
			if (compare(target, item) == 1)
				pWalk = pWalk->getRightPtr();
			else
				found = pWalk;
		}
	}

	return found;
}  

//Implementation for the search find smallest operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr->getLeftPtr())
		return _findSmallest(nodePtr->getLeftPtr());
	return nodePtr;
}

//Implementation for the search find largest operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr->getRightPtr())
		return _findLargest(nodePtr->getRightPtr());
	return nodePtr;
}

// Find all nodes that are same as the target node and then visit them.
template<class ItemType>
void BinarySearchTree<ItemType>::_findVisit(BinaryNode<ItemType>* nodePtr, ItemType& target, int compare(ItemType&, ItemType&), void visit(ItemType&)) const
{
	BinaryNode<ItemType>* pWalk = nodePtr;
	if (pWalk == 0)
		return;
	ItemType item = pWalk->getItem();
	if (compare(target, item) == -1)
		pWalk = pWalk->getLeftPtr();
	else if (compare(target, item) == 1)
		pWalk = pWalk->getRightPtr();
	else
	{
		ItemType item = pWalk->getItem();
		visit(item);
		pWalk = pWalk->getRightPtr();
	}
	_findVisit(pWalk, target, compare, visit);
}
#endif
