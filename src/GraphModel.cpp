#include <QtCharts/QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include "GraphModel.h"

using namespace std;

GraphModel::GraphModel(BudgetMeModel *subModel) {
	this->subModel = subModel;
}

GraphModel::~GraphModel(){}

int GraphModel::getSeriesCount() {
	return data.size();
}

int GraphModel::getCategoryCount(){
	return subModel->getCatNum();
}

vector<QPieSeries *> GraphModel::getPie()
{
	vector<QPieSeries *> container;
	QPieSeries *dataSet;
	vector<QString> catNames = subModel->getCatNames();

	QList<QPieSlice *> pieSliceList;
	for (int i = 0; i < getSeriesCount(); i++)
	{
		dataSet = new QPieSeries();
		dataSet->setName(dataNames[i]);
		for (int j = 0; j < getCategoryCount(); j++)
		{
			dataSet->append(catNames[j], data[i][j]);
		}
		pieSliceList = dataSet->slices();
		for (int i = 0; i < pieSliceList.size(); i++)
		{
			QPieSlice *slice = pieSliceList.at(i);
			slice->setLabelVisible();
			//slice->setExploded();
		}
		container.push_back(dataSet);
	}
	return container;
}

QHorizontalBarSeries * GraphModel::getBar()
{
	QHorizontalBarSeries *container = new QHorizontalBarSeries();
	QBarSet *dataSet;
	vector<QString> catNames = subModel->getCatNames();
		
	// Generating BarSets
	for (int i = 0; i < getSeriesCount(); i++)
	{
		dataSet = new QBarSet(dataNames[i]);
		for (int j = 0; j < getCategoryCount(); j++)
		{
			dataSet->append(data[i][j]);
		}
		container->append(dataSet);
	}
	return container;
}

vector<QLineSeries *>  GraphModel::getLine()
{
	vector<QLineSeries *> container;
	QLineSeries *dataSet;
	vector<QString> catNames = subModel->getCatNames();
	for (int i = 0; i < getSeriesCount(); i++)
	{
		dataSet = new QLineSeries();
		dataSet->setName(dataNames[i]);
		for (int j = 0; j < getCategoryCount(); j++)
		{
			dataSet->append(j, data[i][j]);
		}
	container.push_back(dataSet);
	}
	return container;
}

QValueAxis * GraphModel:: valueAxisY() {
	int max = 0;
	QValueAxis *y = new QValueAxis();
	for (int i = 0; i < getSeriesCount(); i++)
	{
		for (int j = 0; j < getCategoryCount(); j++)
		{
			if(data[i][j] > max) {max = data[i][j];}
		}
	}
	y->setRange(0,max);
	return y;
}

QBarCategoryAxis * GraphModel:: barAxisX () {
	QStringList categories;
	QBarCategoryAxis *x = new QBarCategoryAxis();
	vector<QString> catNames = subModel->getCatNames();
	
	// Generating axis.
	for(int i = 0; i < getCategoryCount(); i++) {
		categories << catNames[i];
	}
	x->append(categories);
	return x;
}

// This might have to be cleaned up later... vvvvv
vector<QString> GraphModel::catNames()
{
	return subModel->getCatNames();
}

QString GraphModel::getReport()
{
	QString container = "";
	vector<QString> catNames = subModel->getCatNames();
	int amount = 0;
	for (int i = 0; i < getSeriesCount(); i++)
	{
		container += "===================================================================\n";
		container = container + dataNames[i] + ":\n\n";
		for (int j = 0; j < getCategoryCount(); j++)
		{
			container = container + "\tCategory: \n\t";
			container = container + catNames[j];
			container = container + " \n\t\tAmount: ";
			amount = data[i][j];
			container = container + QString::number(amount) + "\n\n";
			//container = container + "\n";
		}
	}
	return container;
}
/*
vector<QPieSeries *> GraphModel::getPie()
{
	vector<QPieSeries *> container;
	QPieSeries *dataSet;
	vector<QString> catNames = subModel->getCatNames();

	QList<QPieSlice *> pieSliceList;
	for (int i = 0; i < getSeriesCount(); i++)
	{
		dataSet = new QPieSeries();
		dataSet->setName(dataNames[i]);
		for (int j = 0; j < getCategoryCount(); j++)
		{
			dataSet->append(catNames[j], data[i][j]);
		}
		pieSliceList = dataSet->slices();
		for (int i = 0; i < pieSliceList.size(); i++)
		{
			QPieSlice *slice = pieSliceList.at(i);
			slice->setLabelVisible();
			//slice->setExploded();
		}
		container.push_back(dataSet);
	}
	return container;
}
*/
vector<QScatterSeries *> GraphModel::getScatter()
{
	vector<QScatterSeries *> container;
	QScatterSeries *dataSet;
	vector<QString> catNames = subModel->getCatNames();
	for (int i = 0; i < getSeriesCount(); i++)
	{
		dataSet = new QScatterSeries();
		dataSet->setName(dataNames[i]);
		for (int j = 0; j < getCategoryCount(); j++)
		{
			dataSet->append(j, data[i][j]);
		}
	container.push_back(dataSet);
	}
	return container;
}
