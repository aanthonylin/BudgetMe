/*
Author: Christopher F. S. Maligec
Date: 2021-11-03
*/
#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

/*!	@author Christopher F. S. Maligec.
	@brief Interface for accessing the main window of the application.
	
	Provides Interface for accessing the main window of the application.
*/
class LoginManager {

  public:
	//!	@brief A virtual destructor.
		/*!	
			A virtual destructor for LocalStorageManager.
		*/
	virtual ~LoginManager(){}
	
	//!	@brief A pure virtual method for accessing the guest window.
	/*!	
		A pure virtual method for accessing the guest window.
	*/
    virtual void goGuest() = 0;
	
	//!	@brief A pure virtual method for accessing the main window.
	/*!	
		A pure virtual method for accessing the main window.
	*/
	virtual void goMain() = 0;
};

#endif // LOGINMANAGER_H
