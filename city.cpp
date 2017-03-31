/** ***********************************************************  
 *  \file    : city.cpp
 *  \author  : Kelly Black
 *  \project : PA03 - Flight Paths
 *  \date    : Spring 2017
 *
 *  \description : CITY CLASS IMPLEMENTATION FILE
 *                 CONTAINS CITY NAMES AND DESTINATIONS
 *                 AND OTHER INFORMATION
  ************************************************************* */
                      
 /**< LIBRARIES */    
#include <string>     
#include "string.h"   
#include <iostream>   
#include <cstring>    
#include <stack>      
#include <fstream>    
#include "city.h"     
                      
 using namespace std; 
/**< ========================================================== */
#ifndef CITY_CPP      
#define CITY_CPP      
/**< ========================================================== */
                      
/** \brief  function: Default Constructor
 */
City::City(  ){       
	//cout << " default constructor " << endl;
	
	m_Name = "NO_CITY" ;
    
    m_Filename =  "cityFile.txt"     ;
	//ctor
	m_Destination = nullptr ;
	m_Cost = nullptr ;

    
	 Visited = false ;
    m_DestinationCount = 0 ;
    m_CurrDestIndex = 0 ;
    flightfrom = "NO_CITY" ;
    flightdest= "NO_CITY"  ;
    flightnumb = "000" ;
    flightcost = "0.00" ;
    m_Index = 0 ;
    m_fromPathIndex = 0 ; 


}
                      
// \brief  Default Constructor
                      
/** \brief            
 *
 * \param name const string
 * \param dest const string
 *
 */    
City::City(   string fromname,   string dest ){
	cout << " param constructor " << endl;
	s_Name = fromname ;
	m_Name = fromname ;
	
   // strncpy( m_Name , s_Name.c_str() , s_Name.length()  )  ;
    m_Destination = nullptr        ;
    flightfrom    = fromname       ;
    flightdest    = dest           ;
    flightnumb    = "000"          ;
    flightcost    = "0.00"         ;
    m_Filename    = "cityFile.txt" ;
	//ctor
	
	Visited=false ;
    m_DestinationCount = 0 ;
    m_CurrDestIndex    = 0 ;
    m_Index            = 0 ;
    m_fromPathIndex    = 0 ; 
    
    //cout << __FILE__  << "  " <<  __LINE__  << endl ;

}



/** \brief function:  Destructor
 */
City::~City(){
//dtor
    //cout << "Deleted " << endl ;
    //delete [] m_Destination ;

}



/** \brief function: Copy Constructor
 *
 * \param other const City&
 *
 */
City::City(const City& other){

	if (this == &other || &other==0x0000000 ){
		return ;
	}

    this->m_Index             = other.m_Index             ;
    this->m_fromPathIndex     = other.m_fromPathIndex     ;
	this->m_Name              = other.m_Name              ;
	this->m_DestinationCount  = other.m_DestinationCount  ;
	this->m_Cost              = other.m_Cost              ;
	this->Visited             = other.Visited             ;
	this->m_CurrDestIndex     = other.m_CurrDestIndex     ;
	this->flightcost          = other.flightcost          ;
    this->flightfrom          = other.flightfrom          ;
    this->flightdest          = other.flightdest          ;
    this->flightnumb          = other.flightnumb          ;
    if( other.m_DestinationCount  > 0 ){
#ifdef DEBUG 
    cout << m_Name << " has " <<  other.m_Destination_Count  << " destinations " << endl ;
#endif // DEBUG
		
		m_Destination = new string[other.m_DestinationCount];
		for( int copyIndex = 0 ; copyIndex < other.m_DestinationCount; copyIndex++ ){
		    m_Destination[ copyIndex ] = other.m_Destination[ copyIndex ]  ;
#ifdef DEBUG 
            cout << m_Destination_Count << " " << m_Destination[copyIndex] << endl;
#endif // DEBUG
        }
    }
    
    //cout << __FILE__  << "  " <<  __LINE__  << endl ;

}



/** \brief function:
 *
 * \param rhs const City&
 * \return City&
 *
 */
