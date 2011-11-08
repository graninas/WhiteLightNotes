#include "querywhere.h"

/*! \class QueryWhere
	\brief QueryWhere


Figure1.
QueryWhere 1 && Queryhere 2:
 ______          ______
|QW1|f1|   &&   |QW2|f2|

Result:
 ___
|QW3|
&&|_ ______   ______
	|QW1|f1|-|QW2|f2|

Figure2.
QueryWhere 1 && QueryWhere x:
 ______            ___
|QW1|f1|   &&     |QWx|
				  Or|_ ______   ______
					  |QW2|f2|-|QW3|f3|-...

Result:

 _____
|_QWy_|
&&|_ ______   ___
	|QW1|f1|-|QWx|
			 Or|_ ______   ______
				 |QW2|f2|-|QW3|f3|-...
*/

#include <QDebug>

using namespace Qst;

QueryWhere::QueryWhere()
	:
	_relation(UndefinedRelation)
{
}

QueryWhere::QueryWhere(const QString &condition)
	:
	  _field(QueryField(condition)),
	  _relation(UndefinedRelation)
{
}

QueryWhere::QueryWhere(const QString &fieldName,
					   const QueryValue &value,
					   const Functor &functor)
	:
	  _field(QueryField(fieldName, value, functor)),
	  _relation(UndefinedRelation)
{
}

QueryWhere::QueryWhere(const QString &fieldName,
					   const QVariant &value,
					   const Qst::Functor &functor)
	:
	  _field(QueryField(fieldName, QueryValue(value), functor)),
	  _relation(UndefinedRelation)
{
}

QueryWhere::QueryWhere(const QString &fieldName,
					   const QueryValue &value1,
					   const QueryValue &value2)
	:
	  _field(QueryField(fieldName, value1, value2)),
	  _relation(UndefinedRelation)
{
}

QueryWhere::QueryWhere(const QueryField &field)
	:
	_field(field),
	_relation(UndefinedRelation)
{
}

QueryWhere::QueryWhere(const QueryIn &inCondition)
	:
	  _relation(UndefinedRelation)
{
	_field = inCondition.field();
	_field.setClause(ClauseWhere);
}

QueryWhere::QueryWhere(const QString &fieldName,
					   const Qst::QstPlaceholder &placeholder)
	:
	  _field (QueryField(fieldName,
						 placeholder.name(),
						 Qst::TypeDependedFunctor,
						 Qst::ClauseWhere)),
	  _relation(UndefinedRelation)
{
}

QueryField QueryWhere::field() const
{
	return _field;
}

void QueryWhere::setField(const QueryField &field)
{
	_field = field;
}

void QueryWhere::appendCondition(const QueryWhere &cond)
{
	_conditionList.append(cond);
}

QueryWhere::ConditionList QueryWhere::conditionList() const
{
	return _conditionList;
}

Relation QueryWhere::relation() const
{
	return _relation;
}

void QueryWhere::setRelation(const Relation &relation)
{
	_relation = relation;
}

bool QueryWhere::isValid() const
{
	foreach (QueryWhere cond, _conditionList)
	if (!cond.isValid())
		return false;

	if (_relation == Qst::UndefinedRelation && !_field.isValid())
		return false;

return true;
}

QueryWhere QueryWhere::validOnly() const
{
	QueryWhere resCond;
	resCond.setRelation(_relation);
	resCond.setField(_field);

	foreach (QueryWhere cond, _conditionList)
	{
		if (cond.relation() == UndefinedRelation)
		{
			if (cond.isValid())
				resCond.appendCondition(cond);
		}
		else
		{
			resCond.appendCondition(cond.validOnly());
		}
	}

if (resCond.conditionList().count() == 1)
	return resCond.conditionList().first();

return resCond;
}

void QueryWhere::updatePlaceholder(const QString &placeholderName,
								   const QueryValue &value,
								   const Qst::Functor &functor)
{
	_field.updatePlaceholder(placeholderName, value, functor);

	for (int i = 0; i < _conditionList.count(); ++i)
		_conditionList[i].updatePlaceholder(placeholderName, value, functor);
}

void QueryWhere::updatePlaceholder(const QString &placeholderName,
								   const QVariantList &varList,
								   const Qst::Functor &functor)
{
	_field.updatePlaceholder(placeholderName, varList, functor);

	for (int i = 0; i < _conditionList.count(); ++i)
		_conditionList[i].updatePlaceholder(placeholderName, varList, functor);
}

void QueryWhere::resetPlaceholders()
{
	_field.resetPlaceholder();

	for (int i = 0; i < _conditionList.count(); ++i)
		_conditionList[i].resetPlaceholders();
}

QueryWhere & QueryWhere::operator ||(const QueryWhere &condition)
{
	return _appendCondition(condition, Or);
}

QueryWhere & QueryWhere::operator &&(const QueryWhere &condition)
{
	return _appendCondition(condition, And);
}

QueryWhere & QueryWhere::operator ||(const QueryIn &inCondition)
{
	return _appendCondition(QueryWhere(QueryField(inCondition.field().name(),
												  inCondition.field().valueList(),
												  inCondition.field().functor(),
												  ClauseWhere)), Or);
}

QueryWhere & QueryWhere::operator &&(const QueryIn &inCondition)
{
	return _appendCondition(QueryWhere(QueryField(inCondition.field().name(),
												  inCondition.field().valueList(),
												  inCondition.field().functor(),
												  ClauseWhere)), And);
}

QueryWhere & QueryWhere::_appendCondition(const QueryWhere &cond,
										  const Relation &relation)
{
	if (_relation == UndefinedRelation)
	{
		QueryWhere tmpCond = QueryWhere(_field);
		_field = QueryField();
		_relation = relation;

		_conditionList.append(tmpCond);
		_conditionList.append(cond);
	}
	else
	{
		if (_relation == relation)
			_conditionList.append(cond);
		else
		{
			QueryWhere tmpCond = (*this);
			_field = QueryField();
			_conditionList.clear();
			_relation = relation;

			_conditionList.append(tmpCond);
			_conditionList.append(cond);
		}
	}
return (*this);
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QueryWhere &f)
{
#ifndef Q_BROKEN_DEBUG_STREAM
	dbg.nospace() << "QueryWhere(field = " << f.field();
	dbg.nospace() << ", conditionListOperator = " << f.relation();
	dbg.nospace() << ", conditionList = " << f.conditionList() << ").";

	return dbg.space();
#else
	qWarning("This compiler doesn't support streaming QueryWhere to QDebug");
	return dbg;
	Q_UNUSED(f);
#endif
}
#endif
