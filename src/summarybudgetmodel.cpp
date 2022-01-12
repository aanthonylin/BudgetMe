#include "summarybudgetmodel.h"

using namespace BudgetMe;

SummaryBudgetModel::SummaryBudgetModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Budget");
	filterData(Monthly);
}

SummaryBudgetModel::~SummaryBudgetModel() {}

void SummaryBudgetModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getBudget(time));
}
