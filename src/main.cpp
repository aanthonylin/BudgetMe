/*
Author: Christopher F. S. Maligec
Description: Start the app and display the main window.
Date: 2021-10-31
*/

#include <QApplication>
#include "maincontroller.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainController controller;
	return app.exec();
}
