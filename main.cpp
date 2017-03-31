
/** ***************************************************************
 *  \file    : main.cpp
 *  \author  : Kelly Black
 *  \project : PA03 - Flight Paths
 *  \date    : Spring 2017
 *
 *  \description : MAIN DRIVER
 *                 CONTAINS PROGRAM ENTRY 
 *                 AND OTHER INFORMATION
  ***************************************************************** */


/**< Built in Libraries */
#include <iostream>
#include <fstream>
#include <istream>
#include "locale"
#include "string"
#include <string.h>
#include <cstring>
#include <memory>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <list>


/**< External Libraries */
#include "city.h"
#include "node1.h"
#include "flightmapclass.h"
#include "FileWrite.cpp" 


/* ************************************************* */
/**< Conditional compilation */
/**< un-comment for debug messages /  */
// #define DEBUG 
// #define DEBUG2
// #define DEBUG3
// #define DOPAUSE
#define LINKEDSTACK  
/**< comment LINE ABOVE for STL stack    */
/* ************************************* */
#ifdef LINKEDSTACK
/* ************************************* */
#include "linkedstack.h"
/* ************************************* */
#else   // USE STL STACK
/* ************************************* */
#include <stack>
/* ************************************* */
#endif // LINKEDSTACK
/* ************************************* */
/* ************************************************  */


// ===============================================
/**< Function Prototypes */

/**<   GetCities reads all the cities in from a file and returns an array of cities */
//City*  GetCities(        const string  , City*      , int  ) ;
/**<   GetCityFromName uses the name to return the City from the array of cities */
//City   GetCityFromName(  const string  , City*&     , int  ) ;
/**<   GetCityIndex uses the name to find the index of the city in the array of cities */
//int    GetCityIndex(     const string  , City*      , int  ) ; 
/**<   GetFlights reads flight data in from file for all Cities */
//City*  GetFlights(       const char *  , City*&     , int  ) ;
/**<   GetFlights reads flight data in from file for a single City */
//City*  GetFlights(       const char*   , City&      , City*  , int ,    City*& , int        ) ;
/**<   ConnectFlight matches a City to its flight data */
//City*  ConnectFlight (  City &         , City*      , int    , City*  , int    , bool *     ) ;
/**<   CitiesToFlights matches all cities to their flight data  */
//City*  CitiesToFlights( City*,int      , City*      , int    , bool*                        ) ;

/**<   REWINDS AND DISPLAYS FLIGHT PATH */
//float  ShowResult(int cityIndex, int originIndex , City* cities  ) ;

/** \brief FlightSearch(....)  - is called from ProcessRequests and uses a 
                                  Stack/LinkedStack to find the path for 
                                  each request.
 *   
 * \param originCity      - City* - the city to start from 
 * \param destinationCity - City* - the city to hopefully find a path to. 
 * \param cities          - City* - array of the cities
 * \param flights         - City* - array of the flight data 
 * \param flightCount     - int   - the number of flights in the flight array 
 * \param iVisited        - bool* - an array whose indexes match that 
                                    of the city array. Used to determine
                                    if a city has been visited or not. 
 * \param cityCount       - int   - the number of cities in the array of cities
 * \pre                           - all arrays should contain their respective data
                                    an instance of the origin and destination city 
 * \post return bool              - true if a flight path is found  
 *
 ________________________________________________________________________________________________ */        
//bool   FlightSearch( const string        , const string      , City*  , City*  , int    , bool*,int  ) ;

/**<   Reads requests from file and returns an array of requests */
//City*  GetRequests(      const char *  , City*      , int  ) ;

/**<   Reads requests from the requests array and processes each request */
//City*  ProcessRequests(  City*,int     , City*      , int    , City*  , int    ,  bool*     ) ;

/**<   Set all cities in the city array to not visited */
//City*  UnVisitAll( City* Cities , bool * ,int CityCount ) ;

/**<   determines the # of available destination cities that have not been visited */
//int    HasRoutes( string cityName , City * cities , int cityCount , bool* bVisited , City* Airflights , int flightCount ) ;

/**<   returns the number of lines in a text file */
//int    CountLines(  const char * filename )   ;

/**<   Find positions of character data for parsing data files  */
//int    FirstDigitPosition(const string & dataLine , int  digPos             )  ; 
//int    FirstCommaPosition(const string & dataLine , int  punctPos           )  ;
//int    FirstWhitePosition(const string & dataLine , int  pos ,  int  digPos )  ;



/**<   Used to write to the log file /
void FileWrite( string data, bool newline  = true , bool truncate = false   )  ;
void FileWrite( int    data, bool newline  = true , bool truncate = false   )  ;
void FileWrite( string data, int  numdata,          bool newline  = true    , bool truncate = false ) ;
void FileWrite( City*& data, int  count  ) ;
void FileWrite( City   data              ) ;
*/

/**< Functions to remove white space */
//string rTrim( string & str2cl ) ;
//string lTrim( string & str2cl ) ;
//string  Trim( string & str2cl ) ;


/** < Global Variables   */
 char   CITY_FILE[]    = "cityFile.txt"     ;
 char   FLIGHTS_FILE[] = "flightFile.txt"   ;
 char   REQUEST_FILE[] = "requestFile.txt"  ;
 char   LOG_FILE[]     = "logFile.txt"      ;


 string no_city = "NO_CITY" ;

/**< Namespace */
using namespace std;


/**< ======================================================= */
/** \brief MAIN - Program Entry Starts Here ------------------\
 *  ==========================================================|
 * \param argc     - int   - command line parameter count     |
 * \param argv[]   - char* - array of command line parameters |
 * \return         - int   - exit code                        |
 *  ==========================================================|
 *___________________________________________________________*/
/**< ========================================================*/
int main( int argc , char* argv[] ){
    
    FlightMapClass FM(CITY_FILE, FLIGHTS_FILE, REQUEST_FILE) ;
    FW.FileWrite(" FLIGHT PATHS LOADING "  ,true,true ) ; 
    /**< Variables  */
    int cityCount = 0 ;
    string  dummy = "";
    cityCount    = FM.CountLines( CITY_FILE  );

    for(int i = 0 ; i < cityCount ; i++ ){
        FM.ClearVisited( i ) ;
    }
     /** \brief City* requests -
     * \param REQUEST_FILE = filename
     * \param requests - Request Objects (Stored in 'City' class
     * \param requestCount = # of requests
     * \return - resulting City class with flightfrom and flightdest filled
     */
    //requestCount   = FM.CountLines ( REQUEST_FILE ) ;
    //City* requests = new    City[ requestCount ] ;
    //requests       = FM.GetRequests( );

    bool processed= FM.ProcessRequests(  )  ;

    cout << "Counted: " << cityCount << "  " << processed <<  endl;
    cout << " Press a key and hit enter to exit " << endl ;
    cin >> dummy ;
    return 0;
};



/** \brief GetFileNameAndPath
 *
 * \param location string
 * \param fileName string&
 * \param filePath string&
 * \return void
 *
 */
void GetFileNameAndPath( char* locationch , string & fileName , string & filePath){

	string location = locationch ;
            std::size_t found = location.find_last_of( "/\\" );
            fileName =  location.substr(( found + 1 )) ;
            filePath = location.substr(0,( int )( found )) ;
            std::cout << " path: " <<  filePath << '\n';
            std::cout << " file: " <<  fileName << '\n';

}
