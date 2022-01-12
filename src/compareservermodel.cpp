#include "compareservermodel.h"

using namespace BudgetMe;

CompareServerModel::CompareServerModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Your");
	dataNames.push_back("Server");
	filterData(Monthly);
}

CompareServerModel::~CompareServerModel() {}

void CompareServerModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getEstSpending(time));
	data.push_back(subModel->getServerSpending(time));
}
