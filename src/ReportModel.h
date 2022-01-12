/*
 * Author: Hazem Sabsabi
 * Date: 06/11/2021
 */

#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <vector>
#include "budgetmemodel.h"
#include "budgetmeconstants.h"

class ReportModel
{
	public:
		ReportModel(BudgetMeModel *, int);
		virtual ~ReportModel();
		virtual void filterData(BudgetMe::TimePeriod) = 0;
		QString getReport();
	protected:
		BudgetMeModel *subModel;
		int numSeries;
		std::vector<std::vector<int>> data;
};

#endif // REPORTMODEL_H
