#ifndef STARTERBUDGETVIEW_H
#define STARTERBUDGETVIEW_H

#include <QLineEdit>
#include "submitview.h"
#include "starterbudgetmodel.h"
#include "warningmanager.h"

class StarterBudgetView : public SubmitView
{
  Q_OBJECT
public:
  explicit StarterBudgetView(StarterBudgetModel *, WarningManager *, QString);
  ~StarterBudgetView();
	void handleSubmit();
	void handleReset();
private:
	StarterBudgetModel *m_model;
	WarningManager *m_warnings;
	QLineEdit *m_income;
	std::vector<QLineEdit *> m_inputs;
	void repopulateFromUserData();
};
#endif // STARTERBUDGETVIEW_H
