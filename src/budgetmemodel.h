/*
Author: Christopher F. S. Maligec
Date: 2021-11-03
*/

#ifndef BUDGETMEMODEL_H
#define BUDGETMEMODEL_H

#include <QString>
#include <QDate>
#include "LocalStorageManager.h"
#include "BudgetMeDataManager.h"
#include "budgetmanager.h"
#include "starterbudgetmodel.h"
#include "entertransactionmodel.h"
#include "previewbudgetmodel.h"
#include "budgetmeconstants.h"
#include "preferencesmodel.h"

class BudgetMeModel : public StarterBudgetModel, public EnterTransactionModel, public PreviewBudgetModel
{
public:
	BudgetMeModel(LocalStorageManager *, BudgetMeDataManager *, BudgetManager *, PreferencesModel *);
	~BudgetMeModel();
	int getCatNum();
	std::vector<QString> getCatNames();
	QString getCatName(int);
	int getIncome();
	std::vector<int> getEstSpending(BudgetMe::TimePeriod);
	std::vector<int> getAvgSpending(BudgetMe::TimePeriod);
	QString getIncomeQuestion();
	QString getEstimateQuestion();
	bool genStarterBudget(int, std::vector<int>);
	std::vector<int> getBudget(BudgetMe::TimePeriod);
	bool addTransaction(QString, int, QDate, int);
	void genPreviewBudget(QString, int, QDate, int);
	std::vector<int> getPreviewBudget(BudgetMe::TimePeriod);
	std::vector<int> getLocalSpending(BudgetMe::TimePeriod);
	std::vector<int> getServerSpending(BudgetMe::TimePeriod);
	std::vector<struct LocalStorageManager::transactionInfo> getTransactions(QDate, QDate);
	std::vector<int> getActSpendPerCat(QDate, QDate);
	std::vector<int> getActSpendPerDay(QDate, QDate);
private:
	LocalStorageManager *m_storageManager;
	BudgetMeDataManager *m_statsManager;
	BudgetManager *m_budgetManager;
	PreferencesModel *m_prefModel;
	int m_income;
	int m_avgIncome;
	std::vector<QString> m_catNames;
	std::vector<int> m_estSpending;
	std::vector<int> m_avgSpending;
	std::vector<int> m_budget;
	std::vector<int> m_previewBudget;
	std::vector<int> m_localSpending;
	std::vector<int> m_serverSpending;
	std::vector<int> scaleDown(std::vector<int>, int);
	std::vector<int> scaleUp(std::vector<int>, int);
};
#endif // BUDGETMEMODEL_H
