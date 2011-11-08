#ifndef QUERYSCHEME_H
#define QUERYSCHEME_H

#include "qst/qstglobal.h"

#include <QList>

class QueryScheme
{

private:

	Qst::QueryClauseList _queryClauseList;

	int _currentClause;

public:

	QueryScheme();

	Qst::QueryClause nextClause();

	QueryScheme &operator<<(const Qst::QueryClause &clause);

};



#endif // QUERYSCHEME_H
