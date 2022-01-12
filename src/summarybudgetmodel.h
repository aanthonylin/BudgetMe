#ifndef SUMMARYBUDGETMODEL_H
#define SUMMARYBUDGETMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class SummaryBudgetModel : public GraphModel
{
	public:
		SummaryBudgetModel(BudgetMeModel *);
		~SummaryBudgetModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // SUMMARYBUDGETMODEL_H
