#include <QPushButton>
#include "summaryoverspendingview.h"

SummaryOverspendingView::SummaryOverspendingView(WarningManager *manager, QString title) : BaseView(title) {
	QPushButton *fixWarning = new QPushButton("Fix Overspending");
	m_warnings = manager;
	addToView(fixWarning);
	connect(fixWarning, &QPushButton::released, this, &SummaryOverspendingView::handleFix);
}

SummaryOverspendingView::~SummaryOverspendingView() {}

void SummaryOverspendingView::handleFix() {
	// TODO: Actually fix the warning.
	m_warnings->hideOverspendingWarning();
}