#include "summarypreviewmodel.h"

using namespace BudgetMe;

SummaryPreviewModel::SummaryPreviewModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Preview Budget");
	filterData(Monthly);
}

SummaryPreviewModel::~SummaryPreviewModel() {}

void SummaryPreviewModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getPreviewBudget(time));
}
