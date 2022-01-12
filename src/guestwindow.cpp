/*
Author: Christopher F. S. Maligec
Date: 2021-10-31
*/
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QStatusBar>

#include "guestwindow.h"
#include "SQLManager.h"
#include "BudgetMeDataManager.h"
#include "simplebudgetmanager.h"
#include "privacyview.h"
#include "starterbudgetview.h"
#include "entertransactionview.h"
#include "smartbudgetview.h"
#include "previewbudgetview.h"
#include "preferencesview.h"
#include "GraphView.h"
#include "summaryspendingmodel.h"
#include "summarybudgetmodel.h"
#include "summarypreviewmodel.h"
#include "compareavgmodel.h"
#include "comparebudgetmodel.h"
#include "comparepreviewmodel.h"
#include "comparelocalmodel.h"
#include "compareservermodel.h"
#include "LoginLocalView.h"
#include "summaryoverspendingview.h"
#include "preferencesmanager.h"
#include "summarytransactionmodel.h"
#include "summarytransactionview.h"

/*
GuestWindow Constructor
Description: Sets up the GUI.
As the top window its parent will always be null.
*/
GuestWindow::GuestWindow() {
	BudgetMeDataManager *statsManager = new BudgetMeDataManager();
	SimpleBudgetManager *budgetManager = new SimpleBudgetManager();
	
	m_featureModel = new FeatureModel();
	m_prefModel = new PreferencesManager(false);
	m_budgetModel = new BudgetMeModel(NULL, statsManager, budgetManager, m_prefModel);

	setWindowTitle("BudgetMe");
	createToolBars();
	resize(1000, 700);
	
	m_featureModel->setSelectedFeature(1);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new StarterBudgetView(m_budgetModel, this, s));
}

GuestWindow::~GuestWindow() {
	delete m_featureModel;
	delete m_budgetModel;
}

void GuestWindow::goStarterBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(1);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new StarterBudgetView(m_budgetModel, this, s));
}

void GuestWindow::goSummarySpending() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(6);
	SummarySpendingModel *m = new SummarySpendingModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void GuestWindow::goSummaryBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(7);
	SummaryBudgetModel *m = new SummaryBudgetModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void GuestWindow::goCompareAvg() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(10);
	CompareAvgModel *m = new CompareAvgModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void GuestWindow::goCompareBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(11);
	CompareBudgetModel *m = new CompareBudgetModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void GuestWindow::goSummaryOverspending() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(15);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new SummaryOverspendingView(this, s));
}

void GuestWindow::createToolBars() {
	QToolBar *toolbar = addToolBar("main toolbar");
	
	QIcon icon = m_featureModel->getIcon(1);
	QString tooltip = m_featureModel->getTooltip(1);	
	QAction *act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &GuestWindow::goStarterBudget);
	
	icon = m_featureModel->getIcon(6);
	tooltip = m_featureModel->getTooltip(6);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &GuestWindow::goSummarySpending);
	
	icon = m_featureModel->getIcon(7);
	tooltip = m_featureModel->getTooltip(7);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &GuestWindow::goSummaryBudget);
	
	icon = m_featureModel->getIcon(10);
	tooltip = m_featureModel->getTooltip(10);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &GuestWindow::goCompareAvg);
	
	icon = m_featureModel->getIcon(11);
	tooltip = m_featureModel->getTooltip(11);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &GuestWindow::goCompareBudget);
	
	icon = m_featureModel->getIcon(15);
	tooltip = m_featureModel->getTooltip(15);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &GuestWindow::goSummaryOverspending);
}

void GuestWindow::showOverspendingWarning() {
	QFrame *frame = new QFrame();
	QHBoxLayout *layout = new QHBoxLayout();
	QLabel *msg = new QLabel("Overspending!");
	frame->setObjectName("warningFrame");
	frame->setStyleSheet("#warningFrame { border: 2px solid red; }");
	frame->setLayout(layout);
	layout->addWidget(msg);
	statusBar()->addPermanentWidget(frame, 1);
	statusBar()->setContentsMargins(5, 3, 7, 5);
	statusBar()->setSizeGripEnabled(false);
}

void GuestWindow::hideOverspendingWarning() {
	delete statusBar();
	setStatusBar(NULL);
}
