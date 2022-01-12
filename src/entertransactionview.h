#ifndef ENTERTRANSACTIONVIEW_H
#define ENTERTRANSACTIONVIEW_H

#include <QLineEdit>
#include <QString>
#include <QComboBox>
#include <QDateEdit>
#include "submitview.h"
#include "entertransactionmodel.h"
#include "warningmanager.h"
 
class EnterTransactionView : public SubmitView
{
  Q_OBJECT
public:
  explicit EnterTransactionView(EnterTransactionModel *, WarningManager *, QString);
  ~EnterTransactionView();
	void handleSubmit();
	void handleReset();
private:
	EnterTransactionModel *m_model;
	WarningManager *m_warnings;
	QComboBox *catCombo;
	QLineEdit *costLine;
	QLineEdit *qtyLine;
	QLineEdit *descLine;
	QDateEdit *dateLine;
 };
#endif // ENTERTRANSACTIONVIEW_H
