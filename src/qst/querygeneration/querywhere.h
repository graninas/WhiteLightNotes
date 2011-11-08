#ifndef QUERYWHERE_H
#define QUERYWHERE_H

#include "queryfield.h"
#include "queryin.h"

#include "qst/qstplaceholder.h"

#include <QList>

class QueryWhere
{
public:

	typedef QList<QueryWhere> ConditionList;

private:

	QueryField		_field;
	ConditionList	_conditionList;
	Qst::Relation	_relation;

public:
    QueryWhere();

	QueryWhere(const QString &condition);

	QueryWhere(const QString &fieldName,
			   const QueryValue &value,
			   const Qst::Functor &functor = Qst::TypeDependedFunctor);

	QueryWhere(const QString &fieldName,
			   const QVariant &value,
			   const Qst::Functor &functor = Qst::TypeDependedFunctor);

	QueryWhere(const QString &fieldName,
			   const QueryValue &value1,
			   const QueryValue &value2);

	QueryWhere(const QueryField &field);

	QueryWhere(const QueryIn &inCondition);

	QueryWhere(const QString &fieldName, const Qst::QstPlaceholder &placeholder);

	QueryField field() const;
	void setField(const QueryField &field);

	void appendCondition(const QueryWhere &cond);
	ConditionList	conditionList() const;

	Qst::Relation	relation() const;
	void setRelation(const Qst::Relation &conditionList);

	bool isValid() const;

	QueryWhere validOnly() const;

	void updatePlaceholder(const QString &placeholderName,
						   const QueryValue &value,
						   const Qst::Functor &functor);

	void updatePlaceholder(const QString &placeholderName,
						   const QVariantList &varList,
						   const Qst::Functor &functor);

	void resetPlaceholders();

	QueryWhere &operator ||(const QueryWhere &condition);
	QueryWhere &operator &&(const QueryWhere &condition);
	QueryWhere &operator ||(const QueryIn &inCondition);
	QueryWhere &operator &&(const QueryIn &inCondition);

	friend bool operator==(const QueryWhere &c1, const QueryWhere &c2)
	{
		return c1._field == c2._field
				&& c1._relation == c2._relation
				&& c1._conditionList == c2._conditionList;
	}

private:

	QueryWhere & _appendCondition(const QueryWhere &cond,
								  const Qst::Relation &relation);

};

///////////////////////////////////////////////////////////////////////////////////////////

typedef QueryWhere QueryOn;
typedef QueryWhere QueryHaving;

///////////////////////////////////////////////////////////////////////////////////////////

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const QueryWhere &);
#endif

#endif // QUERYWHERE_H
