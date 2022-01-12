#include <QLabel>
#include <QTimer>
#include "maincontroller.h"
#include "LoginLocalView.h"
#include "mainwindow.h"
#include "guestwindow.h"

MainController::MainController() {
	m_storage = new SQLManager();
	m_window = new LoginLocalView(m_storage, this, "Login");
	m_window->resize(300, 300);
	m_window->show();
}

MainController::~MainController() {
	delete m_window;
}

void MainController::goGuest() {
	QTimer::singleShot(1000, this, &MainController::goGuestDelayed);
}

void MainController::goGuestDelayed() {
	GuestWindow *win = new GuestWindow();
	win->show();
	delete m_window;
	m_window = win;
}

void MainController::goMain() {
	QTimer::singleShot(1000, this, &MainController::goMainDelayed);
}

void MainController::goMainDelayed() {
	MainWindow *win = new MainWindow(m_storage);
	win->show();
	delete m_window;
	m_window = win;
}




