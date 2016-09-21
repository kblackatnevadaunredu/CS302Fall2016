
 
#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.h"

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
} // end default constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
   clear();
} // end destructor


// The public method insert:
template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
      headPtr = insertNode(newPosition, newNodePtr, headPtr);
   } // end if
   return ableToInsert;
} // end insert


template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      Node<ItemType>* curPtr = nullptr;
      if (position == 1)
      {
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
      }
      else
      {
         // Find node that is before the one to remove
         Node<ItemType>* prevPtr = getNodeAt(position -1);
         
         // Point to node to remove
         curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      } // end if
      
      // Return node to system
      curPtr->setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      itemCount--; // Decrease count of entries
   } // end if
   
   return ableToRemove;
} // end remove

// The private method insertNode:
// Adds a given node to the subchain pointed to by subChainPtr
// at a given position. Returns a pointer to the augmented subchain.
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::insertNode(int position, Node<ItemType>* newNodePtr, Node<ItemType>* subChainPtr)
{
   if (position == 1)
   {
      // Insert new node at beginning of subchain
      newNodePtr->setNext(subChainPtr);
      subChainPtr = newNodePtr;
      itemCount++;  // Increase count of entries
   }
   else
   {
      Node<ItemType>* afterPtr = insertNode(position - 1, newNodePtr, subChainPtr->getNext());
      subChainPtr->setNext(afterPtr);
   }  // end if
   
   return subChainPtr;
}  // end insertNode

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const

{
	Node<ItemType>* curPtr = nullptr;
   // Debugging check of precondition
   if( (position >= 1) && (position <= itemCount) ){
   // Count from the beginning of the chain
   curPtr = headPtr;
   for (int skip = 1; skip < position; skip++){
      curPtr = curPtr->getNext();
  }
  }
	return curPtr;
}  // end getNodeAt

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
} // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcept)
{
	if((position >=1) && (position <= itemCount)){
            Node<ItemType>* temp =  getNodeAt(position);
			return  *(ItemType*)temp;
	}	else {

		throw  PrecondViolatedExcept("Invalid Position");
	}
}
template<class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry)
                              throw(PrecondViolatedExcept)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
		ItemType oldEntry = getEntry(position);
		curPtr = this->headPtr ;
		bool nomatch = true;
		while(nomatch){
           ItemType theThing = curPtr->getItem() ;

			if(oldEntry==theThing){
                ItemType cloneEntry = newEntry;
                
				curPtr->setItem(cloneEntry) ;
				nomatch=false;
			}		   
			curPtr  = curPtr->getNext();
		  
		}


   }
   else
   {
      std::string message = "replace() called with an empty list or ";
      message = message + "invalid position.";
      throw(PrecondViolatedExcept(message));
   } // end if
}  // end replace
 #include "LinkedList.h"
#endif

