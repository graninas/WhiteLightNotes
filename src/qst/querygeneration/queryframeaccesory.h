#ifndef QUERYFRAMEACCESORY_H
#define QUERYFRAMEACCESORY_H

#include <QString>
#include <QMap>

class QueryAccessory
{
private:

	QString	_clauseWord;
	QString _subqueryBrackets;

public:
	QueryAccessory(const QString &clauseWord = "",
				   const QString &subqueryBrackets = "");

	QString clauseWord() const;
	QString leftSubqueryBracket() const;
	QString rightSubqueryBracket() const;
};

#endif // QUERYFRAMEACCESORY_H
