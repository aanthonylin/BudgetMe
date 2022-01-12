#ifndef COMPARESERVERMODEL_H
#define COMPARESERVERMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class CompareServerModel : public GraphModel
{
	public:
		CompareServerModel(BudgetMeModel *);
		~CompareServerModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // COMPARESERVERMODEL_H
