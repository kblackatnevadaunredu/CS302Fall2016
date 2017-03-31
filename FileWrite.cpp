// *** ADDED BY HEADER FIXUP ***
#include "istream"
// *** END ***

#include <cstring>
#include <string>
#include "string.h" 
#include "city.h"
#include <iostream>
#include <fstream>

using namespace std;



#ifndef FILEWRITE_CPP
#define FILEWRITE_CPP



static class fw{    
        public:
        char LoG_FiLe[12] = {'l' , 'o', 'g' , 'F', 'i' , 'l' ,'e' ,'.', 't', 'x', 't', '\0'} ;

/** \brief function: fileWrite
 *
 * \param data City*&
 * \param count int
 * \return City*
 *
 */
/*void FileWrite( City*   data , int count ){
	fstream fileStreamWriter ;
    City* home = data ;
    fileStreamWriter.open( LOG_FILE , ( std::ios::out | std::ios::app ) );
    for( int i = 0 ; i < count ; i++ ){
		fileStreamWriter << data->Name() << ", visited=" << std::boolalpha << data->Visited  << std::endl ;
		data++ ;
	}

	fileStreamWriter.close();
    data = home ;
	return ;
}


  */
  

/* \brief FileWrite
 *
 * \param data City&
 * \return void
 *
 */
void FileWrite( City  & data   ){
	fstream fileStreamWriter ;
  
    fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::app ) );
    
		fileStreamWriter << data.Name() << ", visited=" << std::boolalpha << data.Visited  << std::endl ;
	fileStreamWriter << "# of Destinations : " << data.DestinationCount() << endl ;
	for( int i = 0 ; i < data.DestinationCount(); i++ ){
	   // fileStreamWriter << data.GetDestination(i) << " "  ;
		
	}

	fileStreamWriter.close();
    
	return ;
}



/** \brief 
 *
 * \param data string
 * \param numdata int
 * \param newline bool
 * \param truncate bool
 * \return void
 *
 */       
void FileWrite( string data, int numdata,  bool newline   , bool truncate ) {
    fstream fileStreamWriter ;
   
    if(truncate){
        fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::trunc ) );
    } else {
        fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::app ) );
    }
    if(newline){
    fileStreamWriter << data  << "  " << numdata <<   std::endl ;
    } else {
    fileStreamWriter << data  << "  " << numdata << " " ;
    }


	fileStreamWriter.close();
   
	return ;

}



/** \brief FileWrite
 *
 * \param data string
 * \param newline bool
 * \param truncate bool
 * \return void
 *
 */      
void  FileWrite( string data, bool newline  , bool truncate  ) {
    fstream fileStreamWriter ;
    if(truncate){
        fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::trunc ) );
    } else {
        fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::app ) );
    }
    if(newline) {
         fileStreamWriter << data << endl ;
    } else { 
         fileStreamWriter << data << " "  ;
    }
    
    
    fileStreamWriter.close();
}



/** \brief FileWrite
 *
 * \param data int
 * \param newline bool
 * \param truncate bool
 * \return void
 *
 */      
void  FileWrite( int data, bool newline, bool truncate  ) {
   fstream fileStreamWriter ; 
    if(truncate){
        fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::trunc ) );
    } else {
        fileStreamWriter.open( LoG_FiLe , ( std::ios::out | std::ios::app ) );
    }
    if(newline) {
         fileStreamWriter << data << endl ;
    } else { 
         fileStreamWriter << data << " "  ;
    }
    fileStreamWriter.close();
    
}





} FW ; 



#endif // FILEWRITE_CPP