City& City::operator=(const City& rhs){                      
#ifdef DEBUG1                                                
    cout << " = operator " << endl;                          
#endif // DEBUG                                              
                                                             
	if (this == &rhs){                                       
        return *this; // handle self assignment              
	}                                                        
	                                                         
    if(  &rhs != nullptr  ){                         ;
	    this->m_Name= rhs.m_Name                            ;
	    this->m_DestinationCount  = rhs.m_DestinationCount  ;
	    this->m_Cost              = rhs.m_Cost              ;
        this->Visited             = rhs.Visited             ;
        this->m_CurrDestIndex     = rhs.m_CurrDestIndex     ;
        this->flightcost          = rhs.flightcost          ;
        this->flightfrom          = rhs.flightfrom          ;
        this->flightdest          = rhs.flightdest          ;
        this->flightnumb          = rhs.flightnumb          ;
        this->m_Index             = rhs.m_Index             ;
        this->m_fromPathIndex     = rhs.m_fromPathIndex     ;
        if( m_DestinationCount > 0 ) {                       
#ifdef DEBUG3                                                
		    cout << "operator=() m_DestinationCount  = " <<  m_DestinationCount << endl ;
#endif                                                       
                                                             
		    this->m_Destination   = new string[m_DestinationCount] ;
			for( int copyIndex = 0 ; copyIndex < m_DestinationCount ; copyIndex++ ){
		         m_Destination[copyIndex]  = rhs.m_Destination[copyIndex]   ;
#ifdef DEBUG		         
    cout << " to " << m_Destination_Count << " " << m_Destination[copyIndex] << endl;
#endif		        
			}
        }                                                    
        }                                                    
	//assignment operator                                    
	return *this;                                            
}                                                            



/** \brief operator:
 *
 * \param rhs const City&
 * \return bool
 *
 */
bool City::operator==(const City& rhs){
    if (this == &rhs){
        return true; // handle self assignment
	}                // should be equal to itself
    if(this->m_Name == rhs.m_Name){
		return true ;
    }
    return false ;
}



/** \brief operator:
 *
 * \param rhs const City&
 * \return bool
 *
 */
bool City::operator!=(const City& rhs){
    if (this == &rhs){
        return false; // handle self assignment
	}                 // should be equal to itself
    
    if(this->m_Name != rhs.m_Name){
		return true ;
    }
    return false ;
}



/** \brief property: Name()
 *
 * \return string&
 *
 */
string City::Name() {
    #ifdef DEBUG3 
      cout << " Name()= " << m_Name << endl ;
    #endif // DEBUG
  
	return m_Name ;
}



/** \brief property: Name(...)
 *
 * \param name string
 * \return void
 *
 */    
void City::Name( string val ){
    try{
        if( val.length() > 0 ) {
        
            if(std::isalpha(val[0])) {
                m_Name =val ;
            } else {
               throw "bad character in name " ;
            }
        
            
            m_Name = val ; 
            flightfrom=(val)     ;
        }
    }catch(string err ){
           cout << err << endl ; 
        
    }

}



/** \brief Clear()
 *
 * \return void
 *
 */   
void City::Clear(){
     if( this->m_Destination != nullptr ) {
        delete m_Destination ;
        m_Destination = nullptr ;
     }
        m_DestinationCount = 0 ;
        m_CurrDestIndex = 0 ;
        head=false ;
        Visited = false ;
}


/**< =================  AddDestination  ================= */

/** \brief function:    AddDestination(...)
 *
 * \param  cityToAdd    - string
 * \return              - bool  
 *
 */
bool City::AddDestination (  string  cityToAdd , float cost ){
    if ( cityToAdd == "" ) {
         return false ;
    }
    if(this->Contains(cityToAdd)){
         return false ;
    }
 #ifdef DEBUG
 
 #endif // DEBUG
	  m_Dest.push(cityToAdd)  ;

   
	if( this->m_Destination == nullptr ){
#ifdef DEBUG2
        cout <<   " Creating destination array for " << this->Name() << endl ;
#endif // DEBUG       
		this->m_Destination = new string[ MAX_DESTINATIONS ] ;
		this->m_Cost        = new float[  MAX_DESTINATIONS ] ;
		
	}
#ifdef DEBUG 
	cout << " City::AddDestination(" <<  '|' << cityToAdd << '|' << ") \n" ;
#endif // DEBUG
	if( m_DestinationCount < MAX_DESTINATIONS){
	    m_Destination[m_DestinationCount] = cityToAdd ;
	    m_Cost[m_DestinationCount] =  cost ;
 #ifdef DEBUG3
        cout << this->Name()
             << " adding destination # "
             << m_DestinationCount << " "
             << cityToAdd  ;
 #endif 
			 m_DestinationCount++ ;
 #ifdef DEBUG2
        cout << "  " <<  m_DestinationCount << endl;
 #endif			 
			 
	} else {
	        std::cout << "Number of cities allowed is " << MAX_DESTINATIONS << std::endl;
	}


    return true ;
}

