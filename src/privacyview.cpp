#include <iostream>
#include <QLabel>
#include "privacyview.h"

PrivacyView::PrivacyView(PrivacySettingsModel *model, QString title) : SubmitView(title) {
	m_model = model;
	
	privacyCombo = new QComboBox;
	privacyCombo->addItem(tr("Full"));
	privacyCombo->addItem(tr("Medium"));
	privacyCombo->addItem(tr("Low")); 
	
	addToView(new QLabel("Choose your privacy settings:"));
	addToView(privacyCombo);
}

PrivacyView::~PrivacyView(){}

void PrivacyView::handleSubmit() {
	// TODO: Submit user data to the model.
	std::cout << "Submitting privacy." << std::endl;
}

void PrivacyView::handleReset() {
	// TODO: Reset user input fields to default.
	std::cout << "Resetting privacy." << std::endl;
}
