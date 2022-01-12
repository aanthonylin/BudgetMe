#include <vector>
#include <QtCharts/QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include "summarytransactionmodel.h"
#include "LocalStorageManager.h"

using namespace std;

SummaryTransactionModel::SummaryTransactionModel(BudgetMeModel *subModel) {
	this->subModel = subModel;
	reportTitle = "Report Title";
	barTitle = "Bar Title";
	lineTitle = "Line Title";
}

SummaryTransactionModel::~SummaryTransactionModel() {}

QHorizontalBarSeries * SummaryTransactionModel::getBar(QDate start, QDate end)
{
	vector<int> data = subModel->getActSpendPerCat(start, end); 
	QHorizontalBarSeries *series = new QHorizontalBarSeries();
	QBarSet *dataSet = new QBarSet(barTitle);
	maxVal = 0;
	for (int i = 0; i < (int)data.size(); i++)
	{
		dataSet->append(data[i]);
		if(data[i] > maxVal) {maxVal = data[i];}
	}
	series->append(dataSet);
	return series;
}

QLineSeries * SummaryTransactionModel::getLine(QDate start, QDate end)
{
	vector<int> data = subModel->getActSpendPerDay(start, end);
	QLineSeries *dataSet = new QLineSeries();
	dataSet->setName(lineTitle);
	maxVal = 0;
	for (int i = 0; i < (int)data.size(); i++)
	{
		dataSet->append(i, data[i]);
		if(data[i] > maxVal) {maxVal = data[i];}
	}
	return dataSet;
}

QValueAxis * SummaryTransactionModel:: valueAxisY() {
	QValueAxis *y = new QValueAxis();
	y->setRange(0,maxVal);
	return y;
}

QBarCategoryAxis * SummaryTransactionModel:: barAxisX () {
	QStringList categories;
	QBarCategoryAxis *x = new QBarCategoryAxis();
	vector<QString> catNames = subModel->getCatNames();
	
	// Generating axis.
	for(int i = 0; i < (int)catNames.size(); i++) {
		categories << catNames[i];
	}
	x->append(categories);
	return x;
}

QString SummaryTransactionModel::getReport(QDate start, QDate end)
{
	vector<struct LocalStorageManager::transactionInfo> data = subModel->getTransactions(start, end);
	QString container = "";
	vector<QString> catNames = subModel->getCatNames();
	container += "===================================================================\n";
	container += reportTitle + ":\n";
	container += "From: " + start.toString() + " To: " + end.toString() + ":\n\n";
	for (int i = 0; i < (int)data.size(); i++)
	{
		container += data[i].name + "\n";
		container += "$" + QString::number(data[i].cost) + "\n";
		container += data[i].date.toString() + "\n";
		container += catNames[data[i].catid] + "\n\n";
	}
	return container;
}


