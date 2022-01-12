#ifndef WARNINGMANAGER_H
#define WARNINGMANAGER_H

class WarningManager
{
public:
	virtual ~WarningManager(){}
	virtual void showOverspendingWarning() = 0;
	virtual void hideOverspendingWarning() = 0;
};
#endif // WARNINGMANAGER_H
