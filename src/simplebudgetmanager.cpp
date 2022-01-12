#include "simplebudgetmanager.h"

using namespace std;

SimpleBudgetManager::SimpleBudgetManager() {
}

SimpleBudgetManager::~SimpleBudgetManager() {}

bool SimpleBudgetManager::isWithinBudget(vector<int> spending, vector<int> budget) {
	bool isOK = true;
	int len = spending.size();
	for(int i = 0; i < len; i++) {
		isOK &= (spending[i] <= budget[i]);
	}
	return isOK;
}

vector<bool> SimpleBudgetManager::getOverspending(vector<int> spending, vector<int> budget) {
	vector<bool> overspending;
	bool isCatOK;
	int len = spending.size();
	for(int i = 0; i < len; i++) {
		isCatOK = (spending[i] > budget[i]);
		overspending.push_back(isCatOK);
	}
	return overspending;
}

vector<int> SimpleBudgetManager::starterBudget(vector<int> avgSpending, int avgIncome, int income) {
	vector<int> budget;
	int catAmount;
	int len = avgSpending.size();
	for(int i = 0; i < len; i++) {
		catAmount = ((double) avgSpending[i] / avgIncome) * income;
		budget.push_back(catAmount);
	}
	return budget;
}

vector<int> SimpleBudgetManager::smartSpend(vector<int> actSpending, vector<int> estSpending, double margin) {
	for(int i = 0; i < (int)actSpending.size(); i++) {
		if(actSpending[i] > estSpending[i] * margin) {
			estSpending[i] = actSpending[i];
		}
	}
	return estSpending;
}

vector<int> SimpleBudgetManager::smartBudget(vector<int> spending, vector<int> avgSpending, vector<int> budget, double spendingCap) {
	vector<int> balance; 
	int totalSpending = 0;
	int totalSurplus = 0;
	int totalDeficit = 0;
	int catAmount;
	int len = spending.size();
	double spendingShare;
	// int moneyNeededToBalanceBudget = 0;
	
	
	// The budget is adjusted by passing surplusses from categories under budget to those over budget.
	
	for(int i = 0; i < len; i++) {
		
		// The total spending is calculated.
		totalSpending += spending[i];
		
		// The balance for each category is calculated.
		catAmount = budget[i] - spending[i];
		balance.push_back(catAmount);
		
		// Positive balances are added to the totalSurplus.
		if(catAmount >= 0) {
			totalSurplus += catAmount;
		}
		
		// Negative balances are added to the totalDeficit.
		else {
			totalDeficit += catAmount;
		}
	}	
		
		// If total surplus >0, then it can be used to offset the values of categories with spending deficits.
		// Otherwise, there is a global spending overflow, and a warning is generated.
	if(totalSurplus >= 0) {
			
			// To have a bare minimum balanced budget, 
			// strip each surplus category of its surplus, leaving just the spending value;
			// The sum of all the surplusses is the totalSurplus.
			// Take just enough from the totalSurplus to cover the deficits in the deficit categories.
			// Now all the values are at their bare minimum: the spending values.
			// This can be done in one step by setting all the budget values to their corresponding spending values.

			// The left over totalSurplus will be the difference between the original totalSurplus and the totalDeficit.
		totalSurplus += totalDeficit;
			
			// This left over totalSurplus will then be distributed over all the categories 
			// according to the share of each category's spending value.
		spendingShare = (1 + (double)totalSurplus/totalSpending);
		for(int i = 0; i < len; i++) {
			budget[i] = spending[i] * spendingShare;
			
			// So as not to create an upward spiral of spending in preferred categories to the detriment of others, 
			// a spending cap can be set by the user.
			if(budget[i] > avgSpending[i] * spendingCap) {
				budget[i] = avgSpending[i] * spendingCap;
			}
		}	
	}
	return budget;
}
