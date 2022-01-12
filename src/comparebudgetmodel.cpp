#include "comparebudgetmodel.h"

using namespace BudgetMe;

CompareBudgetModel::CompareBudgetModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Estimated Spending");
	dataNames.push_back("Budget");
	filterData(Monthly);
}

CompareBudgetModel::~CompareBudgetModel() {}

void CompareBudgetModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getEstSpending(time));
	data.push_back(subModel->getBudget(time));
}
