/*	For CS3307
	By Brian Au
	2021-11-30
*/
#include "LoginLocalView.h"

// for login
LoginLocalView::LoginLocalView(LoginLocalModel *model, LoginManager *manager, QString title) : BaseView(title) {
	
	//TODO: Add all necessary widgets to m_mainLayout.
	// E.g., addToView(new QLabel("Placeholder"));
	
	m_model = model;
	m_manager = manager;
	username = "";
	password = "";
		
	// go to login view after initialization
	widgetIni();
	login();
	
}

// post login
LoginLocalView::LoginLocalView(QString title) : BaseView(title){
	
	//status = true;
	logoutButton = new QPushButton("Exit Program", this);
	spaceLine = new QFrame(this);
	spaceLine->setFrameShape(QFrame::HLine);
	spaceLine->setFrameShadow(QFrame::Sunken);
	logout();
}

LoginLocalView::~LoginLocalView(){}

// initialize all the widgets
void LoginLocalView::widgetIni(){
	topLab = new QLabel(this);
	botLab = new QLabel(this);
	statusLab = new QLabel("");
	loginButton = new QPushButton("Login", this);
	guestButton = new QPushButton("Login as Guest", this);
	registerButton = new QPushButton("Register", this);
	usernameLine = new QLineEdit(this);
	passwordLine = new QLineEdit(this);
	usernameLine->setClearButtonEnabled(true);
	passwordLine->setClearButtonEnabled(true);
	usernameLine->setMaxLength(15);
	passwordLine->setMaxLength(30);
	
	spaceLine = new QFrame(this);
	spaceLine->setFrameShape(QFrame::HLine);
	spaceLine->setFrameShadow(QFrame::Sunken);
}

// remove all the widget in the window
void LoginLocalView::removeWidget(){
	
	removeFromView(topLab);
	removeFromView(usernameLine);
	removeFromView(passwordLine);
	removeFromView(registerButton);
	removeFromView(statusLab);
	removeFromView(botLab);
	removeFromView(loginButton);
	removeFromView(spaceLine);
	removeFromView(guestButton);
	
}

// add all the login widget to thge window
void LoginLocalView::addLoginWidget(){
	
	addToView(topLab);
	addToView(usernameLine);
	addToView(passwordLine);
	addToView(loginButton);
	addToView(statusLab);
	addToFooter(botLab);
	addToFooter(registerButton);
	addToFooter(spaceLine);
	addToFooter(guestButton);
	
}

// add all the registration widget to the window
void LoginLocalView::addRegWidget(){
	
	addToView(topLab);
	addToView(usernameLine);
	addToView(passwordLine);
	addToView(registerButton);
	addToView(statusLab);
	addToFooter(botLab);
	addToFooter(loginButton);
	addToFooter(spaceLine);
	addToFooter(guestButton);
	
}

// login gui
void LoginLocalView::login(){
	
	removeWidget();
	widgetIni();
	
	topLab->setText("Login");
	botLab->setText("Register for a new account");
	
	usernameLine->setPlaceholderText("username");
	passwordLine->setPlaceholderText("password");
	passwordLine->setEchoMode(QLineEdit::Password);	// hide password
	
	// set button connection
	connect(loginButton, &QPushButton::released, this, &LoginLocalView::handleLogin);
	connect(passwordLine, &QLineEdit::returnPressed, this, &LoginLocalView::handleLogin); // Handling pressing enter when entering username and password
	connect(usernameLine, &QLineEdit::returnPressed, this, &LoginLocalView::handleLogin); // Handling pressing enter when entering username and password
	connect(registerButton, &QPushButton::released, this, &LoginLocalView::registration);
	connect(guestButton, &QPushButton::released, this, &LoginLocalView::handleGuest);
	
	addLoginWidget();
	
}

//registration gui
void LoginLocalView::registration(){
	
	removeWidget();
	widgetIni();
	
	topLab->setText("Registrastion");
	botLab->setText("Login with an existing account");
	
	usernameLine->setPlaceholderText("new username");
	passwordLine->setPlaceholderText("new password");
	passwordLine->setEchoMode(QLineEdit::Normal);	// reveal password for registration
	
	// set button connection
	connect(registerButton, &QPushButton::released, this, &LoginLocalView::handleRegistration);
	connect(passwordLine, &QLineEdit::returnPressed, this, &LoginLocalView::handleRegistration); // Handling pressing enter when entering username and password
	connect(usernameLine, &QLineEdit::returnPressed, this, &LoginLocalView::handleRegistration); // Handling pressing enter when entering username and password
	connect(loginButton, &QPushButton::released, this, &LoginLocalView::login);
	connect(guestButton, &QPushButton::released, this, &LoginLocalView::handleGuest);
	
	addRegWidget();
	
}

//handling login process
void LoginLocalView::handleLogin() {
	
	// make sure username and password is not empty
	if(usernameLine->text() != "" && passwordLine->text() != ""){
		
		username = usernameLine->text();
		password = passwordLine->text();
		
		// verify login credentials with the database
		if(m_model->loginLocal(username.toStdString(), password.toStdString())){
			
			// go to main windows after login success
			statusLab->setText("<font color='green'>:-) Login Successful. Loading application ...</font>");
			usernameLine->setEnabled(false);
			passwordLine->setEnabled(false);
			loginButton->setEnabled(false);
			registerButton->setEnabled(false);
			guestButton->setEnabled(false);
			m_manager->goMain();
			
		}
		else{
			// login failed: userid does not exists
			statusLab->setText("<font color='red'>:-( Login failed. Incorrect username or password.</font>");
		}
		
	}
	else{
		// login failed: empty userid
		statusLab->setText("<font color='red'>Empty username or password field.</font>");
		
	}
	
}

//handling registration process
void LoginLocalView::handleRegistration() {
	
	//make sure usernamd and password is not empty
	if(usernameLine->text() != "" && passwordLine->text() != ""){
		
		username = usernameLine->text();
		password = passwordLine->text();
		
		// verify and store register credentials with the database
		if(m_model->registerLocal(username.toStdString(), password.toStdString())){
			
			//go to main window after registration successful
			statusLab->setText("<font color='green'>:-) Registration successful. Loading application ...</font>");
			usernameLine->setEnabled(false);
			passwordLine->setEnabled(false);
			loginButton->setEnabled(false);
			registerButton->setEnabled(false);
			guestButton->setEnabled(false);
			m_manager->goMain();
		}
		
		else{
			//registration failed: username already exists in database
			statusLab->setText("<font color='red'>:-( Registration failed. Username has been taken.</font>");
		}
	}
	else{
		// registration failed: empty userid
		statusLab->setText("<font color='red'>Empty username or password field.</font>");
	}
	
}

//handling guest mode
void LoginLocalView::handleGuest(){
	
	m_model->guestSession();
	statusLab->setText("<font color='green'>:-) Logged in as GUEST. Loading application ...</font>");
	usernameLine->setEnabled(false);
	passwordLine->setEnabled(false);
	loginButton->setEnabled(false);
	registerButton->setEnabled(false);
	guestButton->setEnabled(false);
	m_manager->goGuest();
	
}

//logout gui
void LoginLocalView::logout() {
	
	connect(logoutButton, &QPushButton::released, this, &LoginLocalView::handleLogout);
	addToView(new QLabel("version 0.3"));
	addToFooter(spaceLine);
	addToFooter(logoutButton);
}

//handling logout process
void LoginLocalView::handleLogout() {
	exit(0);
}
	
	

