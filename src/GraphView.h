/*! GraphView class is used to display the data by retrieving the series and then creating the graphs.
 * @Author: Hazem Sabsabi
 * @Date 08/11/2021
 */
#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QString>
#include <vector>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include "baseview.h"
#include "GraphModel.h"

QT_CHARTS_USE_NAMESPACE

class GraphView : public BaseView
{
	public:
		enum Graphs {Bar, Pie, Scatter, Report}; /*!< enum for the different graph types */
		GraphView(GraphModel *, QString); /*< Constructor to initialize the model used to create the graphs */
		~GraphView(); /*< Deconstructor */
		void showBar(); /*<showBar method used to display the bar graph(s) */
		void showPie(); /*<ShowPie method used to display the pie graph(s) */
		void showLine(); /*<showLine method used to display the line graph(s) */
		void showReport(); /*<showReport method used to display the numbers within the graphs */
		void showScatter(); /*<showScatter method used to display the scatter graph(s) */
		void showWeekly(); /*< showWeekly is used to display weekly spending/weekly transactions based on the data filtered*/
		void showMonthly(); /*< showMonthly is used to display monthly expenses/transactions */
		void showQuarterly(); /*< showQuarterly is used to display quarterly expenses/transactions */
		void showYearly(); /*< showYearly is used to display yearly expenses/transactions */

	//protected:

	private:
		GraphModel *model; /*< GraphModel variable is used to retrieve the data required for the graph views. */
		QHBoxLayout *graphLayout; /*< QHBoxLayout is used to store the different graphs for displaying */
		Graphs currentGraph; /*< currentGraph is used to specify the current graph */
		void refreshGraphs(); /*< refreshGraphs method is used to refresh the graphs after a user changes the time frame */
		void clearGraphs(); /*< clearGraphs is used to clear all the graphs */
};

#endif
