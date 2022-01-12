#include "comparepreviewmodel.h"

using namespace BudgetMe;

ComparePreviewModel::ComparePreviewModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Estimated Spending");
	dataNames.push_back("Actual Budget");
	dataNames.push_back("Preview Budget");
	filterData(Monthly);
}

ComparePreviewModel::~ComparePreviewModel() {}

void ComparePreviewModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getEstSpending(time));
	data.push_back(subModel->getBudget(time));
	data.push_back(subModel->getPreviewBudget(time));
}
