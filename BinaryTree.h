// Binary tree abstract base class
// Created by Jooyul Yoon
// Modified by: Jiayan Dong
// IDE: MSVS 2019
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	// Recursive Depth-First Traversals (DFT)
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}

	void breadthFirst(void visit(ItemType&)) const;
	void printTree(void visit(ItemType&)) const {_printTree(visit, rootPtr, 1, "");}

	// abstract functions to be implemented by derived class
	virtual bool insert( ItemType & newData, int compare(ItemType&, ItemType&)) = 0;
	virtual bool remove( ItemType & data, int compare(ItemType&, ItemType&)) = 0;
	virtual bool getEntry( ItemType & anEntry, ItemType & returnedItem, int compare(ItemType&, ItemType&)) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// Recursive internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _printTree(void visit(ItemType&), BinaryNode<ItemType>* nodePtr, int level, string indentAmt) const;
}; 


//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
		nodePtr = 0;
	}
}  

//Recursive Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

//Recursive Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

//Recursive Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}  

//Print Tree
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType&), BinaryNode<ItemType>* nodePtr, int level, string indentAmt) const
{
	std::cout << indentAmt << "Level " << level << ". ";
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		cout << endl;
		level++;
		indentAmt = indentAmt + "      ";
		if (!nodePtr->isLeaf())
		{
			_printTree(visit, nodePtr->getRightPtr(), level, indentAmt);
			_printTree(visit, nodePtr->getLeftPtr(), level, indentAmt);
		}
	}
	else
		std::cout << "Empty" << std::endl;
}

//Breadth-First Traversal
template<class ItemType>
void BinaryTree<ItemType>::breadthFirst(void visit(ItemType&)) const
{
	Queue<BinaryNode<ItemType>*> q;
	BinaryNode<ItemType>* curr;
	ItemType item;
	if (rootPtr == 0)
		return;
	q.enqueue(rootPtr);
	while (!q.isEmpty())
	{
		q.dequeue(curr);
		item= curr->getItem();
		visit(item);
		if (curr->getLeftPtr() != 0)
			q.enqueue(curr->getLeftPtr());
		if (curr->getRightPtr() != 0)
			q.enqueue(curr->getRightPtr());
	}
}


#endif

