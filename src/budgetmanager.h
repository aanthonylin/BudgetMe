#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <vector>

/**
* @brief BudgetMe Algorithms.
*
* Algorithms that perform key budget-related processing.
*
* @author Christopher F. S. Maligec
*/
class BudgetManager
{
public:
	virtual ~BudgetManager(){}
	
/**
* @brief Makes sure spending is within budget.
*
* Check each category of estimated spending 
* and verifies that it's within the budget.
*
* @param estSpending : user-estimated spending per category.
* @param budget : budget assigned to the user per category.
*
* @return true if there is no overspending, 
* and false if a spending category exceeds its budget
*/
	virtual bool isWithinBudget(std::vector<int>, std::vector<int>) = 0;
	
/**
* @brief Lists overspending amounts
*
* Provides the amounts by which the user is overspending in each category.
*
* @param estSpending : user-estimated spending per category.
* @param budget : budget assigned to the user per category.
*
* @return The amounts per category of overspending.
*/
	virtual std::vector<bool> getOverspending(std::vector<int>, std::vector<int>) = 0;
	
/**
* @brief Generate Starter Budget
*
* Creates a first budget for the user based on their estimated spending and income 
* and values from Statistics Canada.
*
* @param avgSpending : Average Canadian spending per category in dollar amounts.
*
* @return DESCRIPTION OF RETURN
*/
	virtual std::vector<int> starterBudget(std::vector<int>, int, int) = 0;
	virtual std::vector<int> smartSpend(std::vector<int>, std::vector<int>, double) = 0;
	virtual std::vector<int> smartBudget(std::vector<int>, std::vector<int>, std::vector<int>, double) = 0;
};
#endif // BUDGETMANAGER_H
