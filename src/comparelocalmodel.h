#ifndef COMPARELOCALMODEL_H
#define COMPARELOCALMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class CompareLocalModel : public GraphModel
{
	public:
		CompareLocalModel(BudgetMeModel *);
		~CompareLocalModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // COMPARELOCALMODEL_H
