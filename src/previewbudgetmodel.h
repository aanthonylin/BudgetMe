#ifndef PREVIEWBUDGETMODEL_H
#define PREVIEWBUDGETMODEL_H

#include <vector>
#include <QString>


class PreviewBudgetModel
{
public:
	virtual ~PreviewBudgetModel(){}
	virtual std::vector<QString> getCatNames() = 0; 
	virtual void genPreviewBudget(QString, int, QDate, int) = 0;
};
#endif // PREVIEWBUDGETMODEL_H
