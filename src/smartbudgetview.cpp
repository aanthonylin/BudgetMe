#include <iostream>
#include "smartbudgetview.h"

/*
 *
 */
SmartBudgetView::SmartBudgetView(SmartBudgetModel *model, QString title) : BaseView(title) {
	  m_model = model;
	  onButton = new QPushButton("On", this);
	  offButton = new QPushButton("Off", this);
	  
	  connect(onButton,  &QPushButton::released, this, &SmartBudgetView::handleSubmit);
	  connect(offButton,  &QPushButton::released, this, &SmartBudgetView::handleReset);
	  
	  addToView(onButton);
	  addToView(offButton);
}

SmartBudgetView::~SmartBudgetView(){}

void SmartBudgetView::handleSubmit() {
	// TODO: Submit user data to the model.
	m_model->setSmartBudgetOption(true);
	std::cout << m_model->getSmartBudgetOption() << std::endl;
	std::cout << "Submit from smart." << std::endl;
}

void SmartBudgetView::handleReset() {
	// TODO: Reset user input fields to default.
	m_model->setSmartBudgetOption(false);
	std::cout << "Resetting privacy." << std::endl;
	std::cout << m_model->getSmartBudgetOption() << std::endl;
}
