#ifndef SUMMARYSPENDINGMODEL_H
#define SUMMARYSPENDINGMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class SummarySpendingModel : public GraphModel
{
	public:
		SummarySpendingModel(BudgetMeModel *);
		~SummarySpendingModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif
