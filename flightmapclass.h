/** ***********************************************************  
 *  \file    : flightmapclass.h
 *  \author  : Kelly Black
 *  \project : PA03 - Flight Paths
 *  \date    : Spring 2017
 *
 *  \description : FLIGHT MAP CLASS HEADER FILE
 *                 CONTAINS CITIES, FLIGHTS, REQUESTS 
 *                 AND OTHER INFORMATION
  ************************************************************* */

#include <string.h> 
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <array>

/**< Global Variables  /
 char   CITY_FILE[]    = "cityFile.txt"     ;
 char   FLIGHTS_FILE[] = "flightFile.txt"   ;
 char   REQUEST_FILE[] = "requestFile.txt"  ;
 char   LOG_FILE[]     = "logFile.txt"      ;
      */
 
using namespace std;

#ifndef FLIGHTMAPCLASS_H

#define FLIGHTMAPCLASS_H
#include "linkedstack.h"
#include "city.h"

 
class FlightMapClass
{
    public:

        /** Default constructor */
        FlightMapClass( const char* CITYFILE  , const char* FLIGHTFILE     ,const  char* REQUESTFILE    ) ;
        /** Default destructor */
        virtual ~FlightMapClass();
        /** Copy constructor
         *  \param other Object to copy from
         */
        FlightMapClass(const FlightMapClass& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        FlightMapClass& operator=(const FlightMapClass& other);
        /** \brief 
         *
         * \param filename const char*
         * \return int
         *
         */                                            
        int   CountLines(const char* filename);
        /** Access m_Counter
         * \return The current value of m_Counter
         */
        unsigned int GetCityCount() { return m_CityCount; }
        /** Access m_CurrentIndex
         * \return The current value of m_CurrentIndex
         */
        unsigned int GetCurrentIndex() { return m_CurrentIndex; }
        /** Set m_CurrentIndex
         * \param val New value to set
         */
        void SetCurrentIndex(unsigned int val) { m_CurrentIndex = val; }
        /** Access m_OriginIndex
         * \return The current value of m_OriginIndex
         */
        unsigned int GetOriginIndex() { return m_OriginIndex; }
        /** Set m_OriginIndex
         * \param val New value to set
         */
        void SetOriginIndex(unsigned int val) { m_OriginIndex = val; }
        /** Access m_DestinationIndex
         * \return The current value of m_DestinationIndex
         */
        unsigned int GetDestinationIndex() { return m_DestinationIndex; }
        /** Set m_DestinationIndex
         * \param val New value to set
         */
        void SetDestinationIndex(unsigned int val) { m_DestinationIndex = val; }
        /** Access m_Destination
         * \return The current value of m_Destination
         */
        string GetDestination(int cityIndex, int localIndex ) { return Trim( m_cities[ cityIndex ].GetDestination( localIndex )); }
        /** Set m_Destination
         * \param val New value to set
         */
        int GetDestinationCount( int index ) { return m_cities[ index ].DestinationCount() ; }
        /** Access m_cities
         * \return The current value of m_cities
         */
        City* GetCities() ;
        /** Set m_cities
         * \param val New value to set
         */
        City& Cities(int index ) { return m_cities[index] ; }
        /** Access m_flights
         * \return The current value of m_flights
         */
        City*   GetFlights() ;
        /** Get m_flights[index]
         * \param index value to set
         */
        City& Flight( int index ) { return m_flights[index]; }
        /** Access m_requests
         * \return The current value of m_requests
         */
        City* GetRequests();
        /** Set m_requests
         * \param val New value to set
         */
        City& Requests(int index) { return m_requests[index] ; }
        /** Access m_Visited
         * \return The current value of m_Visited
         */
        bool GetVisited(int index ) { return m_Visited[index]; }
        /** Set m_Visited
         * \param val New value to set
         */
        void SetVisited(int val) { m_Visited[val] = true ; }
        void ClearVisited(int val) { m_Visited[val] = false ; }
        /** Access m_HasRoutes
         * \return The current value of m_HasRoutes
         */
        int    HasRoutes( string cityName  ) ;
        /** Access m_GetNextCity
         * \return The current value of m_GetNextCity
         */
        int GetNextCity() ; 
        /** Access cityname)
         * \return The current value of cityname)
         */
        int GetCityIndex( const string  cityname) ; 
        /** Access toCity)
         * \return The current value of toCity)
         */
        //bool AddDestination( string fromCity, string toCity)  ;
        /** Set toCity)
         * \param val New value to set
         */
        string ToCity();
        /** Access toCity)
         * \return The current value of toCity)
         */
        bool  HasDestination(  string fromCity)  ; 
        /** Access )
         * \return The current value of )
         */
        City&  GetCityFromName( const string cityName  )  ; 

        float GetCostFromFlight( string flightfrom , string flightto ) ;
        /** Access )
         * \return The current value of )
         */
        City*  GetCities( const char*  filename,City* , int cityCount )  ; 
        /** Access )
         * \return The current value of )
         */
        City*  GetFlights( const char*  filename ,  int  )  ; 
        void  GetFlights( const char*  fileName , City & fromCity , int flightCount  ) ;
        /** Access )
         * \return The current value of )
         */
        string Trim( string & str2cl  )  ;

        /** Access )
         * \return The current value of )
         */
        string rTrim( string & str2cl  ) ; 

        /** Access )
         * \return The current value of )
         */
        string lTrim( string & str2cl  )  ; 

        /** Access )
         * \return The current value of )
         */
        bool FlightSearch( string fromCity, string toCity  ) ; 
        bool DoPause( string msg )  ;
        int   FirstCommaPosition(const string & dataLine , int punctPos  ) ;
        int   FirstDigitPosition(const string & dataLine , int  digPos )  ;
        int   FirstWhitePosition(const string & dataLine ,int pos ,  int  digPos ) ;
        
       int m_DestinationCount; //!< Member variable "m_DestinationCount"
        int m_GetNextCity; //!< Member variable "m_GetNextCity"
        int GetCityIndex(char* cityname ); //!< Member variable "cityname)"
        //bool AddDestination( int index, string fromCity, string toCity); //!< Member variable "toCity)"
        bool HasDestination( int index, string toCity); //!< Member variable "toCity)"

        float  ShowResult( int cityIndex, int localindex, int originIndex ); //!< Member variable ")"
        bool  ProcessRequests( ); //!< Member variable ")"
        void  UnVisitAll(  ); //!< Member variable ")"

    protected:
         char  cityFile[13]  = {'c','i','t','y','F','i','l','e','.','t','x','t','\0'} ;
        
         char  flightFile[15] = {'f','l','i','g','h','t','F','i','l','e','.','t','x','t','\0'};
        
         char  requestFile[16]  = {'r','e','q','u','e','s','t','F','i','l','e','.','t','x','t','\0'}  ;
        
    private:
        
        unsigned int m_CurrentIndex; //!< Member variable "m_CurrentIndex"
        unsigned int m_OriginIndex; //!< Member variable "m_OriginIndex"
        unsigned int m_DestinationIndex; //!< Member variable "m_DestinationIndex"
        string* m_Destination; //!< Member variable "m_Destination
        int  m_FlightCount ;
        int m_CityCount ;
        int m_RequestCount ;
        
        City* m_cities; //!< Member variable "m_cities"
        City* m_flights; //!< Member variable "m_flights"
        City* m_requests; //!< Member variable "m_requests"
        bool* m_Visited; //!< Member variable "m_Visited"
        
        char* m_flightsFile ;
        char* m_citiesFile ;
        char* m_requestsFile ;

}  ;

#endif // FLIGHTMAPCLASS_H
