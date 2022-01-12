#ifndef COMPAREAVGMODEL_H
#define COMPAREAVGMODEL_H

#include "GraphModel.h"
#include "budgetmeconstants.h"

class CompareAvgModel : public GraphModel
{
	public:
		CompareAvgModel(BudgetMeModel *);
		~CompareAvgModel();
		void filterData(BudgetMe::TimePeriod);
};

#endif // COMPAREAVGMODEL_H
