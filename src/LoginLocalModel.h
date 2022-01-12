/*	For CS3307
	By Brian Au
	2021-11-30
*/
#ifndef LoginServer_CLASS_H
#define LoginServer_CLASS_H
#include "LocalStorageManager.h"
#include <string>

using namespace std;

/*!	@author Brian Au
	@brief Interface for accessing the userid table of application's database.
	
	Interface for accessing the userid table of application's database. 
	Provide the interface for user ID retrieval and storage methods.
*/
class LoginLocalModel {

    public:
	
		//!	@brief A virtual destructor.
		/*!	
			A virtual destructor for LoginLocalModel.
		*/
		virtual ~LoginLocalModel(){}
		
		//!	@brief A pure virtual method for adding a user ID to database.
		/*!	
			A pure virtual method for storing a new user ID in the application's database.
			@param username
			@param password
			@return the status of the registration.
		*/
        virtual bool registerLocal(string, string) = 0;
		
		//!	@brief A pure virtual method for checking a user ID in database.
		/*!	
			A pure virtual method for checking if a user ID exists in the application's database.
			@param username
			@param password
			@return the verification result.
		*/
        virtual bool loginLocal(string, string) = 0;
		
		//!	@brief A pure virtual method for checking if a user has logged in.
		/*!	
			A pure virtual method for checking a user has logged in to the application and that a session has begun.
			@return session status.
		*/
		virtual bool hasSession() = 0;
		
		//!	@brief A pure virtual method for checking if the session is in guess mode.
		/*!	
			A pure virtual method for checking the current session is in guess mode.
			@return session status.
		*/
		virtual void guestSession() = 0;

};

#endif
