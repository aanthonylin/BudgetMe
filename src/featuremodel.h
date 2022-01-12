#ifndef FEATUREMODEL_H
#define FEATUREMODEL_H

#include <QIcon>
#include "privacysettingsmodel.h"
#include "mainwindowmodel.h"
 
class FeatureModel : public MainWindowModel {

public:
	static const int NUM_FEATURES = 17;
	explicit FeatureModel();
	~FeatureModel();
	QIcon getIcon(int);
	QString getTooltip(int);
	QString getSelectedTitle();
	int getSelectedFeature();
	void setSelectedFeature(int);
	
private:
	QIcon m_featureIcons[NUM_FEATURES];
	QString m_featureNames[NUM_FEATURES];
	int m_selectedFeature;
	void initFeatureIcons();
	void initFeatureNames();
};
#endif //FEATUREMODEL_H
