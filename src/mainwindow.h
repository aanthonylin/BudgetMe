/*
Author: Christopher F. S. Maligec
Date: 2021-10-31
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "featuremodel.h"
#include "budgetmemodel.h"
#include "simplebudgetmanager.h"
#include "SQLManager.h"
#include "warningmanager.h"
#include "LocalStorageManager.h"
#include "preferencesmodel.h"

/**
* @brief Authenticated user window.
*
* Window presented to a user that has logged in successfully.
*
* @author Christopher F. S. Maligec
*/
class MainWindow : public QMainWindow, public WarningManager
{
  Q_OBJECT
public:
	/**
	* Sets up the main GUI that will contain all the feature screens.
	*
	* @param storage: The LocalStorageManager used by the rest of the app.
	*/
  explicit MainWindow(LocalStorageManager *);
	
	/**
* Destructor.
*/
  ~MainWindow();
	
	/**
* Transition to the Generate Starter Budget screen.
*/
  void goStarterBudget();
	
	/**
* Transition to the Enter Transaction screen.
*/
	void goEnterTransaction();
	
	/**
* Transition to the Generate Preview Budget screen.
*/
	void goPreviewBudget();
	
	/**
* Transition to the Login Local screen.
*/
	void goLoginLocal();
	
	/**
* Transition to the Summary Spending screen.
*/
	void goSummarySpending();
	
	/**
* Transition to the Summary Budget screen.
*/
	void goSummaryBudget();
	
	/**
* Transition to the Summary Transaction screen.
*/
	void goSummaryTransaction();
	
	/**
* Transition to Summary Preview Budget screen.
*/
	void goSummaryPreview();
	
	/**
* Transition to the Compare to Average Canadian Spending screen.
*/
	void goCompareAvg();
	
	/**
* Transition to the Compare to Actual Budget screen.
*/
	void goCompareBudget();
	
	/**
* Transition to the Compare Preview Budget screen.
*/
	void goComparePreview();
	
	/**
* Transition to the Compare to Local Spending screen.
*/
	void goCompareLocal();
	
	/**
* Transition to the Compare to Server Spending screen.
*/
	void goCompareServer();
	
	/**
* Transition to the Summary Overspending screen.
*/
	void goSummaryOverspending();
	
	/**
* Transition to the Preferences screen.
*/
	void goPreferences();
	
	/**
* @brief Pops up a short overspending warning
*
* The warning will appear at the bottom of every screen until hidden.
*/
	void showOverspendingWarning();
	
	/**
* Hides overspending warning.
*/
	void hideOverspendingWarning();
	
   
//private slots:
  
private:
	FeatureModel *m_featureModel;
	BudgetMeModel *m_budgetModel;
	PreferencesModel *m_prefModel;
	
	/**
* Helper method to populate the main toolbar.
*/
	void createToolBars();
};
#endif // MAINWINDOW_H
