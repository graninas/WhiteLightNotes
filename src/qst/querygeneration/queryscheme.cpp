#include "queryscheme.h"

using namespace Qst;

QueryScheme::QueryScheme()
	:
	_currentClause(-1)
{
}

Qst::QueryClause QueryScheme::nextClause()
{
	++_currentClause;
	return _queryClauseList.value(_currentClause, Qst::NoClause);
}

QueryScheme &QueryScheme::operator<<(const QueryClause &clause)
{
	_queryClauseList << clause;
	return *this;
}
