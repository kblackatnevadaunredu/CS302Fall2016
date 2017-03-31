// *** ADDED BY HEADER FIXUP ***

// *** END ***
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Listing 7-4.
    @file LinkedStack.cpp */

#include <cassert>        // For assert
#include "linkedstack.h"  // Header file
#include <sstream>
#include <iostream>

#include <istream>

#ifndef LINKED_STACK_CPP

#define LINKED_STACK_CPP



template<class ItemType>
LinkedStack<ItemType>::LinkedStack():
 topPtr(nullptr){





}  // end default constructor

     

/** \brief Copy Constructor
 *
 * \param aStack const LinkedStack<ItemType>&
 *
 */
template<class ItemType>    
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
   // Point to nodes in original chain
   Node<ItemType>* origChainPtr = aStack.topPtr;

   if (origChainPtr == nullptr)
      topPtr = nullptr;  // Original stack is empty
   else
   {
      // Copy first node
      topPtr = new Node<ItemType>();
      topPtr->setItem(origChainPtr->getItem());

      // Point to first node in new chain
      Node<ItemType>* newChainPtr = topPtr;

      // Advance original-chain pointer
      origChainPtr = origChainPtr->getNext();

      // Copy remaining nodes
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while

      newChainPtr->setNext(nullptr);           // Flag end of chain
   }  // end if
}  // end copy constructor


template<class ItemType>
LinkedStack<ItemType>::~LinkedStack(){
	// Pop until stack is empty
	ItemType dummy ;
	while (!isEmpty()){
		pop( dummy );
	}

}  // end destructor


template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
	topPtr = newNodePtr;
   newNodePtr = nullptr;

	return true;
}  // end push


/** \brief pop( ItemType & tempPtr)
 *
 * \param tempPtr ItemType&
 * \return bool
 *
 */
template<class ItemType>     
bool LinkedStack<ItemType>::pop( ItemType & tempPtr){
	bool result = false;
	
	if (!isEmpty())	{
	        
        // Stack is not empty; delete top
        
		Node<ItemType>* nodeToDeletePtr = topPtr ;
		tempPtr = topPtr->getItem();
		topPtr = topPtr->getNext() ;

		// Return deleted node to system
		
        nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        
        // Decrement count and return 
        
	    m_Count--;
        result = true;
        
	}

	return result;
}  // end pop




/** \brief pop( void )
 *
 * \param void
 * \return bool
 *
 */ 
template<class ItemType>    
bool LinkedStack<ItemType>::pop( void ){
	bool result = false;
	if (!isEmpty())	{
        // Stack is not empty; delete top
		Node<ItemType>* nodeToDeletePtr = topPtr ;
		topPtr = topPtr->getNext() ;
		// Return deleted node to system
        nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
	    m_Count--;
        result = true;
	}

	return result;
}  // end pop




/** \brief peek() 
 * \desc: for compatability with STL stack | same function as top()
 * \return ItemType
 *
 */ 
template<class ItemType>   
ItemType LinkedStack<ItemType>::peek() const{
	if(isEmpty()){
		 return _NULL;
	}  // Enforce precondition during debugging

	// Stack is not empty; return top
	return topPtr->getItem();
}  // end getTop



/** \brief top() 
 *
 * \return ItemType
 *
 */   
template<class ItemType> 
ItemType LinkedStack<ItemType>::top() const{
	if(isEmpty()){
		 return _NULL;
	}  // Enforce precondition during debugging

	// Stack is not empty; return top
	return topPtr->getItem();
}  // end getTop






/** \brief isEmpty()
 *
 * \return bool
 *
 */
template<class ItemType>   
bool LinkedStack<ItemType>::isEmpty() const {
   return topPtr == nullptr;
}  // end isEmpty


/** \brief empty()
 * \desc: Added for compatability with STL stack
 * \return bool
 *
 */ 
template<class ItemType>   
bool LinkedStack<ItemType>::empty() const {
   return topPtr == nullptr;
}  // end isEmpty


/** \brief contains(...)
 * \author Kelly Black
 * \desc: Checks if an item is already in the list 
 * \param lookFor const ItemType& - search parameter
 * \return bool - true if item is already in the list
 *
 */ 
template<class ItemType>    
bool LinkedStack<ItemType>::contains( const ItemType& lookFor ) const
{
    if( empty() ){
       return false ; 
    }
    Node<ItemType>* traverse = topPtr ;
    while ( traverse != nullptr ) {
         if( lookFor == traverse->getItem() ){
            return true ; 
         }
         traverse = traverse->getNext()  ;
    }
    return false ;
}

// End of implementation file.
#endif // LINKED_STACK_CPP
