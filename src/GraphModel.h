/*! GraphModel class is used to model the data by retrieving the data and then creating the series (line & dots on the graph).
 * @Author: Hazem Sabsabi
 * @Date 06/11/2021
 */

#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <vector>
#include <QString>
#include <string>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSlice>
#include <QtCharts/QScatterSeries>
#include "budgetmeconstants.h"
#include "budgetmemodel.h"

QT_CHARTS_USE_NAMESPACE

class GraphModel
{
	public:
		GraphModel(BudgetMeModel *); /*!< Constructor storing the model to call the data */
		virtual ~GraphModel(); /*!< Destructor */
		virtual void filterData(BudgetMe::TimePeriod) = 0; /*!< Virtual method to filter the data needed by each operation and comparison */
		int getSeriesCount(); /*!<Method that returns the number of Series to be used */
		int getCategoryCount(); /*!<Method that returns the number of categories used by the program */
		QString getReport(); /*!<Method that returns a report of the data specified by the filter method */
		QHorizontalBarSeries * getBar(); /*!<Method to return an a Bar Series */
		std::vector<QPieSeries *> getPie(); /*!<Method to return a Pie Series */
		std::vector<QLineSeries *> getLine(); /*!<Method to return a Line Series */
		std::vector<QScatterSeries *> getScatter(); /*!<Method to return a Scatter 'Series' */
		QValueAxis * valueAxisY(); /*!<Method to return the Value of the y Axis */
		QBarCategoryAxis * barAxisX(); /*!<Method to return the value of an Axis */
		std::vector<QString> catNames();
	protected:
		BudgetMeModel *subModel; /*!<Variable to hold the model that calls the data */
		std::vector<std::vector<int>> data; /*!<Variable to hold the data */
		std::vector<QString> dataNames; /*!<Variable to hold the name of the Graph */
};

#endif
