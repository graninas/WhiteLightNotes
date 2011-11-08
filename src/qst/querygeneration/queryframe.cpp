#include "queryframe.h"

#include <QDebug>

using namespace Qst;

QueryFrame::QueryFrame()
	:
	  _token(""),
	  _leftToken(""),
	  _rightToken(""),
	  _partClause(NoClause)
{
}

QueryFrame::QueryFrame(const QString &token,
					   const QString &leftToken,
					   const QString &rightToken)
   :
	 _token(token),
	 _leftToken(leftToken),
	 _rightToken(rightToken),
	 _partClause(NoClause)
{
}

QueryFrame::QueryFrame(const QString &leftToken,
					   const QString &rightToken,
					   const QueryFrameList &frameList)
   :
	 _token(""),
	 _frameList(frameList),
	 _leftToken(leftToken),
	 _rightToken(rightToken),
	 _partClause(NoClause)
{
}

QueryFrame *QueryFrame::appendFrame(const QueryFrame &frame)
{
	_frameList.append(frame);

	return &_frameList[_frameList.count()-1];
}

QString QueryFrame::toString() const
{
QString res;

	res = _leftToken;

	res += _token;

	for (int i = 0; i < _frameList.count(); ++i)
		res += _frameList[i].toString();

	res += _rightToken;
return res;
}

QueryFrame QueryFrame::part(const Qst::QueryClause &clause) const
{
	if (this->_partClause == clause)
		return (*this);

	foreach (QueryFrame frame, _frameList)
		return frame.part(clause);

	return QueryFrame();
}

ClauseFrameMap QueryFrame::parts(const Qst::QueryClauses &clauses) const
{
	ClauseFrameMap map;

	QList<QueryClause> clauseList;
	clauseList << ClauseSelect       << ClauseFrom
			   << ClauseLeftJoin     << ClauseRightJoin
			   << ClauseFullJoin     << ClauseInnerJoin
			   << ClauseWhere        << ClauseInsert
			   << ClauseUpdate       << ClauseOrderBy
			   << ClauseGroupBy      << ClauseParameters
			   << ClauseHaving       << ClauseValues
			   << ClauseSet          << ClauseDelete
			   << ClauseExecute      << ClauseOn
			   << UserDefinedClauses;

	foreach(QueryClause clause, clauseList)
	{
		if (clauses.testFlag(clause))
			map.insert(clause, part(clause));
	}

	return map;
}

void QueryFrame::clear()
{
	_token.clear();;
	_frameList.clear();
	_leftToken.clear();
	_rightToken.clear();
}

void QueryFrame::setPartClause(const Qst::QueryClause &clause)
{
	_partClause = clause;
}

QString QueryFrame::token() const
{
	return _token;
}

QString QueryFrame::leftToken() const
{
	return _leftToken;
}

QString QueryFrame::rightToken() const
{
	return _rightToken;
}

QueryFrameList QueryFrame::frameList() const
{
	return _frameList;
}

QueryFrame &QueryFrame::operator<<(const QueryFrame &frame)
{
	appendFrame(frame);

	return *this;
}

QueryFrame &QueryFrame::operator<<(const QString &token)
{
	appendFrame(QueryFrame(token, "", ""));

	return *this;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QueryFrame &f)
{
#ifndef Q_BROKEN_DEBUG_STREAM
	dbg.nospace() << "QueryFrame(leftToken = " << f.leftToken();
	dbg.nospace() << ", token = " << f.token();
	dbg.nospace() << ", rightToken = " << f.rightToken();
	dbg.nospace() << ", frameList = " << f.frameList() << ").";

	return dbg.space();
#else
	qWarning("This compiler doesn't support streaming QueryFrame to QDebug");
	return dbg;
	Q_UNUSED(f);
#endif
}
#endif
