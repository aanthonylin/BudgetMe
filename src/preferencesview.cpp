#include <iostream>
#include "preferencesview.h"

PreferencesView::PreferencesView(PreferencesModel *model, QString title) : SubmitView(title){
	m_model = model;
	
	QGroupBox *firstBox = new QGroupBox(tr("Share Data?"));
	QVBoxLayout *vbox = new QVBoxLayout;
	on_data_button = new QRadioButton("On", this);
	off_data_button = new QRadioButton("Off", this);
	vbox->addWidget(on_data_button);
	vbox->addWidget(off_data_button);
	firstBox->setLayout(vbox);
	addToView(firstBox);
	
	QGroupBox *secondBox = new QGroupBox(tr("Smart Budget"));
	vbox = new QVBoxLayout;
	on_smart_button = new QRadioButton("On", this);
	off_smart_button = new QRadioButton("Off", this);
	vbox->addWidget(on_smart_button);
	vbox->addWidget(off_smart_button);
	secondBox->setLayout(vbox);
	addToView(secondBox);
	
	QGroupBox *thirdBox = new QGroupBox(tr("Overspending Warning"));
	vbox = new QVBoxLayout;
	on_warning_button = new QRadioButton("On", this);
	off_warning_button = new QRadioButton("Off", this);
	vbox->addWidget(on_warning_button);
	vbox->addWidget(off_warning_button);
	thirdBox->setLayout(vbox);
	addToView(thirdBox);
	
	QGroupBox *fourthBox = new QGroupBox(tr("Smart Spending"));
	vbox = new QVBoxLayout;
	on_spending_button = new QRadioButton("On", this);
	off_spending_button = new QRadioButton("Off", this);
	vbox->addWidget(on_spending_button);
	vbox->addWidget(off_spending_button);
	fourthBox->setLayout(vbox);
	addToView(fourthBox);
}


PreferencesView::~PreferencesView(){}

void PreferencesView::handleSubmit() {
	if (on_data_button->isChecked()){
		std::cout << "share: ON" <<std::endl;
		m_model->setSharingOption(true);
	}
	else if (off_data_button->isChecked()){	
		std::cout << "share: OFF" <<std::endl;
		m_model->setSharingOption(false);
	}
	
	if (on_smart_button->isChecked()){
		std::cout << "smart: ON" << std::endl;
		m_model->setSmartBudgetOption(true);
	}
	else if (off_smart_button->isChecked()){
		std::cout << "smart: OFF" << std::endl;
		m_model->setSmartBudgetOption(false);
	}
	
	if (on_warning_button->isChecked()){
		std::cout << "warning: ON" <<std::endl;
		m_model->setWarningOption(true);
	}
	else if (off_warning_button->isChecked()){
		std::cout << "warning: OFF" << std::endl;
		m_model->setWarningOption(false);
	}
	
	if (on_spending_button->isChecked()){
		std::cout << "spending: ON" <<std::endl;
		m_model->setSmartSpendingOption(true);
	}
	else if (off_spending_button->isChecked()){
		std::cout << "spending: OFF" <<std::endl;
		m_model->setSmartSpendingOption(false);
	}
}

void PreferencesView::handleReset() {
	//reset all radio buttons
	on_data_button->setAutoExclusive(false);
	on_data_button->setChecked(false);
	
	off_data_button->setAutoExclusive(false);
	off_data_button->setChecked(false);
	
	on_smart_button->setAutoExclusive(false);
	on_smart_button->setChecked(false);
	
	off_smart_button->setAutoExclusive(false);
	off_smart_button->setChecked(false);
	
	on_warning_button->setAutoExclusive(false);
	on_warning_button->setChecked(false);
	
	off_warning_button->setAutoExclusive(false);
	off_warning_button->setChecked(false);
	
	on_spending_button->setAutoExclusive(false);
	on_spending_button->setChecked(false);
	
	off_spending_button->setAutoExclusive(false);
	off_spending_button->setChecked(false);
	//turn auto exclusion back on 
	on_data_button->setAutoExclusive(true);
	off_data_button->setAutoExclusive(true);
	on_smart_button->setAutoExclusive(true);
	off_smart_button->setAutoExclusive(true);
	on_warning_button->setAutoExclusive(true);
	off_warning_button->setAutoExclusive(true);
	on_spending_button->setAutoExclusive(true);
	off_spending_button->setAutoExclusive(true);
}


