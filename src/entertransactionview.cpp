#include <vector>
#include <QFormLayout>
#include "entertransactionview.h"

using namespace std;
/*
 *
 */
EnterTransactionView::EnterTransactionView(EnterTransactionModel *model, WarningManager *warnings, QString title) : SubmitView(title) {
	m_model = model;
	m_warnings = warnings;
	costLine = new QLineEdit;
	qtyLine = new QLineEdit;
	descLine = new QLineEdit;
	dateLine = new QDateEdit(QDate::currentDate());
	dateLine->setDisplayFormat("yyyy.MM.dd");
	dateLine->setCalendarPopup(true);
	
	catCombo = new QComboBox;
	vector<QString> catNames = m_model->getCatNames();
	int len = catNames.size();
	for (int i = 0; i < len; i++){
		catCombo->addItem(catNames[i]);
	}
		
	QFormLayout *txLayout = new QFormLayout;
	txLayout->addRow(tr("Item Desc:"), descLine);
	txLayout->addRow(tr("Quantity:"), qtyLine);
	txLayout->addRow(tr("Total Cost:"), costLine);
	txLayout->addRow(tr("Purchase Date:"), dateLine);
	txLayout->addRow(tr("Category:"), catCombo);
	addToView(txLayout);	
}	

EnterTransactionView::~EnterTransactionView(){}

void EnterTransactionView::handleSubmit() {
	QString item = descLine->text();
	int cost = costLine->text().toDouble();
	QDate date = dateLine->date();
	int catId = catCombo->currentIndex();
	handleReset();
	
	// Make transaction and display OverSpending warning if necessary.
	bool isOK = m_model->addTransaction(item, cost, date, catId);
	if(!isOK) {
		m_warnings->showOverspendingWarning();
	}
}

void EnterTransactionView::handleReset() {
	descLine->clear();
	qtyLine->clear();
	costLine->clear();
	dateLine->setDate(QDate::currentDate());
	catCombo->setCurrentIndex(0);
}
