CC=g++
OBJECTS=Black_Kelly_PA01.o Node.o  ListInterface.o LinkedList.o PrecondViolatedExcept.o #FFFFFF
SOURCES=Black_Kelly_PA01.cpp PrecondViolatedExcept.cpp Node.cpp ListInterface.cpp  LinkedList.h 
FLAGS= -Wall


ALL:	$(OBJECTS)	$(SOURCES)	
	$(CC) $(FLAGS) $(OBJECTS) -o Black_Kelly_PA01

Black_Kelly_PA01.o:	Black_Kelly_PA01.cpp
	$(CC) -c Black_Kelly_PA01.cpp
	
Node.o:	Node.h Node.cpp
	$(CC) -c Node.h Node.cpp 
	
LinkedList.o:	LinkedList.h LinkedList.cpp
	$(CC) -c LinkedList.h LinkedList.cpp
	
ListInterface.o:	ListInterface.h	ListInterface.cpp
	$(CC) -c  ListInterface.h ListInterface.cpp 
	
PrecondViolatedExcept.o:	PrecondViolatedExcept.h PrecondViolatedExcept.cpp
	$(CC) -c PrecondViolatedExcept.cpp   
	
clean:
		rm *.o
		