/**< =================  AddDestination  ================= */


/** \brief function:    HasDestination(...)
 *
 * \param destination string
 * \return bool
 *
 */
bool City::HasDestination( string destination ){
    for( int checkDestination = 0 ; checkDestination < m_DestinationCount ; checkDestination++ ) {
		if( m_Destination[ checkDestination ] == destination ){
 #ifdef DEBUG2 
        std::cout << " HasDestination " << '|' << destination << '|' << std::endl ;
 #endif  
			return true ;
		}
    }
    return false ;
}



/** \brief function:    DestinationCount()
 *
 * \return int
 *
 */
int City::DestinationCount(){
    if ( (this->m_DestinationCount < 0 ) || (this->m_DestinationCount > 100000) ){
        m_DestinationCount = 0 ;
    }
	return m_DestinationCount ;
}



/** \brief function:    GetNextCity(...)
 *
 * \param nextCity string&
 * \param index int&
 * \return bool
 *
 */     
bool City::GetNextCity( string & nextCity , int& index ){
    if( m_CurrDestIndex < 0 || m_CurrDestIndex > 100000 ){
        m_CurrDestIndex = 0 ;
    }
    if( this->m_DestinationCount < 0 || this->m_DestinationCount > 100000 ){
        this->m_DestinationCount = 0 ;
    }
 #ifdef DEBUG 
     std::cout << " GetNextCity() index = " 
               << this->m_CurrDestIndex 
               << " of " 
               << this->m_DestinationCount 
               << std::endl ;
 #endif   
    if ( m_Dest.empty()  ) {
		nextCity =   m_Dest.peek();
		m_Dest.pop() ;
		index = m_CurrDestIndex ;
		m_CurrDestIndex++ ; 
		return true ;
	}	else  { 
	    nextCity = "NO_CITY" ;
		index = -1 ;
		m_CurrDestIndex = 0  ; 
	
	}
	return false ;
}



/** \brief function:    getCost()
 *
 * \param
 * \return float
 *
 */
float City::getCost( int index  ) {
	return m_Cost[ index ]  ;
}



/** \brief function:    GetDestination(...)
 *
 * \param index int
 * \return string&
 *
 */
string& City::GetDestination(int index) {
    return m_Destination[index] ;
	
}



/** \brief function:    GetCurrentDestinationIndex()
 *
 * \return int
 *
 */
int City::GetCurrentDestinationIndex()  {
	int curIndx = m_CurrDestIndex ;
    return curIndx ;
}



/** \brief function:    Display(...)
 * \param cities City*
 * \param cityCount int
 * \return void
 *
 */
void City::Display( City* cities , int cityCount  ){
    for( int index = 0 ; index < m_DestinationCount; index++ ){
		for( int innerloop = 0 ; innerloop < cityCount; innerloop++ )	{
			if( cities[innerloop].Name() == m_Destination[index] ){
				cout << boolalpha  << " to " << m_Destination[index] << " visited = " << cities[innerloop].Visited  << endl ;
			}
		}

    }

 }



/** \brief function:    Display()
 * \param cities City*
 * \param cityCount int
 * \return void
 *
 */
void City::DisplayDestinations(  ){
    for( int index = 0 ; index < m_DestinationCount; index++ ){
        cout <<  m_Destination[index]  << endl ;
    }

 } 



/** \brief function:    Contains(...)
 *
 * \param lookFor string
 * \return bool
 *
 */    
bool City::Contains( string lookFor ){
    if( m_DestinationCount == 0 ){
        return false ;
    }
    for( int index = 0 ; index < m_DestinationCount ; index++ ){
         if( lookFor == m_Destination[index] ){
             return true ;
         }
        
    }
    return false ; 

}
 
 
 
#endif // CITY_CPP

