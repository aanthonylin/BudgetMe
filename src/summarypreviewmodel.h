#ifndef SUMMARYPREVIEWMODEL_H
#define SUMMARYPREVIEWMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class SummaryPreviewModel : public GraphModel
{
	public:
		SummaryPreviewModel(BudgetMeModel *);
		~SummaryPreviewModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // SUMMARYPREVIEWMODEL_H
