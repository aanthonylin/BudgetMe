#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include "submitview.h"

SubmitView::SubmitView(QString title) : BaseView(title){
	QFrame *line = new QFrame();
	QHBoxLayout *bottom = new QHBoxLayout();
	QPushButton *reset= new QPushButton("Reset");
	QPushButton *submit= new QPushButton("Submit");
	
	// Add a line above footer.
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
	addToFooter(line);
	
	// Construct the footer and add buttons.
	bottom->addStretch();
	bottom->addWidget(reset);
	bottom->addWidget(submit);
	bottom->addStretch();
	addToFooter(bottom);
	
	connect(reset, &QPushButton::released, this, &SubmitView::handleReset);
	connect(submit, &QPushButton::released, this, &SubmitView::handleSubmit);
}

SubmitView::~SubmitView() {}

void SubmitView::handleReset() {}

void SubmitView::handleSubmit() {}
