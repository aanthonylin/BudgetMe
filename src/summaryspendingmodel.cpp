#include "summaryspendingmodel.h"

using namespace BudgetMe;

SummarySpendingModel::SummarySpendingModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Estimated Spending");
	filterData(Monthly);
}

SummarySpendingModel::~SummarySpendingModel() {}

void SummarySpendingModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getEstSpending(time));
}
