/*
 * Author: Hazem Sabsabi
 * Date: 06/11/2021
 */

#include <iostream>
#include <QString>
#include "ReportModel.h"

ReportModel::ReportModel(BudgetMeModel *subModel, int numSeries)
{
	this->subModel = subModel;
	this->numSeries = numSeries;
	//filterData(defaultTimePeriodID);
}

ReportModel::~ReportModel(){}

QString ReportModel::getReport()
{	
	return QString("Place Holder");
}
