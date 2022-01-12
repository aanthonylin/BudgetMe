#ifndef SUBMITVIEW_H
#define SUBMITVIEW_H

#include <QString>
#include "baseview.h"

class SubmitView : public BaseView
{
  Q_OBJECT
public:
  explicit SubmitView(QString);
  virtual ~SubmitView();
	virtual void handleReset();
	virtual void handleSubmit();
	

};
#endif // SUBMITVIEW_H