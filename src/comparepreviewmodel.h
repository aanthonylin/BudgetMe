#ifndef COMPAREPREVIEWMODEL_H
#define COMPAREPREVIEWMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class ComparePreviewModel : public GraphModel
{
	public:
		ComparePreviewModel(BudgetMeModel *);
		~ComparePreviewModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // COMPAREPREVIEWMODEL_H
