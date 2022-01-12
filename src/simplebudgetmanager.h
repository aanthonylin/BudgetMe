#ifndef SIMPLEBUDGETMANAGER_H
#define SIMPLEBUDGETMANAGER_H

#include "budgetmemodel.h"
#include "budgetmanager.h"

class SimpleBudgetManager : public BudgetManager
{
public:
	SimpleBudgetManager();
	~SimpleBudgetManager();
	bool isWithinBudget(std::vector<int>, std::vector<int>);
	std::vector<bool> getOverspending(std::vector<int>, std::vector<int>);
	std::vector<int> starterBudget(std::vector<int>, int, int);
	std::vector<int> smartSpend(std::vector<int>, std::vector<int>, double);
	std::vector<int> smartBudget(std::vector<int>, std::vector<int>, std::vector<int>, double);
};
#endif // SIMPLEBUDGETMANAGER_H
