#ifndef REPORTVIEW_H
#define REPORTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include "baseview.h"
#include "ReportModel.h"

class ReportView : public BaseView
{
	public:
		ReportView(ReportModel *, QString);
		virtual ~ReportView();
		void showReport();
	private:
		QWidget *centralWidget;
		QTextEdit *reportBox;
		ReportModel *model;
};

#endif
