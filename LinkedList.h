//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT list: Link-based implementation.
    Listing 9-2.
    @file LinkedList.h */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
//@system depends: iostream, string
#include <iostream>
#include <string>
//@depends: Node.h, ListInterface.h, PrecondViolatedExcept.h
#include "Node.h"
#include "ListInterface.h"
#include "PrecondViolatedExcept.h"
//@class: LinkedList<ItemType>
//@inherits: ListInterface<ItemType>
//@description: 
template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
   Node<ItemType>* headPtr; // @var: headPtr
							// Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items 
   
   // @function: getNodeAt(int) 
   // @desc: Locates a specified node in this linked list.
   // @pre:  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post:  The node is found and a pointer to it is returned.
   // @param: "position"  The number of the node to locate.
   // @return:  A pointer to the node at the given position.
   Node<ItemType>* getNodeAt(int position) const;
   int position =0; 
   
public:
   LinkedList();
   LinkedList(const LinkedList<ItemType>& aList);
   virtual ~LinkedList();
	Node<ItemType>* prevPtr;
	Node<ItemType>* curPtr;
   bool isEmpty() const;
   int getLength() const;

   // @function: insert(int ,const ItemType&)
   // @param: newPosition
   // @param: newEntry
   // @pre: 
   // @post
   bool insert(int newPosition, const ItemType& newEntry);

   // @function: insertNode(int , Node<ItemType>* , Node<ItemType>* )
     // @param: position
     // @param: newNodePtr
     // @param: subChainPtr 
     // @pre:
     // @post:
	Node<ItemType>* insertNode(int position, Node<ItemType>* newNodePtr, Node<ItemType>* subChainPtr);
  
   // @function: remove(int) 
   // @param: position
   bool remove(int position);

   // @function: clear() 
   
   void clear();
   
   /** @throw PrecondViolatedExcept if position < 1 or
                                       position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcept);

   /** @throw PrecondViolatedExcept if position < 1 or
                                       position > getLength(). */
   void replace(int position, const ItemType& newEntry)
                              throw(PrecondViolatedExcept);
  
}; // end LinkedList
#include "LinkedList.cpp"

#endif 
