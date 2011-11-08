#ifndef QUERYSCHEME_H
#define QUERYSCHEME_H

#include "qst/qstglobal.h"

#include <QList>

class QueryScheme
{
public:

	typedef QList<Qst::QueryClause> QueryClauseList;

private:

	QueryClauseList _queryClauseList;

	int _currentClause;

public:

	QueryScheme();

	Qst::QueryClause nextClause();

	QueryScheme &operator<<(const Qst::QueryClause &clause);

};



#endif // QUERYSCHEME_H
