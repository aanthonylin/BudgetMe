#include <QLabel>
#include <QFont>
#include "baseview.h"

BaseView::BaseView(QString title) {
	QHBoxLayout *mid = new QHBoxLayout();
	QLabel *label = new QLabel(title);
	QFont font = label->font();
	QFrame *line = new QFrame();
	
	m_outer = new QVBoxLayout();
	m_center = new QVBoxLayout();
	setLayout(m_outer);
	
	// Set up the title.
	font.setPointSize(16);
	label->setFont(font);
	m_outer->addWidget(label);
	
	// Add a line under the title.
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
	m_outer->addWidget(line);
	
	// Finish setting up the m_outer layout.
	m_outer->addStretch();
	m_outer->addLayout(mid);
	m_outer->addStretch();
	
	// Set up the mid layout.
	mid->addStretch();
	mid->addLayout(m_center);
	mid->addStretch();
}

BaseView::~BaseView(){}

void BaseView::addToView(QWidget *widget) {
	m_center->addWidget(widget);
}

void BaseView::removeFromView(QWidget *widget) {
	m_center->removeWidget(widget);
	delete widget;
}

void BaseView::addToView(QLayout *layout){
	m_center->addLayout(layout);
}

void BaseView::addToFooter(QWidget *widget) {
	m_outer->addWidget(widget);
}

void BaseView::addToFooter(QLayout *layout){
	m_outer->addLayout(layout);
}
