#ifndef PREFERENCESVIEW_H
#define PREFERENCESVIEW_H

#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include "submitview.h"
#include "preferencesmodel.h"


class PreferencesView : public SubmitView
{
	Q_OBJECT
public:
	explicit PreferencesView(PreferencesModel*, QString);
	~PreferencesView();
	void handleSubmit();
	void handleReset();
private:
	PreferencesModel *m_model;
	QVBoxLayout *vbox;
	QRadioButton *on_data_button;
	QRadioButton *off_data_button;
	QRadioButton *on_warning_button;
	QRadioButton *off_warning_button;
	QRadioButton *on_smart_button;
	QRadioButton *off_smart_button;
	QRadioButton *on_spending_button;
	QRadioButton *off_spending_button;
	

};
#endif // PREFERENCESVIEW_H


