#include <vector>
#include <QFormLayout>
#include "previewbudgetview.h"

using namespace std;
/*
 *
 */
PreviewBudgetView::PreviewBudgetView(PreviewBudgetModel *model, QString title) : SubmitView(title) {
	m_model = model;
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
	
	QFormLayout *budgetLayout = new QFormLayout;
	budgetLayout->addRow(tr("Item Desc:"), descLine);
	budgetLayout->addRow(tr("Quantity:"), qtyLine);
	budgetLayout->addRow(tr("Total Cost:"), costLine);
	budgetLayout->addRow(tr("Purchase Date:"), dateLine);
	budgetLayout->addRow(tr("Category:"), catCombo);
	addToView(budgetLayout);
}

PreviewBudgetView::~PreviewBudgetView(){}

void PreviewBudgetView::handleSubmit() {
	QString item = descLine->text();
	int cost = costLine->text().toDouble();
	QDate date = dateLine->date();
	int catId = catCombo->currentIndex();
	handleReset();
	m_model->genPreviewBudget(item, cost, date, catId);
}

void PreviewBudgetView::handleReset() {
	descLine->clear();
	qtyLine->clear();
	costLine->clear();
	dateLine->setDate(QDate::currentDate());
	catCombo->setCurrentIndex(0);
}
