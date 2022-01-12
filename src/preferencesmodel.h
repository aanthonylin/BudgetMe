#ifndef PREFERENCESMODEL_H
#define PREFERENCESMODEL_H

class PreferencesModel
{
public:
	virtual ~PreferencesModel(){}
	virtual bool getCanSave() = 0;
	virtual bool getSmartSpendingOption() = 0;
	virtual void setSmartSpendingOption(bool) = 0;
	virtual bool getSmartBudgetOption() = 0;
	virtual void setSmartBudgetOption(bool) = 0;
	virtual bool getSharingOption() = 0;
	virtual void setSharingOption(bool) = 0;
	virtual bool getWarningOption() = 0;
	virtual void setWarningOption(bool) = 0;
};
#endif // PREFERENCESMODEL_H
