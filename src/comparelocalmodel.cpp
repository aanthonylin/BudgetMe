#include "comparelocalmodel.h"

using namespace BudgetMe;

CompareLocalModel::CompareLocalModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Your");
	dataNames.push_back("Local");
	filterData(Monthly);
}

CompareLocalModel::~CompareLocalModel() {}

void CompareLocalModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getEstSpending(time));
	data.push_back(subModel->getLocalSpending(time));
}
