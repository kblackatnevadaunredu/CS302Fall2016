//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.h
    Listing 4-1 */
#ifndef NODE_
#define NODE_

template<class ItemType>
class Node
{
private:
   ItemType        m_Item; // A data item
   Node<ItemType>* next; // Pointer to next node

public:
   Node();
   Node(const ItemType& anItem);
   Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
   void setItem(const ItemType& anItem);
   void setNext(Node<ItemType>* nextNodePtr);
   ItemType getItem() const ;
   ItemType Item() const { return m_Item ; }
   void Item( ItemType val ) { m_Item = val ; }
   Node<ItemType>* getNext() const ;
}; // end Node

#include "node1.cpp"
#endif
