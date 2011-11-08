#include "queryframeaccesory.h"

QueryAccessory::QueryAccessory(const QString &clauseWord,
							   const QString &subqueryBrackets)
	:
	_clauseWord(clauseWord),
	_subqueryBrackets(subqueryBrackets)
{
	if (!subqueryBrackets.isEmpty())
	{
		Q_ASSERT(subqueryBrackets.count() == 2);
	}
}

QString QueryAccessory::clauseWord() const
{
	return _clauseWord;
}

QString QueryAccessory::leftSubqueryBracket() const
{
	if (_subqueryBrackets.count() > 0)
		return _subqueryBrackets[0];
return QString();
}

QString QueryAccessory::rightSubqueryBracket() const
{
	if (_subqueryBrackets.count() > 1)
		return _subqueryBrackets[1];
return QString();
}


