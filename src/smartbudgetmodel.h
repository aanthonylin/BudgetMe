#ifndef SMARTBUDGETMODEL_H
#define SMARTBUDGETMODEL_H

class SmartBudgetModel
{
public:
	virtual ~SmartBudgetModel(){}
	virtual bool getSmartBudgetOption() = 0;
	virtual void setSmartBudgetOption(bool) = 0;
};
#endif // SMARTBUDGETMODEL_H	
