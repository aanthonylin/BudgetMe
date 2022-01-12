#ifndef PREFERENCESMANAGER_H
#define PREFERENCESMANAGER_H

#include "preferencesmodel.h"

class PreferencesManager : public PreferencesModel {
public:
	PreferencesManager(bool = true);
	~PreferencesManager();
	bool getCanSave();
	bool getSmartSpendingOption();
	void setSmartSpendingOption(bool);
	bool getSmartBudgetOption();
	void setSmartBudgetOption(bool);
	bool getSharingOption();
	void setSharingOption(bool);
	bool getWarningOption();
	void setWarningOption(bool);
	
private:
	bool m_canSave;
	bool m_isSmartSpendingEnabled;
	bool m_isSmartBudgetEnabled;
	bool m_isSharingEnabled;
	bool m_isWarningEnabled;
};	
#endif // PREFERENCESMANAGER_H
