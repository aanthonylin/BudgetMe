#ifndef ENTERTRANSACTIONMODEL_H
#define ENTERTRANSACTIONMODEL_H

#include <vector>
#include <QString>

class EnterTransactionModel
{
public:
	virtual ~EnterTransactionModel(){}
	virtual std::vector<QString> getCatNames() = 0;
	virtual bool addTransaction(QString, int, QDate, int) = 0;
};
#endif // ENTERTRANSACTIONMODEL_H
