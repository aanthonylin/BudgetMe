#ifndef STARTERBUDGETMODEL_H
#define STARTERBUDGETMODEL_H

#include <vector>
#include <QString>
#include "budgetmeconstants.h"

class StarterBudgetModel
{
public:
	virtual ~StarterBudgetModel(){}
	virtual int getIncome() = 0;
	virtual std::vector<int> getEstSpending(BudgetMe::TimePeriod) = 0;
	virtual QString getIncomeQuestion() = 0;
	virtual QString getEstimateQuestion() = 0;
	virtual std::vector<QString> getCatNames() = 0;
	virtual bool genStarterBudget(int, std::vector<int>) = 0;
};
#endif // STARTERBUDGETMODEL_H
