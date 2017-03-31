/** ***********************************************************  
 *  \file    : flightmapclass.cpp
 *  \author  : Kelly Black
 *  \project : PA03 - Flight Paths
 *  \date    : Spring 2017
 *
 *  \description : FLIGHT MAP CLASS IMPLEMENTATION FILE
 *                 CONTAINS CITIES, FLIGHTS, REQUESTS 
 *                 AND OTHER INFORMATION
  ************************************************************* */




#include "flightmapclass.h"
#include <string.h> 
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "linkedstack.h"
#include "city.h"
#include "istream"
#include "string"
#include <cstdlib>



#ifndef LINKEDSTACK
#define LINKEDSTACK
#include "FileWrite.cpp"

#define DEBUG4 
using namespace std;

/**< Global Variables  /
 char   CITY_FILE[]    = "cityFile.txt"     ;
 char   FLIGHTS_FILE[] = "flightFile.txt"   ;
 char   REQUEST_FILE[] = "requestFile.txt"  ;
 char   LOG_FILE[]     = "logFile.txt"      ;
 
                */
FlightMapClass::FlightMapClass(  const char* CITYFILE , const  char*  FLIGHTFILE, const  char*  REQUESTFILE){
    //ctor
    m_flightsFile = new char[strlen(FLIGHTFILE)]  ;
    m_citiesFile  = new char[strlen(CITYFILE)]    ;
    m_requestsFile= new char[strlen(REQUESTFILE)] ;
    strcpy( m_flightsFile , FLIGHTFILE  ) ;
    strcpy( m_citiesFile  , CITYFILE    ) ;
    strcpy( m_requestsFile, REQUESTFILE ) ;
    m_CityCount    = CountLines( m_citiesFile   ) ;
    m_FlightCount  = CountLines( m_flightsFile  ) ;
    m_RequestCount = CountLines( m_requestsFile ) ;
    cout << " cities " 
         << m_CityCount 
         << " flights " 
         <<  m_FlightCount  
         <<  " requests " 
         << m_RequestCount << endl ; 
    m_cities   = new City[m_CityCount]    ;
    m_flights  = new City[m_FlightCount]  ;
    m_requests = new City[m_RequestCount] ;
    m_cities   = GetCities()    ;
    m_flights  = GetFlights()   ;
    m_requests = GetRequests()  ;
    
    m_CurrentIndex = 0 ;
    m_Visited  = new bool[m_CityCount] ;
    for( int index = 0 ; index < m_CityCount ; index++ ) {
       m_Visited[index] = false ;
        
    } 
    
    

    
    
    
}

FlightMapClass::~FlightMapClass()
{
    //dtor
}

FlightMapClass::FlightMapClass(const FlightMapClass& other)
{
    //copy ctor
}

