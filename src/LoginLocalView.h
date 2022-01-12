/*	For CS3307
	By Brian Au
	2021-11-30
*/
#ifndef LOGLOCVIEW_H
#define LOGLOCVIEW_H

#include "baseview.h"
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <string>
#include <QString>
#include "LoginLocalModel.h"
#include "loginmanager.h"
 
/*!	@author Brian Au
	@brief View class for the application's login system.
	
	View class for the application's login system.
	Provide the GUI for the login window.
*/
class LoginLocalView : public BaseView
{
	Q_OBJECT
public:

	//!	@brief A constructor for login view.
	/*!	
		A constructor for the login portion of the view.
		@param login model connection.
		@param login manager connection.
		@param title of the login window.
	*/
	explicit LoginLocalView(LoginLocalModel *, LoginManager *, QString);
	
	//!	@brief A constructor for post login view.
	/*!	
		A constructor for the post login portion of the view.
		@param title of the login window.
	*/
	explicit LoginLocalView(QString);
	
	//!	@brief A destructor for login view.
	/*!	
		A destructor for the class.
	*/
	~LoginLocalView();
	
	//!	@brief A public method for handling login.
	/*!	
		A public method for handling login verification.
	*/
	void handleLogin();
	
	//!	@brief A public method for handling registration.
	/*!	
		A public method for handling registration process.
	*/
	void handleRegistration();
	
	//!	@brief A public method for handling guest.
	/*!	
		A public method for handling guest process.
	*/
	void handleGuest();
	
	//!	@brief A public method for cheching if a user has loggin in.
	/*!	
		A public method for cheching if a user has loggin in, and a session has begun.
		@return session status.
	*/
	bool getStatus();
	
	//!	@brief A public method for displaying the logout GUI.
	/*!	
		A public method for deleting the current GUI and displaying the logout GUI.
	*/
	void logout();
private:

	//!	@brief A private method for displaying the login GUI.
	/*!	
		A private method for deleting the current GUI and displaying the login GUI.
	*/
	void login();
	
	//!	@brief A private method for displaying the registration GUI.
	/*!	
		A private method for deleting the current GUI and displaying the registration GUI.
	*/
	void registration();
	
	//!	@brief A private method for handling logout.
	/*!	
		A private method for handling logout process.
	*/
	void handleLogout();
	
	//!	@brief A private method for initializing all the wigdets.
	/*!	
		A private method for initializing all the wigdets required for the different GUIs.
	*/
	void widgetIni();
	
	//!	@brief A private method for removing all the wigdets.
	/*!	
		A private method for removing all the wigdets required for the different GUIs.
	*/
	void removeWidget();
	
	//!	@brief A private method for adding the login wigdets.
	/*!	
		A private method for adding all the wigdets required for the login GUI.
	*/
	void addLoginWidget();
	
	//!	@brief A private method for adding the registration wigdets.
	/*!	
		A private method for adding all the wigdets required for the registration GUI.
	*/
	void addRegWidget();
	
	//! the upper label of the window.
	QLabel *topLab;
	
	//! the bottom label of the window.
	QLabel *botLab;
	
	//! the status label for the login/registration proccess of the window.
	QLabel *statusLab;
	
	//! the seperator line of the window.
	QFrame *spaceLine;
	
	//! the username textfield of the window.
	QLineEdit *usernameLine;
	
	//! the password textfield of the window.
	QLineEdit *passwordLine;
	
	//! the login button for the window.
	QPushButton *loginButton;
	
	//! the registration button for the window.
	QPushButton *registerButton;
	
	//! the logout button for the window.
	QPushButton *logoutButton;
	
	//! the guest button for the window.
	QPushButton *guestButton;
	
	//! the username entered by the user.
	QString username;
	
	//! the password entered by the user.
	QString password;
	
	//! the LoginLocalModel interface used by the class.
	LoginLocalModel *m_model;
	
	//! the Loginmanager interface used by the class.
	LoginManager *m_manager;
};
#endif
