#ifndef COMPAREBUDGETMODEL_H
#define COMPAREBUDGETMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class CompareBudgetModel : public GraphModel
{
	public:
		CompareBudgetModel(BudgetMeModel *);
		~CompareBudgetModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // COMPAREBUDGETMODEL_H
