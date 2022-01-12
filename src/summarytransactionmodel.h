#ifndef SUMMARYTRANSACTIONMODEL_H
#define SUMMARYTRANSACTIONMODEL_H

#include <QString>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "budgetmemodel.h"

QT_CHARTS_USE_NAMESPACE

class SummaryTransactionModel {
public:
	SummaryTransactionModel(BudgetMeModel *);
	~SummaryTransactionModel();
	QString getReport(QDate, QDate);
	QHorizontalBarSeries * getBar(QDate, QDate);
	QLineSeries * getLine(QDate, QDate);
	QValueAxis * valueAxisY();
	QBarCategoryAxis * barAxisX();
private:
	BudgetMeModel *subModel;
	QString reportTitle;
	QString barTitle;
	QString lineTitle;
	int maxVal;
};
#endif // SUMMARYTRANSACTIONMODEL_H
