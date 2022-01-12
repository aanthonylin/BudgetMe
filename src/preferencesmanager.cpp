#include "preferencesmanager.h"

PreferencesManager::PreferencesManager(bool canSave) {
	m_canSave = canSave;
	m_isSmartSpendingEnabled = true;
	m_isSmartBudgetEnabled = true;
	m_isSharingEnabled = false;
	m_isWarningEnabled = true;
}

PreferencesManager::~PreferencesManager() {}

bool PreferencesManager::getCanSave() {
	return m_canSave;
}

bool PreferencesManager::getSmartSpendingOption() {
	return m_isSmartSpendingEnabled;
}

void PreferencesManager::setSmartSpendingOption(bool enabled) {
	m_isSmartSpendingEnabled = enabled;
}

bool PreferencesManager::getSmartBudgetOption() {
	return m_isSmartBudgetEnabled;
}

void PreferencesManager::setSmartBudgetOption(bool enabled) {
	m_isSmartBudgetEnabled = enabled;
}

bool PreferencesManager::getSharingOption() {
	return m_isSharingEnabled;
}

void PreferencesManager::setSharingOption(bool enabled) {
	m_isSharingEnabled = enabled;
}

bool PreferencesManager::getWarningOption() {
	return m_isWarningEnabled;
}

void PreferencesManager::setWarningOption(bool enabled) {
	m_isWarningEnabled = enabled;
}