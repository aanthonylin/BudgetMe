/*
 * Author: Hazem Sabsabi
 * Date 08/11/2021
 */
#include <QGroupBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include "GraphView.h"

using namespace std;
using namespace BudgetMe;

QT_CHARTS_USE_NAMESPACE

GraphView::GraphView(GraphModel *model, QString title) : BaseView(title)
{
	this->model = model;
	graphLayout = new QHBoxLayout();
	
	// Buttons for selecting the graph type.
	QGroupBox *group = new QGroupBox("Graph Type");
	QHBoxLayout *layout = new QHBoxLayout;
	QRadioButton *rButton = new QRadioButton("Bar");
	rButton->setChecked(true);
	connect(rButton, &QRadioButton::released, this, &GraphView::showBar);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Pie");
	connect(rButton, &QRadioButton::released, this, &GraphView::showPie);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Scatter");
	connect(rButton, &QRadioButton::released, this, &GraphView::showScatter);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Report");
	connect(rButton, &QRadioButton::released, this, &GraphView::showReport);
	layout->addWidget(rButton);
	group->setLayout(layout);
	addToView(group);

	// Display the graphs in between the radio button groups.
	addToView(graphLayout);

	// Buttons for selecting the time period.
	group = new QGroupBox("Time Period");
	layout = new QHBoxLayout;
	rButton = new QRadioButton("Weekly");
	connect(rButton, &QRadioButton::released, this, &GraphView::showWeekly);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Monthly");
	rButton->setChecked(true);
	connect(rButton, &QRadioButton::released, this, &GraphView::showMonthly);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Quarterly");
	connect(rButton, &QRadioButton::released, this, &GraphView::showQuarterly);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Yearly");
	connect(rButton, &QRadioButton::released, this, &GraphView::showYearly);
	layout->addWidget(rButton);
	group->setLayout(layout);
	addToView(group);
		
	showBar();
}

GraphView::~GraphView() {}

void GraphView::showBar()
{
	QHorizontalBarSeries *series = model->getBar();
	QChart *chart = new QChart();
	QChartView *chartView = new QChartView();
	chartView->setFixedSize(800, 500);
	
	// Flipping x and y, so that the graph will be horizontal.
	QBarCategoryAxis *y = model->barAxisX(); 
	QValueAxis *x = model->valueAxisY();
	
	clearGraphs();
	chart->addSeries(series);
	//chart->setTitle("EXAMPLE BAR CHART");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	
	chart->addAxis(x, Qt::AlignBottom); 
	chart->addAxis(y, Qt::AlignLeft);
	series->attachAxis(x);
	series->attachAxis(y);
	
	chartView->setChart(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	graphLayout->addWidget(chartView);
	currentGraph = Bar;
}

void GraphView::showPie()
{
	vector<QPieSeries *> series = model->getPie();
	QChart *chart;
	QChartView *chartView;
	
	
	clearGraphs();
	for (vector<QPieSeries*>::iterator it = series.begin(); it != series.end(); ++it)
	{
		chart = new QChart();
		chart->addSeries(*it);
		chart->setTitle((*it)->name());
		chart->legend()->hide();
		chart->setAnimationOptions(QChart::SeriesAnimations);
		chartView = new QChartView();
		chartView->setChart(chart);
		chartView->setRenderHint(QPainter::Antialiasing);
		graphLayout->addWidget(chartView);
	}
	currentGraph = Pie;
}

void GraphView::showLine()
{
	vector<QLineSeries *> series = model->getLine();
	QChart *chart = new QChart();
	QChartView *chartView = new QChartView();
	chartView->setFixedSize(1000, 500);
	
	clearGraphs();
	QBarCategoryAxis *axisX = model->barAxisX();
	QValueAxis *axisY = model->valueAxisY();
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	for (vector<QLineSeries*>::iterator it = series.begin(); it != series.end(); ++it)
	{
		chart->addSeries(*it);
		(*it)->attachAxis(axisX);
		(*it)->attachAxis(axisY);
	}
	//chart->setTitle("EXAMPLE LINE CHART");
	//chart->createDefaultAxes();
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chartView->setChart(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	graphLayout->addWidget(chartView);
}

void GraphView::showScatter()
{
	vector<QScatterSeries *> series = model->getScatter();
	QChart *chart = new QChart();
	QChartView *chartView = new QChartView();
	chartView->setFixedSize(1000, 500);
	
	clearGraphs();
	QBarCategoryAxis *axisX = model->barAxisX();
	QValueAxis *axisY = model->valueAxisY();
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	for (vector<QScatterSeries*>::iterator it = series.begin(); it != series.end(); ++it)
	{
		chart->addSeries(*it);
		(*it)->attachAxis(axisX);
		(*it)->attachAxis(axisY);
	}

	//chart->setTitle("EXAMPLE LINE CHART");
	//chart->createDefaultAxes();
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chartView->setChart(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	graphLayout->addWidget(chartView);
	currentGraph = Scatter;
}

void GraphView::showReport()
{
	QString reportData = model->getReport();
	QTextEdit *reportGraph = new QTextEdit();

	clearGraphs();
	reportGraph->setFixedSize(800, 600);

	reportGraph->append(reportData);
	reportGraph->show();
	reportGraph->setReadOnly(true);
	graphLayout->addWidget(reportGraph);
	currentGraph = Report; 
}

void GraphView::showWeekly() {
	model->filterData(Weekly);
	refreshGraphs();
}

void GraphView::showMonthly() {
	model->filterData(Monthly);
	refreshGraphs();
}

void GraphView::showQuarterly() {
	model->filterData(Quarterly);
	refreshGraphs();
}

void GraphView::showYearly() {
	model->filterData(Yearly);
	refreshGraphs();
}

void GraphView::refreshGraphs() {
	switch (currentGraph) {
		case Bar: 
			showBar();
			break;
		case Pie: 
			showPie();
			break;
		case Scatter: 
			showScatter();
			break;
		default: 
			showReport();
			break;
	}		
}
	
void GraphView::clearGraphs() {
	QLayoutItem *child;
	
	// Removes previous chartViews.
	while ((child = graphLayout->takeAt(0)) != nullptr) {
    delete child->widget(); // delete the widget
    delete child;   // delete the layout item
	}
}
