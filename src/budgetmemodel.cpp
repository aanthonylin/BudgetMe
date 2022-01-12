/*
Author: Christopher F. S. Maligec
Date: 2021-11-03
*/
#include<iostream>
#include "budgetmemodel.h"

using namespace std;
using namespace BudgetMe;

BudgetMeModel::BudgetMeModel(LocalStorageManager *storage, BudgetMeDataManager *stats, BudgetManager *budget, PreferencesModel *pref) {
	
	m_storageManager = storage;
	m_statsManager = stats;
	m_budgetManager = budget;
	m_prefModel = pref;
		
	// If StorageManager has StatsCan data cached, get it from there as it's faster.
	if(m_prefModel->getCanSave() && storage->isStatsCanDataSaved()) { 
		m_avgIncome = storage->getAverageAnnualIncome();
		m_avgSpending = storage->getAverageCanadianSpending();
		m_catNames = storage->getCategoryNames();
	}
	else { // Else, retrieve it from StatsCan and save it locally.
		m_avgIncome = stats->getAverageIncome();
		m_avgSpending = stats->getAverageSpending();
		m_avgSpending.erase(m_avgSpending.begin()); // Delete Total Spending from the start.
		m_catNames = stats->getShortNames();
		m_catNames.erase(m_catNames.begin()); // Delete "Total Spending" from the start.
		
		// Cache the values immediately.
		if(m_prefModel->getCanSave()) {
			storage->setAverageAnnualIncome(m_avgIncome);
			storage->setAverageCanadianSpending(m_avgSpending);
			storage->setCategoryNames(m_catNames);
			storage->setStatsCanDataSaved(true);
		}
	}
	
	// If StorageManager has user data, retrieve it.
	if(m_prefModel->getCanSave() && storage->isUserDataSaved()) {
		m_income = storage->getUserAnnualIncome();
		m_estSpending = storage->getEstimatedSpending();
		m_budget = storage->getUserBudget();
	}
	else { // Else, initialize it here.
		m_income = 0;
		m_estSpending = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		m_budget = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	}
	m_previewBudget = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	m_localSpending = {12320, 20200, 6450, 3490, 1350, 7740, 2780, 1390, 4530, 700, 170, 390, 2040, 15170, 4300, 2280, 1590};
	m_serverSpending = {10300, 18100, 4340, 1480, 3340, 13730, 780, 1880, 2620, 1690, 560, 180, 1530, 17160, 5290, 3180, 1380};
}

BudgetMeModel::~BudgetMeModel() {
	delete m_statsManager;
	delete m_budgetManager;
}

vector<QString> BudgetMeModel::getCatNames() {
	return m_catNames;
}

QString BudgetMeModel::getCatName(int catId) {
	return m_catNames[catId];
}

int BudgetMeModel::getIncome() {
	return m_income;
}

vector<int> BudgetMeModel::getEstSpending(TimePeriod time) {
	if(time == Yearly) {
		return m_estSpending;
	}
	else {
		return scaleDown(m_estSpending, time);
	}
}

vector<int> BudgetMeModel::getAvgSpending(TimePeriod time) {
	if(time == Yearly) {
		return m_avgSpending;
	}
	else {
		return scaleDown(m_avgSpending, time);
	}
}

QString BudgetMeModel::getIncomeQuestion(){
	return "What is your annual income?";
}

QString BudgetMeModel::getEstimateQuestion(){
	return "What is your estimated monthly spending for the following categories?";
}
	
bool BudgetMeModel::genStarterBudget(int userIncome, vector<int> estSpending){
	m_income = userIncome;
	m_estSpending = scaleUp(estSpending, 12);
	m_budget = m_budgetManager->starterBudget(m_avgSpending, m_avgIncome, m_income);
	if(m_prefModel->getCanSave()) {
		m_storageManager->setUserAnnualIncome(m_income);
		m_storageManager->setEstimatedSpending(m_estSpending);
		m_storageManager->setUserBudget(m_budget);
		m_storageManager->setUserDataSaved(true);
	}
	return m_budgetManager->isWithinBudget(m_estSpending, m_budget);
}

