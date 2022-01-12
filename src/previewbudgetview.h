#ifndef PREVIEWBUDGETVIEW_H
#define PREVIEWBUDGETVIEW_H

#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include "submitview.h"
#include "previewbudgetmodel.h"

class PreviewBudgetView : public SubmitView
{
  Q_OBJECT
public:
  explicit PreviewBudgetView(PreviewBudgetModel *, QString);
  ~PreviewBudgetView();
	void handleSubmit();
	void handleReset();
private:
	PreviewBudgetModel *m_model;
	QLineEdit *costLine;
	QLineEdit *qtyLine;
	QLineEdit *descLine;
	QDateEdit *dateLine;
	QComboBox *catCombo;
 };
#endif // PREVIEWBUDGETVIEW_H
