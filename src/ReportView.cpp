/*
 * Author: Hazem Sabsabi
 * Date: 08/11/2021
 */
#include <iostream>
#include "ReportView.h"

ReportView::ReportView(ReportModel *model, QString title) : BaseView(title) {
	this->model = model;
}

ReportView::~ReportView() {
	delete model;
}

void ReportView::showReport() {
	std::cout << "Place Holder Text" << std::endl;
}
