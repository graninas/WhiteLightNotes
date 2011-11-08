#ifndef QUERYFRAME_H
#define QUERYFRAME_H

#include <QString>
#include <QList>
#include <QMap>

#include "qst/qstglobal.h"

#include "queryframeaccesory.h"
#include "queryscheme.h"

class QueryFrame;

typedef QList<QueryFrame> QueryFrameList;
typedef QMap<Qst::QueryClause, QueryFrame> ClauseFrameMap;

class QueryFrame
{
private:

	QString			_token;
	QueryFrameList	_frameList;

	QString			_leftToken;
	QString			_rightToken;

	Qst::QueryClause _partClause;

public:
	QueryFrame();

	QueryFrame(const QString &token,
			   const QString &leftToken,
			   const QString &rightToken);

	QueryFrame(const QString &leftToken,
			   const QString &rightToken,
			   const QueryFrameList &frameList);

	QueryFrame *appendFrame(const QueryFrame &frame);

	QString toString() const;

	QueryFrame part(const Qst::QueryClause &clause) const;
	ClauseFrameMap parts(const Qst::QueryClauses &clauses) const;

	void clear();

	void setPartClause(const Qst::QueryClause &clause);

	QString token() const;
	QString leftToken() const;
	QString rightToken() const;
	QueryFrameList frameList() const;

	QueryFrame & operator<<(const QueryFrame &frame);
	QueryFrame & operator<<(const QString &token);

};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const QueryFrame &);
#endif

#endif // QUERYFRAME_H
