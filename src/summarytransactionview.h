
#ifndef SUMMARYTRANSACTIONVIEW_H
#define SUMMARYTRANSACTIONVIEW_H

#include <vector>
#include <QString>
#include <QDate>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include "baseview.h"
#include "summarytransactionmodel.h"

QT_CHARTS_USE_NAMESPACE

class SummaryTransactionView : public BaseView
{
	public:
		enum Graphs {Bar, Line, Report};
		SummaryTransactionView(SummaryTransactionModel *, QString);
		~SummaryTransactionView();
		void showBar();
		void showLine();
		void showReport();
		void showWeekly();
		void showMonthly();
		void showQuarterly();
		void showYearly();
	private:
		SummaryTransactionModel *model;
		QHBoxLayout *graphLayout;
		Graphs currentGraph;
		QDate start;
		QDate end;
		void refreshGraphs();
		void clearGraphs();
};

#endif // SUMMARYTRANSACTIONVIEW_H
