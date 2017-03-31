/** *************************************************
 *  \file    : city.h                                
 *  \author  : Kelly Black                           
 *  \project : PA03 - Flight Paths                   
 *  \date    : Spring 2017                           
 *                                                   
 *  \description : CITY CLASS HEADER FILE            
 *                 CONTAINS NAMES AND DESTINATIONS   
 *                 AND OTHER INFORMATION             
  ************************************************ */
                                                     
   /**< LIBRARIES */                                 
#include <istream>                                   
#include <string>                                    
#include <iostream>                                  
#include <cstring>                                   
//#include <stack>                                     
#include "linkedstack.h"                             
                                                     
//#define DEBUG3 
                                                     
                                                     
#ifndef CITY_H                                       
#define CITY_H                                       
                                                     
                                                     
 using namespace std;                                
                                                     
const int MAX_DESTINATIONS = 10 ;                    
                                                     
                                                     
class City{                                          
	public:                                          
                                                     
	    /** Default constructor */                   
		City();                                      
                                                     
		/** Default PARAM constructor */             
		City(  string name,   string dest  );        
                                                     
		/** Default destructor */                    
		virtual ~City();                             
                                                     
		/** Copy constructor                         
		 *  \param other Object to copy from
		 */
		City(const City& other);                     
                                                     
		/** Assignment operator                      
		 *  \param other Object to assign from
		 *  \return A reference to this
		 */
		City&   operator=(const City& other);        
                                                     
        /** \brief operator == Equal                 
         *
         * \param rhs const City&
         * \return bool
         *
         */
		bool    operator==(const City& rhs);         
                                                     
        /** \brief operator != Not Equal             
         *
         * \param rhs const City&
         * \return bool
         *
         */
		bool    operator!=(const City& rhs);         
                                                     
		/** \brief Name                              
		 * \return The current value of this objects Name
		 */
		string  Name();                              
                                                     
		/** \brief Name                              
		 * \param val New value to set
		 */
	//	void    Name(const char* val);               
                                                     
        /** \brief Name                              
         *
         * \param val string
         * \return void
         *
         */
        void    Name( string  val );                 
                                                     
        /** \brief Clear                             
         *
         * \return void
         *
         */                                   
        void    Clear();                             
                                                     
        /** \brief                                   
         *
         * \param lookFor string
         * \return bool
         *
         */                                            
        bool    Contains( string lookFor );          
                                                     
                                                     
        /** \brief CountLines                        
         *
         * \param filename const char*
         * \return int
         *
         */
        int     CountLines(const char* filename);    
                                                     
                                                     
        /** \brief                                   
         *
         * \param index int
         * \return string&
         *
         */                                            
		string& GetDestination(int index) ;          
                                                     
                                                     
        /** \brief                                   
         *
         * \param 
         * \param 
         * \return 
         *
         */                                                     
        bool  AddDestination ( string destination, float cost  ) ;
                                                     
                                                     
        /** \brief                                   
         *
         * \param 
         * \param 
         * \return 
         *
         */                                                     
        bool  HasDestination ( string destination ) ;
                                                     
        /** \brief                                   
         *
         * \param 
         * \return float
         *
         */                                            
		float   getCost( int index );                          
                                                     
        /** \brief                                   
         *
         * \param cost float
         * \return void
         *
         */                                            
		void   setCost(int index , float cost){ m_Cost[ index ] = cost ; }
                                                     
		/** Access Visited                           
		 * \return The current value of Visited
		 */
		bool    Visited ;                            
                                                     
        /** \brief                                   
         *
         * \return int
         *
         */                                   
        int     DestinationCount();/**<  */          
                                                     
                                                     
        /** \brief                                   
     *
     * \param 
     * \return void
     *
     */                        
        void    DisplayDestinations(  )  ;           
                                                     
        /** \brief                                   
         *
         * \return int
         *
         */                                   
        int    GetCurrentDestinationIndex() ;/**<  */
                                                     
                                                     
        /** \brief  \call GetNextCity(next)          
         *
         * \param next string& - Result passed by reference
         * \return bool - returns true if successful
         */
        bool GetNextCity( string & next,int& index );
                                                     
                                                     
                                                     
                                                     
        /** \brief                                   
         *
         * \param val int
         * \return void
         *
         */                                            
        void  SetIndex( int val ){ m_Index = val ; } 
                                                     
                                                     
                                                     
        /** \brief                                   
         *
         * \return int
         *
         */                                   
        int     GetIndex() { return m_Index ; }      
                                                     
                                                     
                                                     
        /** \brief                                   
         *
         * \param val int
         * \return void
         *
         */                                            
        void    SetFromPathIndex(int val ) { m_fromPathIndex = val ; }
                                                     
                                                     
                                                     
        /** \brief                                   
         *
         * \return int
         *
         */                                   
        int     GetFromPathIndex(){ return m_fromPathIndex ; }
                                                     
                                                     
        /** \brief                                   
         *
         * \param cities City*
         * \param cityCount int
         * \return void
         *
         */
        void    Display( City* cities , int cityCount  );
                                                     
        string flightnumb ;/**<  */                  
                                                     
        string flightdest ;/**<  */                  
                                                     
        string flightfrom ;/**<  */                  
                                                     
        string flightcost ;/**<  */                  
	                                                 
	    bool   head       ;/**<  */                  
	protected:                                       
                                                     
                                                     
	private:                                         
        int m_Index           ; /**<  */             
        int m_fromPathIndex   ;                      
        int m_DestinationCount;/**<  */              
		int m_CurrDestIndex   ;/**<  */              
		                                             
        LinkedStack<string> m_Dest ;                 
                                                     
        string  m_Filename    ;/**<  */              
	    string  s_Name        ;                      
		string* m_Destination ; //!< Member variable "Destination"
		string  m_Name        ;                      
        float*  m_Cost        ;/**<  */              
                                                     
                                                     
};                                                   
                                                     
#endif // CITY_H                                     
                                                     
