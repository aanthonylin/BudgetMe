#include <QGroupBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include "summarytransactionview.h"

using namespace std;
using namespace BudgetMe;

QT_CHARTS_USE_NAMESPACE

SummaryTransactionView::SummaryTransactionView(SummaryTransactionModel *model, QString title) : BaseView(title)
{
	this->model = model;
	graphLayout = new QHBoxLayout();
	
	// Buttons for selecting the graph type.
	QGroupBox *group = new QGroupBox("Graph Type");
	QHBoxLayout *layout = new QHBoxLayout;
	QRadioButton *rButton = new QRadioButton("Bar");
	rButton->setChecked(true);
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showBar);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Line");
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showLine);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Report");
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showReport);
	layout->addWidget(rButton);
	group->setLayout(layout);
	addToView(group);

	// Display the graphs in between the radio button groups.
	addToView(graphLayout);

	// Buttons for selecting the time period.
	group = new QGroupBox("Time Period");
	layout = new QHBoxLayout;
	rButton = new QRadioButton("Last 7 Days");
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showWeekly);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Last 30 Days");
	rButton->setChecked(true);
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showMonthly);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Last 90 Days");
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showQuarterly);
	layout->addWidget(rButton);
	rButton = new QRadioButton("Last 365 Days");
	connect(rButton, &QRadioButton::released, this, &SummaryTransactionView::showYearly);
	layout->addWidget(rButton);
	group->setLayout(layout);
	addToView(group);
	currentGraph = Bar;
	end = QDate::currentDate();
	showMonthly();
}

SummaryTransactionView::~SummaryTransactionView() {}

void SummaryTransactionView::showBar()
{
	QHorizontalBarSeries *series = model->getBar(start, end);
	QChart *chart = new QChart();
	QChartView *chartView = new QChartView();
	chartView->setFixedSize(800, 500);
	
	// Flipping x and y, so that the graph will be horizontal.
	QBarCategoryAxis *y = model->barAxisX(); 
	QValueAxis *x = model->valueAxisY();
	
	clearGraphs();
	chart->addSeries(series);
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

void SummaryTransactionView::showLine()
{
	QLineSeries * series = model->getLine(start, end);
	QChart *chart = new QChart();
	QChartView *chartView = new QChartView();
	chartView->setFixedSize(1000, 500);
	
	clearGraphs();
	chart->addSeries(series);
	chart->createDefaultAxes();
	
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chartView->setChart(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	graphLayout->addWidget(chartView);
	currentGraph = Line;
}

void SummaryTransactionView::showReport()
{
	QString reportData = model->getReport(start, end);
	QTextEdit *reportGraph = new QTextEdit();

	clearGraphs();
	reportGraph->setFixedSize(800, 600);

	reportGraph->append(reportData);
	reportGraph->show();
	reportGraph->setReadOnly(true);
	graphLayout->addWidget(reportGraph);
	currentGraph = Report; 
}

void SummaryTransactionView::showWeekly() {
	start = end.addDays(-7);
	refreshGraphs();
}

void SummaryTransactionView::showMonthly() {
	start = end.addDays(-30);
	refreshGraphs();
}

void SummaryTransactionView::showQuarterly() {
	start = end.addDays(-90);
	refreshGraphs();
}

void SummaryTransactionView::showYearly() {
	start = end.addDays(-365);
	refreshGraphs();
}

void SummaryTransactionView::refreshGraphs() {
	switch (currentGraph) {
		case Bar: 
			showBar();
			break;
		case Line: 
			showLine();
			break;
		default: 
			showReport();
			break;
	}		
}
	
void SummaryTransactionView::clearGraphs() {
	QLayoutItem *child;
	
	// Removes previous chartViews.
	while ((child = graphLayout->takeAt(0)) != nullptr) {
    delete child->widget(); // delete the widget
    delete child;   // delete the layout item
	}
}
