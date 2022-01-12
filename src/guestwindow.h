#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include "featuremodel.h"
#include "budgetmemodel.h"
#include "warningmanager.h"
 
/**
* @brief Guest user window.
*
* Window presented to a user that does not want their data saved on the device.
*
* @author Christopher F. S. Maligec
*/
class GuestWindow : public QMainWindow, public WarningManager
{
  Q_OBJECT
public:
  explicit GuestWindow();
  ~GuestWindow();
  void goStarterBudget();
	void goSummarySpending();
	void goSummaryBudget();
	void goCompareAvg();
	void goCompareBudget();
	void goSummaryOverspending();
	void showOverspendingWarning();
	void hideOverspendingWarning();
private:
	FeatureModel *m_featureModel;
	BudgetMeModel *m_budgetModel;
	PreferencesModel *m_prefModel;
	void createToolBars();
};
#endif // GUESTWINDOW_H
