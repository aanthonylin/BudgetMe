#include <QLabel>
#include <QFormLayout>
#include "starterbudgetview.h"
#include "budgetmeconstants.h"

using namespace std;
/*
 *  The initial budget created for the user - starter budget
 *  user inputs yearly income / estimated monthly spending per category to output a relevant budget
 */
StarterBudgetView::StarterBudgetView(StarterBudgetModel *model, WarningManager *warnings, QString title) : SubmitView(title) {
	m_model = model;
	m_warnings = warnings;		
	m_income = new QLineEdit;
	QFormLayout *starterLayout = new QFormLayout;
	vector<QString> catNames = m_model->getCatNames();
	int len = catNames.size();
	QString labelText = m_model->getIncomeQuestion();
	starterLayout->addRow(labelText, m_income);
	labelText = m_model->getEstimateQuestion();
	starterLayout->addRow(new QLabel(labelText));
	for (int i = 0; i < len; i++){
		labelText = catNames[i] + ":";
		m_inputs.push_back(new QLineEdit);
		starterLayout->addRow(labelText, m_inputs[i]);
	}
	addToView(starterLayout);
	repopulateFromUserData();
}

StarterBudgetView::~StarterBudgetView(){}

void StarterBudgetView::handleSubmit() {
	int income = m_income->text().toDouble();
	
	vector<int> estSpending;
	int len = m_inputs.size();
	int val;
	for(int i = 0; i < len; i++) {
		val = m_inputs[i]->text().toDouble();
		estSpending.push_back(val);
	}
	
	bool isOK = m_model->genStarterBudget(income, estSpending);
	if(!isOK) {
		m_warnings->showOverspendingWarning();
	}
}

void StarterBudgetView::handleReset() {
	int len = m_inputs.size();
	m_income->clear();
	for(int i = 0; i < len; i++) {
		m_inputs[i]->clear();
	}
}

void StarterBudgetView::repopulateFromUserData() {
	int val = m_model->getIncome();
	QString s;
	if(val > 0){
		s.setNum(val);
		m_income->setText(s);
	}
	
	vector<int> spend = m_model->getEstSpending(BudgetMe::Monthly);
	int len = spend.size();
	for(int i = 0; i < len; i++) {
		val = spend[i];
		if(val> 0) {
			s.setNum(val);
			m_inputs[i]->setText(s);
		}
	}
}
