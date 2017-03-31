//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Link-based implementation.
    Listing 7-3.
    @file LinkedStack.h */

#ifndef LINKED_STACK_
#define LINKED_STACK_

#include "node1.h"
#include <sstream>
#include <iostream>


template<class ItemType>
class LinkedStack  
{
private:
	Node<ItemType>* topPtr; // Pointer to first node in the chain;
                           // this node contains the stack's top
    int m_Count   ;  // added 
    ItemType _NULL;

public:
// Constructors and destructor:
	LinkedStack();                                   // Default constructor
    LinkedStack(const LinkedStack<ItemType>& aStack);// Copy constructor
	virtual ~LinkedStack();                          // Destructor

// Stack operations:
/**< isEmpty() is same as empty() */
	bool isEmpty() const;     // 
	bool empty() const;       // added
	
	bool push(const ItemType& newItem);
	
/**< pop returning value was added  */	
    bool pop( ItemType & tempPtr);
    bool pop( void );
    
/**< contains was added */    
    bool contains( const ItemType& lookFor ) const   ;
    
/**< peek() is same as top() */
	ItemType peek() const;
	ItemType top() const;
	
/**< getCount() was added */
	int getCount() {return m_Count ; }
}; // end LinkedStack

#include "linkedstack.cpp"
#endif