vector<int>  BudgetMeModel::getBudget(TimePeriod time){
	if(time == Yearly) {
		return m_budget;
	}
	else {
		return scaleDown(m_budget, time);
	}
}
	
bool BudgetMeModel::addTransaction(QString item, int value, QDate date, int catId) {
	double cap;
	vector<int> actSpending;
	QDate start;
	QDate end;
	struct LocalStorageManager::transactionInfo ti;
	ti.name = item;
	ti.cost = value;
	ti.date = date;
	ti.catid = catId;
	m_storageManager->saveTransaction(ti);
	
	// Do Smart Spending updates.
	if(m_prefModel->getSmartSpendingOption()) {
		
		// Get last 30 days' spending per category.
		end = QDate::currentDate();
		start = end.addDays(-30);
		actSpending = m_storageManager->getActualSpending(start, end);
		
		// Update estimated spending if actual spending has exceeded any category by a margin.
		cap = 1.1;
		m_estSpending = m_budgetManager->smartSpend(actSpending, m_estSpending, cap);
		m_storageManager->setEstimatedSpending(m_estSpending);
	}
	
	// Do Smart Budget updates based on potential change to estimated spending.
	if(m_prefModel->getSmartBudgetOption()) {
		cap = ((double)m_income) / m_avgIncome * 1.5; // NOTE: 1.5 should come from UserPreferences.
		m_budget = m_budgetManager->smartBudget(m_estSpending, m_avgSpending, m_budget, cap);
		m_storageManager->setUserBudget(m_budget);
	}
	return m_budgetManager->isWithinBudget(m_estSpending, m_budget);
}
	
void BudgetMeModel::genPreviewBudget(QString item, int value, QDate date, int catId){
	vector<int> prevSpending = m_estSpending;
	double cap = ((double)m_income) / m_avgIncome * 1.5; // NOTE: 1.5 should come from UserPreferences.
	prevSpending[catId] += value;
	m_previewBudget = m_budgetManager->smartBudget(prevSpending, m_avgSpending, m_budget, cap);
	cout << "Generating Preview Budget: " << item.toStdString() << value << date.toString().toStdString() << catId << endl;
}
	
vector<int>  BudgetMeModel::getPreviewBudget(TimePeriod time){
	if(time == Yearly) {
		return m_previewBudget;
	}
	else {
		return scaleDown(m_previewBudget, time);
	}
}
	
vector<int>  BudgetMeModel::getLocalSpending(TimePeriod time){
	if(time == Yearly) {
		return m_localSpending;
	}
	else {
		return scaleDown(m_localSpending, time);
	}
}

vector<int> BudgetMeModel::getServerSpending(TimePeriod time){
	if(time == Yearly) {
		return m_serverSpending;
	}
	else {
		return scaleDown(m_serverSpending, time);
	}
}

int BudgetMeModel::getCatNum() {
	return m_catNames.size();
}

vector<struct LocalStorageManager::transactionInfo> BudgetMeModel::getTransactions(QDate start, QDate end) {
	return m_storageManager->getTransactions(start, end);
}

vector<int> BudgetMeModel::getActSpendPerCat(QDate start, QDate end) {
	return m_storageManager->getActualSpending(start, end);
}

vector<int> BudgetMeModel::getActSpendPerDay(QDate start, QDate end) {
	return m_storageManager->getDailySpending(start, end);
}


vector<int>  BudgetMeModel::scaleDown(vector<int> v, int factor){
	int len = v.size();
	for( int i = 0; i < len; i++){
		v[i] /= factor; 
	}
	return v;
}

vector<int>  BudgetMeModel::scaleUp(vector<int> v, int factor){
	int len = v.size();
	for( int i = 0; i < len; i++){
		v[i] *= factor; 
	}
	return v;
}