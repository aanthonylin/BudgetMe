#ifndef SMARTBUDGETVIEW_H
#define SMARTBUDGETVIEW_H

#include <QPushButton>
#include "baseview.h"
#include "smartbudgetmodel.h"

class SmartBudgetView : public BaseView
{
  Q_OBJECT
public:
  explicit SmartBudgetView(SmartBudgetModel *, QString);
  ~SmartBudgetView();
	void handleSubmit();
	void handleReset();
private:
	SmartBudgetModel *m_model;
	QPushButton *onButton;
	QPushButton *offButton;
 };
#endif // SMARTBUDGETVIEW_H
