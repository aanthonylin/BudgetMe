#include "featuremodel.h"

FeatureModel::FeatureModel() {
	m_selectedFeature = 0;
	initFeatureIcons();
	initFeatureNames();
}

FeatureModel::~FeatureModel() {}

QIcon FeatureModel::getIcon(int featureId) {
	return m_featureIcons[featureId];
}

QString FeatureModel::getTooltip(int featureId) {
	return m_featureNames[featureId];
}

QString FeatureModel::getSelectedTitle() {
	return m_featureNames[m_selectedFeature];
}

int FeatureModel::getSelectedFeature() {
	return m_selectedFeature;
}

void FeatureModel::setSelectedFeature(int featureId) {
	m_selectedFeature = featureId;
}

void FeatureModel::initFeatureNames() {
	m_featureNames[0] = "Privacy Settings";
	m_featureNames[1] = "Starter Budget";
	m_featureNames[2] =	"Enter Transaction";
	m_featureNames[3] =	"Smart Budget";
	m_featureNames[4] = "Preview Budget";
	m_featureNames[5] = "Local Login";
	m_featureNames[6] = "Spending Summary";
	m_featureNames[7] = "Budget Summary";
	m_featureNames[8] = "Transaction Summary";
	m_featureNames[9] = "Preview Summary";
	m_featureNames[10] = "Average Spending Comparison";
	m_featureNames[11] = "Budget Comparison";
	m_featureNames[12] = "Preview Comparison";
	m_featureNames[13] = "Local Comparison";
	m_featureNames[14] = "Server Comparison";
	m_featureNames[15] = "Overspending Summary";
	m_featureNames[16] = "Preferences";
}

void FeatureModel::initFeatureIcons() {
	m_featureIcons[0] = QIcon(":/priv");
	m_featureIcons[1] = QIcon(":/start");
	m_featureIcons[2] =	QIcon(":/transac");
	m_featureIcons[3] =	QIcon(":/smart");
	m_featureIcons[4] = QIcon(":/prev");
	m_featureIcons[5] = QIcon(":/logloc");
	m_featureIcons[6] = QIcon(":/sumspend");
	m_featureIcons[7] = QIcon(":/sumbud");
	m_featureIcons[8] = QIcon(":/sumtransac");
	m_featureIcons[9] = QIcon(":/sumbud");
	m_featureIcons[10] = QIcon(":/sumbud");
	m_featureIcons[11] = QIcon(":/sumbud");
	m_featureIcons[12] = QIcon(":/sumbud");
	m_featureIcons[13] = QIcon(":/sumbud");
	m_featureIcons[14] = QIcon(":/sumbud");
	m_featureIcons[15] = QIcon(":/sumbud");
	m_featureIcons[16] = QIcon(":/priv");
}

