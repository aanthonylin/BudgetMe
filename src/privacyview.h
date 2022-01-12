#ifndef PRIVACYVIEW_H
#define PRIVACYVIEW_H

#include "submitview.h"
#include "privacysettingsmodel.h"
#include <QComboBox>
#include <QWidget>
 
class PrivacyView : public SubmitView
{
  Q_OBJECT
public:
  explicit PrivacyView(PrivacySettingsModel *, QString);
  ~PrivacyView();
	void handleSubmit();
	void handleReset();
private:
	PrivacySettingsModel *m_model;
	QComboBox *privacyCombo;	
};
#endif // PRIVACYVIEW_H