FlightMapClass& FlightMapClass::operator=(const FlightMapClass& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

City*  FlightMapClass::GetFlights(  ){
    std::cout << "Opening file " << m_flightsFile << "  count = " << m_FlightCount << std::endl ;
    /**< Local Variables  */
	std::fstream fileStreamReader ;
	fileStreamReader.open( m_flightsFile , std::ios::in );
	std::string dummy ="";
	int track = 0 ;
	int firstDigit  = 0 ; 
	int firstComma = 0 ;
	//int firstWS = 0 ;
	City* home = m_flights ;

	try{
		/**< Loop to read in data */
		while(!(fileStreamReader.eof()) && (track < m_FlightCount -2 ) ){
            std::getline( fileStreamReader , dummy , '\n' ) ;
           // cout << "....5....0....5....0....5....0...5....0....5....0....5....0....5\n"  ;
          //  cout <<  dummy  << endl ;
            firstDigit= FirstDigitPosition( dummy , firstDigit )    ;
            firstComma =FirstCommaPosition( dummy , firstComma )     ;
          //  cout << " comma = " << firstComma << "  digit= " << firstDigit << endl ;
			std::size_t found = dummy.find (',',  0) ;
            if( found == 0 || (found == std::string::npos) ){
				goto getthehellout ;
            }
            m_flights->flightfrom = dummy.substr(0 , firstComma);
            m_flights->Name(m_flights->flightfrom);
            
            #ifdef DEBUG3
               cout << " FLIGHTFROM read in FROM FLIGHTS FILE  |" << m_flights->flightfrom << '|' << endl ;
               DoPause(" Is name ok? " )      ;
            #endif // DEBUG2
         
			m_flights->flightdest = dummy.substr( firstComma+1  , firstDigit - (firstComma+1) );
            m_flights->flightnumb = dummy.substr( firstDigit , 3 ) ;
            m_flights->flightcost = dummy.substr( firstDigit + 3 ) ;
         

            m_flights->head = false ;
            if(fileStreamReader.peek() == fileStreamReader.eof()){
				goto getthehellout;
            }
            

            m_flights++;
		}

	} catch (int err) {

		std::cout << "Error # " << err << std::endl ;

	}
getthehellout:
	m_flights = home ;

	fileStreamReader.close() ;
    return m_flights ;

}

float FlightMapClass::GetCostFromFlight( string fflightfrom , string fflightto ) {
    //std::cout << "Opening file " << fileName << "  count = " << flightCount << std::endl ;
    /**< Local Variables  */
	std::fstream fileStreamReader ;
	fileStreamReader.open( m_flightsFile , std::ios::in );
	std::string dummy = "" ;
	int track       = 0 ;
	int firstDigit  = 0 ;
	int firstComma  = 0 ;
	float ret = 0.00 ; 
	//int firstWS = 0 ;
	City* home = m_flights ;

	try{
		/**< Loop to read in data */
		while(!(fileStreamReader.eof()) && (track < m_FlightCount -2 ) ){
            std::getline( fileStreamReader , dummy , '\n' ) ;
            /**< get key positions for parsing */
            firstDigit = FirstDigitPosition( dummy , firstDigit )    ;
            firstComma = FirstCommaPosition( dummy , firstComma )    ;
            
			std::size_t found = dummy.find (',',  0) ;
            if( found == 0 || (found == std::string::npos) ){
				goto getthehellout ;
            }
            m_flights->flightfrom =  dummy.substr(0 , firstComma )  ;
            m_flights->flightfrom =  Trim( m_flights->flightfrom )  ;
            m_flights->Name( m_flights->flightfrom ) ;

			m_flights->flightdest = dummy.substr( firstComma + 1   , firstDigit - ( firstComma + 1 ) );
			m_flights->flightdest = Trim( m_flights->flightdest )  ;
           
            m_flights->flightnumb = dummy.substr( firstDigit , 3 ) ;
            m_flights->flightcost = dummy.substr( firstDigit + 3 ) ;
            
            if( ( m_flights->flightfrom == fflightfrom ) && ( m_flights->flightdest == fflightto ) ){
                float tcost       =  atof( m_flights->flightcost.c_str() ) ;
                ret = tcost ;
                 
            }
            
            m_flights->head = false ;
            if(fileStreamReader.peek() == fileStreamReader.eof()){
				goto getthehellout;
            }
            
            /**< move to next flight */
            m_flights++;
		}

	} catch (int err) {

		std::cout << "Error # " << err << std::endl ;

	}
getthehellout:
	m_flights = home ;

	fileStreamReader.close() ;
    return ret ;




}


void  FlightMapClass::GetFlights( const char*  fileName , City& fromCity , int flightCount  ){
    //std::cout << "Opening file " << fileName << "  count = " << flightCount << std::endl ;
    /**< Local Variables  */
	std::fstream fileStreamReader ;
	fileStreamReader.open( fileName , std::ios::in );
	std::string dummy = "" ;
	int track       = 0 ;
	int firstDigit  = 0 ;
	int firstComma  = 0 ;
	//int firstWS = 0 ;
	City* home = m_flights ;

	try{
		/**< Loop to read in data */
		while(!(fileStreamReader.eof()) && (track < flightCount -2 ) ){
            std::getline( fileStreamReader , dummy , '\n' ) ;
            /**< get key positions for parsing */
            firstDigit = FirstDigitPosition( dummy , firstDigit )    ;
            firstComma = FirstCommaPosition( dummy , firstComma )    ;
            
			std::size_t found = dummy.find (',',  0) ;
            if( found == 0 || (found == std::string::npos) ){
				goto getthehellout ;
            }
            m_flights->flightfrom =  dummy.substr(0 , firstComma )  ;
            m_flights->flightfrom =  Trim( m_flights->flightfrom )  ;
            m_flights->Name( m_flights->flightfrom ) ;

			m_flights->flightdest = dummy.substr( firstComma + 1   , firstDigit - ( firstComma + 1 ) );
			m_flights->flightdest = Trim( m_flights->flightdest )  ;
           
            m_flights->flightnumb = dummy.substr( firstDigit , 3 ) ;
            m_flights->flightcost = dummy.substr( firstDigit + 3 ) ;
            
            if( m_flights->flightfrom == fromCity.Name()  ){
                float tcost       =  atof( m_flights->flightcost.c_str() ) ;
                fromCity.AddDestination( m_flights->flightdest , tcost   ) ;
                //cout << " cost: " << tcost << endl ;
            }
            
            m_flights->head = false ;
            if(fileStreamReader.peek() == fileStreamReader.eof()){
				goto getthehellout;
            }
            
            /**< move to next flight */
            m_flights++;
		}

	} catch (int err) {

		std::cout << "Error # " << err << std::endl ;

	}
getthehellout:
	m_flights = home ;

	fileStreamReader.close() ;
    return  ;

}

City* FlightMapClass::GetRequests(){
    int count = CountLines(m_requestsFile) ;
std::fstream fileStreamReader ;
#ifdef DEBUG3
    std::cout << "GetRequests(" << m_requestsFile << " )" << std::endl ;
#endif // DEBUG
	fileStreamReader.open( m_requestsFile , std::ios::in );
	std::string dummy = "" ;
	m_requests = new City[ count ] ;
	City* home = m_requests ;
	try{
		while( !fileStreamReader.eof() ){
                //@ READ EACH LINE INTO dummy VARIABLE TO BE PARSED
                std::getline( fileStreamReader , dummy , '\n' ) ;
				//@ FIND FIRST COMMA
				std::size_t positionOfComma = 0  ;
				for( size_t pos = 0 ; pos < dummy.length() ; pos++ ){
                    if(dummy.at(pos) == ',' ) {
                        positionOfComma = pos ;
                    }
				}
	            //@ PARSE findFrom
                m_requests->flightfrom = dummy.substr( 0 , positionOfComma );
	            m_requests->flightdest = dummy.substr( positionOfComma +2 , dummy.length() - ( positionOfComma + 1 ) );
#ifdef DEBUG3
    std::cout << "getFlightPaths From: " << '|' << m_requests->flightfrom << '|' << std::endl ;
    std::cout << "getFlightPaths Dest: " << '|' << m_requests->flightdest << '|' << std::endl ;
#endif // DEBUG
	            m_requests->Visited = false ;
	            //@===============================================
	            m_requests++;
		}	// end while
	} catch (int err) {
		std::cout << "Error # " << err << std::endl ;
	}
    m_requests = home ;
    return m_requests ;

}


/** \brief function:  ReadCities
 *
 * \param fileToRead const char*
 * \param m_cities City*
 * \param max_cities int
 * \return City*
 *
 */
City* FlightMapClass::GetCities(  ){

    cout << " ReadCities(" << m_citiesFile << " ) "
		 << endl      ;
	fstream reader    ;
	string  dummy     ;
	char**  readin    = new char*[m_CityCount] ;
	int     index     = 0   ;
	int     charnum   = 0   ;
	char    ch        = ' ' ;

	reader.open(  m_citiesFile  , std::ios::in  ) ;
	if( reader.good() && index < m_CityCount ) {
		std::cout <<"File Opened "
		          << m_citiesFile
		          << " \n"       ;
		while( ( reader.good() == true ) && ( index < m_CityCount -1 ) ){
			// read in character by character 
			// until we hit the new line char '\n'
			// so we can read white space ex: Los Angeles
			charnum       = 0                  ;
			readin[index] = new char[35]       ;
			ch            = reader.get()       ;
			/* <<<<<<<<<< while <<<<<<<<<<<<< */
			while ( ch   != '\n'  )	           {
#ifdef DEBUG                                    
                std::cout << " "  << ch        ;
#endif // DEBUG
				readin[index][charnum]= ch     ;
				ch        = reader.get()       ;
				charnum++                      ;
		                                       }
		    /* >>>>>>>>>> loop >>>>>>>>>>>>>> */ 
		    readin[ index ][ charnum ]= '\0'   ;
		    #ifdef DEBUG
		          cout << " straight from file " << '|' <<  readin[index] << '|' << endl ;
		          DoPause(" is string ok? " )  ;
		    #endif // DEBUG2
		    string fixString =readin[ index ]  ;
		   // fixString = Trim( fixString )      ;
            m_cities[index].Name( fixString )    ;
		    m_cities[index].flightfrom= fixString;
		    m_cities[index].SetIndex(index)      ;
		    index++                            ;
		    
	    }

	} else {
		std::cout <<"File Not Opened " << m_citiesFile << " \n" ;
	}
	if(reader){
		reader.close();
	}

    cout << " File closed " << endl ;

   return m_cities ;
}



/** \brief function: GetCityIndex(...)
 *
 * \param cityName    - const string   -
 * \param m_cities      - City*          -
 * \param cityCount   - int            -
 * \return            - int            -
 *
 */      
int FlightMapClass::GetCityIndex( const string cityName  ){
     string fixCityName = cityName ;
     fixCityName = Trim( fixCityName ) ;
 #ifdef DEBUG3 
     cout << __FILE__  << "  " <<  __LINE__  << endl ;
     cout << '|' << cityName << '|' << " fixed is " << '|' << fixCityName << '|' << endl ;
 #endif // DEBUG2
    
     for( int i = 0 ; i < m_CityCount ; i++){
        string fixToo = m_cities[i].Name() ;
        fixToo = Trim(fixToo) ;
        
 #ifdef DEBUG3 
     cout << '|' << m_cities[i].Name() << '|' << " fixed is " << '|' << fixToo << '|' << endl ;
 #endif // DEBUG2        
        
        if ( fixToo == fixCityName )  {
             return i ;
        }   
     }
     DoPause("GetCityIndex(" + cityName + ")  Didn't find an index!!!" )  ;
     return -1 ;
}




/** \brief function: HasRoutes(...) 
 *                                - 
 * \param cityName      - string  - 
 * \param m_cities        - City*   - 
 * \param cityCount     - int     - 
 * \return              - int     - 
 *                                - 
 */
int   FlightMapClass::HasRoutes(string cityName  ){
#ifdef DEBUG3  
    std::cout << " HasRoutes() " << std::endl ;
#endif // DEBUG
	int routeCount = 0 ;
	int cityIndex = GetCityIndex( cityName );
    for( int checkDestination = 0 ; checkDestination < m_cities[ cityIndex ].DestinationCount() ; checkDestination++ ) {
        string dest = GetDestination(cityIndex , checkDestination );
        int destCityIndex = GetCityIndex( dest )   ;
        if(m_Visited[ destCityIndex ] == false ){
            routeCount++ ;
            std::cout << " HasRoute( " << routeCount <<  ") to " << dest << std::endl ;
        } else {
            cout << " Already visited " << m_cities[ destCityIndex ].flightfrom << endl ;
        }
    }
    return routeCount ;
}


/** \brief function: FlightSearch(...)
 *
 * \param  originCity      - const string  -  Find flight from here
 * \param  destinationCity - const string  -  Find flight to here 
 * \param  m_cities          - City*         -  City array
 * \param  flights         - City*         -  Flights array
 * \param  flightCount     - int           -  #of flights in array
 * \param  bVisited        - bool*         -  Array of bool - flags if city has been used
 * \param  cityCount       - int           -  #of m_cities in array
 * \return                 - bool          -  returns true if a flight path was found
 *
 */          
bool FlightMapClass::FlightSearch( const string originCity   ,  const string destinationCity   ){
	cout << " searchS( " << originCity  << " ," << destinationCity  <<  " ) " << endl;
    // ============================== LOG =========================================
    FW.FileWrite( (string)"-------------------------------------------------------------" , true , false  ) ;
    FW.FileWrite( " GetFlightPath( " , false , false ) ;
    FW.FileWrite( originCity , false , false ) ;
    FW.FileWrite( " , " , false , false  ) ;
    FW.FileWrite( destinationCity , false ,false  ) ;
    FW.FileWrite( " ) " , true , false  ) ;
    // ============================================================================
/**<  VARIABLES =================================*/

#ifdef  LINKEDSTACK
    LinkedStack<string> cityStack ;
    LinkedStack<string> destStack ;
#else 
    stack<string> cityStack ;
    stack<string> destStack ;
#endif // LINKED_STACK
    /**< Get key indexes */                                                                       
    int topCityIndex     =  this->GetCityIndex( originCity.c_str() )      ;
    int nextCityIndex    =  0 ;                                            
    int destinationIndex =  this->GetCityIndex( destinationCity.c_str() ) ;
    int originCityIndex  =  this->GetCityIndex( originCity.c_str() )      ;
    int absolutecount    =  0 ;                                            
    /**< Get names of cities */                                                                       
    string topCityName         = m_cities[ topCityIndex     ].Name()     ; 
    string nextCityName                                                  ; 
    string cityOriginName      = m_cities[ topCityIndex     ].flightfrom ; 
    string finalDestinationName= m_cities[ destinationIndex ].Name()     ; 
    /**< clear all marks  */                                            
    this->UnVisitAll( ) ;
    /**< push origin on to both stacks */
    cityStack.push( originCity ) ;              
    destStack.push( originCity ) ;              
    /**< Mark origin city */
    m_Visited[ originCityIndex  ]         = true ;
    m_cities[   originCityIndex ].Visited = true ;
    m_cities[   originCityIndex ].head    = true ;
    m_cities[   originCityIndex ].SetFromPathIndex( originCityIndex ) ; 
                                                                      
/**< Loop until the stack is empty or we have found our destination */
 //==================================    
// Try flight to each unvisited city     
//==================================     
// CHECK CURRENT CITY FOR                
//  MORE DESTINATIONS                    
// IF A DESTINATION EXISTS               
//  GET THE NAME OF THE CITY             
// IF THE CITY HAS NOT BEEN              
// MARKED AS VISITED THEN                
// PUT IT ON A STACK                     
// IF THE DESTINATION CITY HAS           
// ROUTES THEN PUT IT ON THE ACTIVE      
// CITY STACK OTHERWISE PUT IT ON THE    
// DESTINATION STACK. IF THE ACTIVE      
// CITY STACK RUNS OUT OF CITIES         
// TO VISIT THEN THE DESTINATION STACK   
// MOVES ALL ITS CITIES TO THE LIVE STACK
// IT IS BASICALLY A DEPTH FIRST SEARCH  
//________________________________ */    
  int nn = 0 ;
 
    while ( ( cityStack.empty( )== false ) && ( cityStack.contains(finalDestinationName)== false ) )  {    
        nn=0 ;
        absolutecount++ ;
        cout << " ((((((((((((((((((((((((((((" << absolutecount << ")))))))))))))))))))))))" << endl ; 
#ifdef DEBUG 
    cout << __FILE__  << "  " <<  __LINE__  << endl ;  
#endif    
        /**< Get city on top of stack */
        topCityName = cityStack.peek() ;
        topCityName = Trim( topCityName ) ;
        /**< Get city's index */
        topCityIndex = GetCityIndex( topCityName.c_str()  ) ; 
        /**< mark as visited */
        this->m_Visited[ topCityIndex ]         = true ;
        this->m_cities[  topCityIndex ].Visited = true ;
        /**< populate city with connecting flights */
        cout << " Visited= " << this->m_Visited[ topCityIndex ]  << endl ; 
        GetFlights(this->flightFile,  m_cities[  topCityIndex ]   , m_FlightCount ) ;   
        // ============================== LOG =========================================
        FW.FileWrite(  m_cities[ topCityIndex ].Name() + " has "  , false , false ) ;
        FW.FileWrite(  m_cities[ topCityIndex ].DestinationCount(), false , false ) ;
        FW.FileWrite( " destinations. ", true, false );
        // ============================================================================
#ifdef DEBUG5 
        cout << m_cities[ topCityIndex ].Name() 
             << " has " << m_cities[ topCityIndex ].DestinationCount() 
             <<  " destinations " << endl ;
#endif
        /**< get next city from live stack */
        cityStack.pop() ;
        if( cityStack.empty() == true ) {
#ifdef DEBUG 
            cout << " cityStack is empty " << endl ;
#endif // DEBUG
             /**< move destination stack to live stack */   
             while(destStack.empty() == false ) {
#ifdef DEBUG 
                 cout << " push onto cityStack " << destStack.peek() << endl ; 
#endif // DEBUG
                 cityStack.push( destStack.peek() ) ;
                 destStack.pop() ;
             }
            
        }        
        
          
        while ( (nn < m_cities[ topCityIndex ].DestinationCount())   )  {
#ifdef DEBUG 
            cout << " nn= " << nn << endl ;  
#endif // DEBUG
            /**< Get each destination city */
            nextCityName  = Trim( m_cities[ topCityIndex ].GetDestination ( nn ) ) ;
            nextCityIndex = GetCityIndex( nextCityName.c_str() ) ;
//#ifdef DEBUG5             
            cout << " possible route exists from |" << topCityName << "| to |" << nextCityName << "|" <<  endl ; 
//#endif
            // Does the stack already contain next city?
            if(  cityStack.contains( nextCityName )== false ) {
                
                if( m_Visited[ nextCityIndex ] == false ) { 
                    m_cities[ nextCityIndex ].SetFromPathIndex( topCityIndex ) ;
//#ifdef DEBUG5 
                    cout << " Push -> |" << nextCityName   << "|" << endl ;
//#endif // DEBUG
                   
                    int hrts = HasRoutes( nextCityName)  ;

//#ifdef DEBUG5 
                    cout << " routes = " << hrts << endl ; 
//#endif // DEBUG                  
                    FW.FileWrite( " Has " , false , false  ) ;
                    FW.FileWrite( hrts    , false , false  ) ;
                    FW.FileWrite( " routes ", true , false  ) ; 
                    /**< If destination has routes push onto cityStack otherwise put it in the destStack  */
                    if( hrts > 0 ) {
                        cityStack.push( nextCityName ) ;
                        cout << nextCityName << " has " << hrts << " routes. " << endl ;
                   
                    }  else {
                        if( !destStack.contains(nextCityName) ){
                             cout << nextCityName << " has " << hrts << " routes" ;
                             cout << " pushing on to destination stack. " << endl ;
                            destStack.push( nextCityName ) ;
                        }
                    }
                    /**< If we put final destination on destStack move it to cityStack */
                    if( destStack.contains(finalDestinationName) ){
                        cityStack.push(destStack.peek() ) ;
                        destStack.pop() ;
                    }                     
                    /**< mark city as visited */
                    m_Visited[ nextCityIndex ] = true ;
                    
                    FW.FileWrite("Push( " + nextCityName + " )" , true , false );
                    /**< Have we found the final destination ? */
                    if( cityStack.contains(finalDestinationName) ){
                        /**< make inner loop terminate  */
                        
                        FW.FileWrite("Found Destination (" + nextCityName + ")",true,false );
                        /**< display flight path  */
                        ShowResult( nextCityIndex , nn , destinationIndex  ) ;
                        nn = m_cities[ topCityIndex ].DestinationCount()  ;
                        return true;
                        
                    } else {
                    
                    }
                    
                    
                } else {
                  FW.FileWrite( nextCityName + " has been visited.",true,false ) ;
                }
            }
                nn++ ;
        }  // end inner while loop 

    }   // end while loop 
    // no flight path found
    return false ;

}  // ==========================================================================================
 // ============================================================================================
/** \brief function: CountLines
 *
 * \param filename const char*
 * \return int
 *
 */
int   FlightMapClass::CountLines(const char* filename){
	// count the number of lines in the file called filename
 #ifdef DEBUG 
    std::cout << " Counting Lines " << endl ;
	std::cout << " Opening file " << filename << std::endl ;
 #endif // DEBUG
	
	FILE *fp = fopen(filename,"r");
	int ch=0;  	int lines=0;

	if (fp == NULL)	{
		return 0;
	}

	lines++;
	while ((ch = fgetc(fp)) != EOF)	{
		if (ch == '\n'){
			lines++;
		}
	}
	fclose(fp);
	return lines;
}



/** \brief function: DoPause(...)
 *
 * \param msg string
 * \return bool
 *
 */    
bool   FlightMapClass::DoPause( string msg ) {
    string ret = "Y" ;
    cout << msg << endl ;
    cout << "Press a key and hit enter to continue ... " << endl ;
    cin >> ret ;
    return true ;
}



/** \brief function: FirstCommaPosition(...)
 *                                      
 * \param dataLine   - const string&  - 
 * \param punctPos   - int            - 
 * \return           - int            - 
 *                                      
 */     
int   FlightMapClass::FirstCommaPosition(const string & dataLine , int punctPos  )          {
      int sLng = dataLine.length() ;
      const char* datach = dataLine.c_str() ;
      for( int eachChar = 0 ; eachChar < sLng ; eachChar++ ){
          if ( ispunct( datach[eachChar] ) )  {
               punctPos = eachChar ;
               goto bailout;
          }
          
      }
bailout:
      return punctPos  ;
}



/** \brief function: FirstDigitPosition(...)
 *
 * \param dataLine   - const string&
 * \param digPos     - int
 * \return           - int
 *
 */     
int   FlightMapClass::FirstDigitPosition(const string & dataLine , int  digPos )          {
      int sLng = dataLine.length() ;
      const char* datach = dataLine.c_str() ;
      for( int eachChar = 0 ; eachChar < sLng ; eachChar++ ){
          if ( isdigit(datach[eachChar] ) )  {
               digPos = eachChar ;
               goto bailout;
          }
          
      }
bailout:
      return digPos  ;
}



/** \brief function: FirstWhitePosition(...)
 *
 * \param dataLine   - const string&
 * \param pos        - int
 * \param digPos     - int
 * \return           - int
 *
 */      
int   FlightMapClass::FirstWhitePosition(const string & dataLine ,int pos ,  int  digPos )          {
      int sLng = dataLine.length() ;
      const char* datach = dataLine.c_str() ;
      for( int eachChar = pos ; eachChar < sLng ; eachChar++ ){
          if ( isspace(datach[eachChar] ) )  {
               digPos = eachChar ;
               goto bailout;
          }
          
      }
bailout:
      return digPos  ;
}



/**  @ function: rTrim()
 *  @ Desc: right trim - removes trailing spaces
 *  @ param: [IN][OUT] str2cl - String to clean
 *  @
 *  @
 *  *
 *  */
string FlightMapClass::rTrim( string & str2cl ) {
	int nx = -1 ;
	size_t strlIn = str2cl.length() ;
		while( (str2cl[ strlIn + nx ] == ' ') || ( str2cl[ strlIn + nx ] == '\t' )  ){
#ifdef DEBUG2 
    
    cout << '|' << str2cl << '|' <<  " length = " << strlIn << endl ;
#endif // DEBUG2
			str2cl.pop_back() ;
			str2cl.shrink_to_fit() ;
			nx-- ;
		}
		
#ifdef DEBUG2 
    cout << '|' << str2cl << '|' <<  " length = " << str2cl.length() << endl ;
#endif // DEBUG2
	return str2cl ;
}



/** \brief 
 *
 * \param str2cl string&
 * \return string
 *
 */    
string FlightMapClass::lTrim( string & str2cl){

    size_t strlIn = str2cl.length() ;

    size_t nx = 0 ;
    if( str2cl[0] != '\0' ){
        while(( str2cl[0] == ' ') || ( str2cl[0] == ',') || ( str2cl[0] =='\t'  ) ){
            nx++;
#ifdef DEBUG2 
           cout << " str2cl.substr( 1, str2cl.length() -" << nx << " ) " << '|' << str2cl.substr( 1, strlIn - nx )  << '|' << endl ;
#endif // DEBUG2 
            str2cl = str2cl.substr( 1, strlIn  )  ; 
            str2cl.shrink_to_fit() ;
#ifdef DEBUG2 
           cout << "left fixed " << '|' << str2cl << '|' << endl ;
#endif // DEBUG2            
            
 
        }
    }
    
#ifdef DEBUG2 
    if( strlIn  !=  str2cl.length() ){
        cout << "string was changed" <<  endl ;
    }
#endif // DEBUG3
   
    return str2cl ;
}



/** \brief 
 *
 * \param str2cl string&
 * \return string
 *
 */    
string  FlightMapClass::Trim( string & str2cl){
    str2cl = rTrim(str2cl) ;
    str2cl = lTrim(str2cl) ;
    str2cl = rTrim(str2cl) ;
    return str2cl ;
}



/** \brief function: ShowResult(...)
 *
 * \param cityIndex   - int   - index of the destination 
 * \param originIndex - int   - index of the origin city 
 * \param m_cities      - City* - array of all cities      
 * \return cost       - float - total cost of all flights
 *
 */      
float FlightMapClass::ShowResult(int cityIndex,int localindex , int originIndex   ) {
      float cost = 0.0 ;
      LinkedStack<int> Visited ;
       Visited.push(cityIndex) ;
       Visited.push(originIndex) ;
        cout << "===============================================================================" << endl ;
        cout << " Found destination " << m_cities[originIndex].Name()  << endl ;    
        while(  m_cities[ cityIndex ].GetFromPathIndex() != originIndex && (m_cities[ cityIndex ].GetFromPathIndex() != m_cities[ cityIndex ].GetIndex() )) {
            string ffrom = m_cities[ m_cities[ cityIndex ].GetFromPathIndex() ].Name() ;
            string ffto  = m_cities[ cityIndex ].Name()  ;
            cout << "Flight  " <<  ffrom << " to  " <<  ffto << endl ; 
            FW.FileWrite("Flight  " + m_cities[ m_cities[ cityIndex ].GetFromPathIndex() ].Name()  +  " to  "  + m_cities[ cityIndex ].Name(), true , false  )  ;
            
            cout << " Cost: " << GetCostFromFlight( ffrom , ffto )  <<  endl ;
             
            cost += GetCostFromFlight( ffrom , ffto ) ;

            cityIndex = m_cities[ cityIndex ].GetFromPathIndex()  ;

            if( Visited.contains( cityIndex )){
                //    cout << " visited contained cityindex " << endl ;
                goto exitwhileloop ;
            }
            Visited.push(cityIndex) ;
            
        }
exitwhileloop:
        cout << "===============================================================================" << endl ;
        FW.FileWrite("Flight path " + m_cities[ cityIndex ].Name() +  " to  "  + m_cities[ originIndex ].Name() ,  true , false  )  ;
        cout << " Flight path " << m_cities[ cityIndex ].Name() << " to  " << m_cities[ originIndex ].Name()  << endl ;  
        cout << " Total cost "  << cost << endl ; 
        cout << "===============================================================================" << endl ;
                
        return cost ;
}



/** \brief function: UnVisitAll
 *
 * \param Cities City*
 * \param CityCount int
 * \return 
 *
 */
void FlightMapClass::UnVisitAll(   ){
  // 
    for( int index = 0 ; index < m_CityCount ; index++ ){
 #ifdef DEBUG 
        cout << " UnvisitAll() " << endl;
        cout << " Visited " <<   m_cities[index].Name() << " " <<  m_Visited[index] << endl ;
 #endif // DEBUG    
         m_cities[index].flightfrom  =  m_cities[index].Name()  ;
         m_Visited[index]=false ;
         m_cities[index].Visited = false ;
        
    }
    return ;
}



/**< =============================================================== */
    /** \brief : Loop to process Requests
 *
 * \param m_requests City*
 * \param m_RequestCount int
 * \param city City*
 * \param cityCount int
 * \param ivisited bool*
 * \return City*
 *
 */        
bool FlightMapClass::ProcessRequests(  ){
    FW.FileWrite("Process Requests " ,true,false ) ;
    cout << " # of requests " << m_RequestCount  << endl ;
    
    for( int reqIndex = 0 ; reqIndex < m_RequestCount ; reqIndex++ ){
        /**< Get City names from request file  */
		string OrIgIn = Trim(m_requests[reqIndex].flightfrom)  ;
        string DeStIn = Trim(m_requests[reqIndex].flightdest)  ;
        if( OrIgIn == "NO_CITY"){
                DoPause("NoCity");
            return false ;
        }
        cout << "Check Flight From |" << OrIgIn << "| to |" << DeStIn << "| line " << __LINE__ << endl ; 
        
        FW.FileWrite( "Check Flight From " + OrIgIn + " to " + DeStIn, true , false  ) ;
        int ORIG = GetCityIndex( OrIgIn  );
        int DEST = GetCityIndex( DeStIn  );

        /**< Find City from name  */                      
            UnVisitAll(  )  ;
                                                          
            FW.FileWrite( " city index " , false , false )  ;
            FW.FileWrite( ORIG , true, false  )  ;           
            FW.FileWrite( " dest index " , false , false )  ;
            FW.FileWrite( DEST , true , false ) ;                           
            
            
#ifdef DOPAUSE
            DoPause( " Calling GetFlightPath( from , to ) ") ;
#endif // DOPAUSE 
          cout << " ===============================================================\n" ;
			GetFlights(m_flightsFile, m_cities[ORIG] , m_FlightCount  )  ;
			bool result = FlightSearch( m_cities[ ORIG ].Name() , m_cities[ DEST ].Name()  ) ;
            
            if(result){
                FW.FileWrite( " Success  " , true , false  ) ;
                FW.FileWrite("=================================================================",true,false ) ;
                cout << " ===============================================================\n" ;
                
            }  else {
                FW.FileWrite( " Failed "   , true , false  ) ;
                cout << " ===============================================================\n" ;
            }

    }
    return m_requests  ;
}



/** \brief function: GetCityFromName
 *
 * \param cityname string
 * \param cities City*
 * \param count int
 * \return City*
 *
 */
City&  FlightMapClass::GetCityFromName( const string cityName  ){
    #ifdef DEBUG3 
        cout << "GetCityFromName( " << '|' << cityName << '|' << " ) \n" ;
    #endif // DEBUG
    	string fixCityName = cityName ;
	fixCityName =  Trim( fixCityName ) ;
    #ifdef DEBUG2 
        cout << "fixed GetCityFromName( " << '|' << fixCityName << '|' << " ) \n" ;
    #endif // DEBUG
	for( int index = 0 ; index < m_CityCount ; index++ ){
#ifdef DEBUG 
    string temp = cities[index].Name();
    cout << " -cities[index].Name()      " << m_cities[index].Name()        << endl ; 
    
    cout << "             length =       " << temp.length() << endl ; 
    cout << " -cities[index].flightfrom  " << m_cities[index].flightfrom    << endl ; 
    cout << "  cityname                  " << cityName                    << endl ; 
    cout << "  cityname.length()         " << cityName.length()           << endl ; 
		  	        
#endif // DEBUG
        string fixToo = m_cities[ index ].Name() ;
        fixToo = Trim(fixToo) ;
        string fixFrom = m_cities[ index ].flightfrom  ;
        fixFrom = Trim( fixFrom ) ;
		if( ( fixToo == fixCityName )  ||  ( fixFrom == fixCityName ) ){
			return m_cities[ index ]  ;
		}
	}
    this->DoPause("Didn't match City " + cityName  );
    return m_cities[ 0 ] ;

}











#endif // LINKEDSTACK













