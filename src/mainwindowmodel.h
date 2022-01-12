#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QString>

class MainWindowModel
{
public:
	virtual ~MainWindowModel(){}
	virtual QString getSelectedTitle() = 0;
	virtual int getSelectedFeature() = 0;
	virtual void setSelectedFeature(int) = 0;
};
#endif // MAINWINDOWMODEL_H 
