/*
Author: Christopher F. S. Maligec
Date: 2021-10-31
*/
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QStatusBar>

#include "mainwindow.h"
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

MainWindow::MainWindow(LocalStorageManager *storage) {
	BudgetMeDataManager *statsManager = new BudgetMeDataManager();
	SimpleBudgetManager *budgetManager = new SimpleBudgetManager();
	
	m_featureModel = new FeatureModel();
	m_prefModel = new PreferencesManager();
	m_budgetModel = new BudgetMeModel(storage, statsManager, budgetManager, m_prefModel);

	setWindowTitle("BudgetMe");
	createToolBars();
	resize(1000, 700);
	
	m_featureModel->setSelectedFeature(1);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new StarterBudgetView(m_budgetModel, this, s));
}

MainWindow::~MainWindow(){
	delete m_featureModel;
	delete m_budgetModel;
	delete m_prefModel;
}

void MainWindow::goStarterBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(1);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new StarterBudgetView(m_budgetModel, this, s));
}

void MainWindow::goEnterTransaction() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(2);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new EnterTransactionView(m_budgetModel, this, s));
}

void MainWindow::goPreviewBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(4);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new PreviewBudgetView(m_budgetModel, s));
}

void MainWindow::goLoginLocal() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(5);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new LoginLocalView(s));
}

void MainWindow::goSummarySpending() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(6);
	SummarySpendingModel *m = new SummarySpendingModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goSummaryBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(7);
	SummaryBudgetModel *m = new SummaryBudgetModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goSummaryTransaction() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(8);
	SummaryTransactionModel *m = new SummaryTransactionModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new SummaryTransactionView(m, s));
}

void MainWindow::goSummaryPreview() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(9);
	SummaryPreviewModel *m = new SummaryPreviewModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goCompareAvg() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(10);
	CompareAvgModel *m = new CompareAvgModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}


void MainWindow::goCompareBudget() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(11);
	CompareBudgetModel *m = new CompareBudgetModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goComparePreview() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(12);
	ComparePreviewModel *m = new ComparePreviewModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goCompareLocal() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(13);
	CompareLocalModel *m = new CompareLocalModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goCompareServer() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(14);
	CompareServerModel *m = new CompareServerModel(m_budgetModel);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new GraphView(m, s));
}

void MainWindow::goSummaryOverspending() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(15);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new SummaryOverspendingView(this, s));
}

void MainWindow::goPreferences() {
	delete centralWidget();
	m_featureModel->setSelectedFeature(16);
	QString s = m_featureModel->getSelectedTitle();
	setCentralWidget(new PreferencesView(m_prefModel, s));
}

void MainWindow::createToolBars() {
	QToolBar *toolbar = addToolBar("main toolbar");
	
	QIcon icon = m_featureModel->getIcon(1);
	QString tooltip = m_featureModel->getTooltip(1);	
	QAction *act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goStarterBudget);
		
	icon = m_featureModel->getIcon(2);
	tooltip = m_featureModel->getTooltip(2);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goEnterTransaction);
		
	icon = m_featureModel->getIcon(4);
	tooltip = m_featureModel->getTooltip(4);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goPreviewBudget);
	
	// Login Local. featureID = 5.
	
	icon = m_featureModel->getIcon(6);
	tooltip = m_featureModel->getTooltip(6);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goSummarySpending);
	
	icon = m_featureModel->getIcon(7);
	tooltip = m_featureModel->getTooltip(7);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goSummaryBudget);
	
	icon = m_featureModel->getIcon(8);
	tooltip = m_featureModel->getTooltip(8);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goSummaryTransaction);
	
	icon = m_featureModel->getIcon(9);
	tooltip = m_featureModel->getTooltip(9);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goSummaryPreview);
	
	icon = m_featureModel->getIcon(10);
	tooltip = m_featureModel->getTooltip(10);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goCompareAvg);
	
	icon = m_featureModel->getIcon(11);
	tooltip = m_featureModel->getTooltip(11);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goCompareBudget);
	
	icon = m_featureModel->getIcon(12);
	tooltip = m_featureModel->getTooltip(12);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goComparePreview);
	
	icon = m_featureModel->getIcon(13);
	tooltip = m_featureModel->getTooltip(13);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goCompareLocal);
	
	icon = m_featureModel->getIcon(14);
	tooltip = m_featureModel->getTooltip(14);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goCompareServer);
	
	icon = m_featureModel->getIcon(15);
	tooltip = m_featureModel->getTooltip(15);	
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goSummaryOverspending);
	
	icon = m_featureModel->getIcon(16);
	tooltip = m_featureModel->getTooltip(16);
	act = toolbar->addAction(icon, tooltip);
	connect(act, &QAction::triggered, this, &MainWindow::goPreferences);
}

void MainWindow::showOverspendingWarning() {
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

void MainWindow::hideOverspendingWarning() {
	delete statusBar();
	setStatusBar(NULL);
}
