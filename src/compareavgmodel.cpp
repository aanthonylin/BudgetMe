#include "compareavgmodel.h"

using namespace BudgetMe;

CompareAvgModel::CompareAvgModel(BudgetMeModel *subModel) : GraphModel(subModel) {
	dataNames.push_back("Estimated Spending");
	dataNames.push_back("Average Spending");
	filterData(Monthly);
}

CompareAvgModel::~CompareAvgModel() {}

void CompareAvgModel::filterData(TimePeriod time) {
	data.clear();
	data.push_back(subModel->getEstSpending(time));
	data.push_back(subModel->getAvgSpending(time));
}
