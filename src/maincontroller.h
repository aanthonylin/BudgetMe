#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "loginmanager.h"
#include "SQLManager.h"

class MainController : public QObject, public LoginManager {
public:
	MainController();
	~MainController();
	void goGuest();
	void goMain();
private:
	SQLManager *m_storage;
	QWidget *m_window;
	void goGuestDelayed();
	void goMainDelayed();
};
#endif // MAINCONTROLLER_H
