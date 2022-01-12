#ifndef SUMMARYOVERSPENDINGVIEW_H
#define SUMMARYOVERSPENDINGVIEW_H

#include <QString>
#include "baseview.h"
#include "warningmanager.h"

class SummaryOverspendingView : public BaseView
{
  Q_OBJECT
public:
  explicit SummaryOverspendingView(WarningManager *, QString);
  virtual ~SummaryOverspendingView();
	void handleFix();
private:
	WarningManager *m_warnings;
};
#endif // SUMMARYOVERSPENDINGVIEW_H