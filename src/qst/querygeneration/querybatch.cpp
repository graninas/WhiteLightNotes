#include "querybatch.h"

using namespace Qst;

#include <QDebug>

/*!

Структура QueryBatch - иерархическая.

-= QuerySelect =-

QueryBatch (QuerySelect, name, BatchSource, ClauseNone)
|
|__ _batchPacks:
	|__<ClauseSelect>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseSelect)
	|__<ClauseFrom>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseFrom)
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseFrom)
		|__ ~
	|__<ClauseFrom>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseFrom)
			|__ fields(ClauseFrom)


	|__<ServiceJoinClause_Mask>

		 |__ QueryBatch (QueryJoin, _, BatchSource, ServiceJoinClause_Mask)
			 |__ <ClauseLeftJoin>
				 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseLeftJoin)
			 |__ <ClauseOn>
				 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseOn)
						|__ QueryWhere (condition tree)

		 |__ QueryBatch (QueryJoin, _, BatchSource, ServiceJoinClause_Mask)
			 |__ <ClauseRightJoin>
				 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseRightJoin)
			 |__ <ClauseOn>
				 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseOn)
						|__ QueryWhere (condition tree)

		 |__ QueryBatch (QueryJoin, _, BatchSource, ServiceJoinClause_Mask)
			 |__ <ClauseInnerJoin>
				 |__ QueryBatch (QuerySelect, alias, BatchSource, ClauseInnerJoin)
					 |
					 |__ _batchPacks:
						 |__<ClauseSelect>
							 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseSelect)
						 |__<ClauseFrom>
							 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseFrom)
							 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseFrom)
							 |__ ~
			 |__ <ClauseOn>
				 |__ QueryBatch (QueryUndefined, name, StringSource, ClauseOn)
						|__ QueryWhere (condition tree)

		 |__ ~

	|__<ClauseWhere>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseWhere)
				|__ QueryWhere (condition tree)

	|__<ClauseGroupBy>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseGroupBy)

	|__<ClauseHaving>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseHaving)

	|__<ClauseOrderBy>
		|__ QueryBatch (QueryUndefined, name, StringSource, ClauseOrderBy)


-= QueryInsert =-

	QueryBatch (QueryInsert, name, BatchSource, ClauseNone)
	|
	|__ _batchPacks:
		|__<ClauseInsert>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseInsert)
		|__<ClauseValues>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseValues)
				|__ fields(ClauseValues)

-= QueryUpdate =-

	QueryBatch (QueryUpdate, name, BatchSource, ClauseNone)
	|
	|__ _batchPacks:
		|__<ClauseUpdate>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseUpdate)
		|__<ClauseSet>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseSet)
				|__ fields(ClauseSet)
		|__<ClauseWhere>
				|__ QueryBatch (QueryUndefined, name, StringSource, ClauseWhere)
						|__ QueryWhere (condition tree)

-= QueryDelete =-

	QueryBatch (QueryDelete, name, BatchSource, ClauseNone)
	|
	|__ _batchPacks:
		|__<ClauseDelete>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseDelete)
		|__<ClauseWhere>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseWhere)
					|__ QueryWhere (condition tree)

-= QueryExecute =-

	QueryBatch (QueryExecute, name, BatchSource, ClauseNone)
	|
	|__ _batchPacks:
		|__<ClauseExecute>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseExecute)
		|__<ClauseParameters>
			|__ QueryBatch (QueryUndefined, name, StringSource, ClauseParameters)
				|__ fields(ClauseParameters)

-= UserDefinedQuery =-

 QueryBatch (UserDefinedQuery, name, BatchSource, ClauseNone)
 |
 |__ _batchPacks:
	 |__<UserDefinedClauses>
		 |__ QueryBatch (QueryUndefined, name, StringSource, UserDefinedClauses)
*/


QueryClauseList QueryBatch::_placeholderedClauses()
{
	return QueryClauseList()
			<< ClauseParameters
			<< ClauseValues
			<< ClauseWhere;
}

QueryBatch::QueryBatch()
	:
	  _name(QString()),
	  _sourceType(StringSource),
	  _queryType(QueryUndefined),
	  _queryClause(NoClause)
{
}

QueryBatch::QueryBatch(const QueryType &queryType,
					   const QString &name,
					   const Qst::QueryClause &queryClause)
	:
	  _name(name),
	  _sourceType(BatchSource),
	  _queryType(queryType),
	  _queryClause(queryClause)

{
}

QueryBatch::QueryBatch(const Qst::QueryClause &queryClause,
					   const QString &name)
	:
	  _name(name),
	  _sourceType(StringSource),
	  _queryType(QueryUndefined),
	  _queryClause(queryClause)
{
	Q_ASSERT(queryClause != NoClause);
}

QueryBatch::QueryBatch(const QString &name)
	:
	  _name(name),
	  _sourceType(StringSource),
	  _queryType(QueryUndefined),
	  _queryClause(NoClause)
{
}

QueryBatch::QueryBatch(const QueryWhere &condition, const Qst::QueryClause &queryClause)
	:
	  _name(QString()),
	  _sourceType(StringSource),
	  _queryType(QueryUndefined),
	  _condition(condition),
	  _queryClause(queryClause)
{
}

void QueryBatch::setName(const QString &name)
{
	_name = name;
}

QString QueryBatch::name() const
{
	return _name;
}

QString QueryBatch::alias() const
{
	if (_queryClause == NoClause)
		return "";
	return _name;
}

void QueryBatch::setQueryClause(const Qst::QueryClause &queryClause)
{
	_queryClause = queryClause;
}

Qst::QueryClause QueryBatch::queryClause() const
{
	return _queryClause;
}

void QueryBatch::setQueryType(const Qst::QueryType &queryType)
{
	_queryType = queryType;
}

Qst::QueryType QueryBatch::queryType() const
{
	return _queryType;
}

QueryBatchPack QueryBatch::batchPack() const
{
	return _batchPacks;
}

QueryBatchList QueryBatch::batches(const Qst::QueryClause clause) const
{
	QueryClause packClause = _clauseInBatchPack(clause);

	if (packClause != NoClause)
		return _batchPacks[packClause];

	return QueryBatchList();
}

/*! Добавляет batch в конец слота с индексом packClause.*/
void QueryBatch::appendBatch(const Qst::QueryClause packClause,
							 const QueryBatch &batch)
{
	_batchPacks[packClause].append(batch);
}

QueryWhere	QueryBatch::condition(const bool &validOnly) const
{
	if (validOnly)
		return _condition.validOnly();
return _condition;
}

bool QueryBatch::contains(const QueryField &field) const
{
	return _fields.contains(field);
}

QStringList QueryBatch::fieldNames() const
{
QStringList resList;

	for (int i = 0; i < _fields.count(); ++i)
		resList << _fields[i].name();

	return resList;
}

QStringList QueryBatch::sourceNames() const
{
	return QStringList() << _name;
}

void QueryBatch::setFields(const QueryFieldList &fields)
{
	_fields = fields;
}

QueryFieldList QueryBatch::fields(const QueryClause &queryClause) const
{
	QueryFieldList fieldList;

	for (int i = 0; i < _fields.count(); ++i)
		if (_fields[i].testClause(queryClause))
			fieldList.append(_fields[i]);

return fieldList;
}

QueryBatch & QueryBatch::updatePlaceholder(const QString &placeholderName,
										   const QueryValue &value,
										   const Qst::Functor &functor)
{
	foreach (Qst::QueryClause cl, _placeholderedClauses())
	{
		if (_batchPacks.contains(cl))
			for (int i = 0; i < _batchPacks[cl].count(); ++i)
				_batchPacks[cl][i].updatePlaceholder(placeholderName, value, functor);
	}

	_condition.updatePlaceholder(placeholderName, value, functor);

	return (*this);
}

QueryBatch & QueryBatch::updatePlaceholder(const QString &placeholderName,
										   const QVariantList &varList,
										   const Qst::Functor &functor)
{
	foreach (Qst::QueryClause cl, _placeholderedClauses())
	{
		if (_batchPacks.contains(cl))
			for (int i = 0; i < _batchPacks[cl].count(); ++i)
				_batchPacks[cl][i].updatePlaceholder(placeholderName, varList, functor);
	}

	_condition.updatePlaceholder(placeholderName, varList, functor);

	return (*this);
}

QueryBatch & QueryBatch::updatePlaceholder(const QVariantMap &varMap)
{
	foreach (Qst::QueryClause cl, _placeholderedClauses())
	{
	if (_batchPacks.contains(cl))
		for (int i = 0; i < _batchPacks[cl].count(); ++i)
			_batchPacks[cl][i].updatePlaceholder(varMap);
	}

	QVariantMap::const_iterator iter = varMap.begin();
	while (iter != varMap.end())
	{
		for (int i = 0; i < _fields.count(); ++i)
			_fields[i].updatePlaceholder(iter.key(), QueryValue(iter.value()), NoFunctor);
		iter++;
	}

	return (*this);
}

void QueryBatch::resetPlaceholders()
{
	foreach (Qst::QueryClause cl, _placeholderedClauses())
	{
		if (_batchPacks.contains(cl))
			for (int i = 0; i < _batchPacks[cl].count(); ++i)
				_batchPacks[cl][i].resetPlaceholders();
	}

	_condition.resetPlaceholders();

	for (int i = 0; i < _fields.count(); ++i)
		_fields[i].resetPlaceholder();
}

/*! Добавляет batch в "свой" слот - слот с индексом batch.queryClause(). */
QueryBatch & QueryBatch::operator<<(const QueryBatch &batch)
{
	Q_ASSERT(batch.queryClause() != NoClause);
	if (batch.queryClause() == NoClause)
		return (*this);

	appendBatch(batch.queryClause(), batch);
	return *this;
}

QueryBatch & QueryBatch::operator<<(const QueryWhere &condition)
{
	Q_ASSERT(_sourceType == BatchSource);

	if (_batchPacks[ClauseWhere].isEmpty())
		appendBatch(ClauseWhere, QueryBatch(condition));
	else
		_batchPacks[ClauseWhere].first()._addCondition(condition);

	return *this;
}

QueryBatch & QueryBatch::operator<<(const QueryField &field)
{
	QueryClause clause = field.clause();

	if (_sourceType == BatchSource)
	{
		if (clause == ClauseWhere)
		{
			appendBatch(ClauseWhere, QueryBatch(QueryWhere(field)));
		}
		else
		{
			if (_batchPacks[clause].isEmpty())
				appendBatch(clause, QueryBatch(clause, QString()));

			_batchPacks[clause].last()._addField(field);
		}
	}
	else
		_addField(field);

	return *this;
}

QueryBatch & QueryBatch::operator<<(const QString &sourceName)
{
	QueryClause clause;
	switch (_queryType)
	{
	case QuerySelect:
	case QueryDelete: clause = ClauseFrom; break;
	case QueryInsert: clause = ClauseInsert; break;
	case QueryUpdate: clause = ClauseUpdate; break;
	case QueryExecute: clause = ClauseExecute; break;

	default: Q_ASSERT(false);
	}

	appendBatch(clause, QueryBatch(clause, sourceName));
	return *this;
}

QueryBatch & QueryBatch::setUserDefinedQuery(const QString &query)
{
	Q_ASSERT(queryType() == UserDefinedQuery);
	Q_ASSERT(!query.isEmpty());

	QueryBatch btch = QueryBatch(UserDefinedClauses, query);
	(*this) << btch;

return (*this);
}

QueryBatch & QueryBatch::select(const QueryBatch &batch)
{
	Q_ASSERT(queryType() == QuerySelect);

	QueryBatch btch = batch;
	btch.setQueryClause(ClauseSelect);
	(*this) << btch;

return (*this);
}

QueryBatch & QueryBatch::select(const QueryFieldList &fields)
{
	Q_ASSERT(queryType() == QuerySelect);
	Q_ASSERT(!fields.isEmpty());

	foreach (QueryField field, fields)
	{
		Q_ASSERT(!field.name().isEmpty());

		field.setClause(ClauseSelect);
		(*this) << field;
	}

return (*this);
}

QueryBatch & QueryBatch::select(const QStringList &fieldNames)
{
	Q_ASSERT(queryType() == QuerySelect);
	Q_ASSERT(!fieldNames.isEmpty());

	foreach (QString name, fieldNames)
	{
		Q_ASSERT(!name.isEmpty());
		(*this) << QueryField(name, ClauseSelect);
	}

return (*this);
}

QueryBatch & QueryBatch::select(const QString &fieldName)
{
	Q_ASSERT(queryType() == QuerySelect);
	Q_ASSERT(!fieldName.isEmpty());

	(*this) << QueryField(fieldName);
return (*this);
}

QueryBatch & QueryBatch::from(const QueryBatch &batch)
{
	QueryBatch btch(batch);

	btch.setQueryClause(ClauseFrom);

	(*this) << btch;
return (*this);
}

QueryBatch & QueryBatch::from(const QString &source)
{
	Q_ASSERT(!source.isEmpty());

	(*this) << QueryBatch(ClauseFrom, source);
return (*this);
}

QueryBatch & QueryBatch::join(const QueryBatch &batch,
							  const QueryOn &condition)
{
	Q_ASSERT(ServiceJoinClause_Mask &  batch.queryClause());
	Q_ASSERT(ServiceJoinClause_Mask != batch.queryClause());

	QueryBatch joinQueryBatch = QueryBatch(ServiceQueryJoin, "", ServiceJoinClause_Mask);

	joinQueryBatch.appendBatch(batch.queryClause(), batch);
	joinQueryBatch.appendBatch(ClauseOn, QueryBatch(condition, ClauseOn));

appendBatch(ServiceJoinClause_Mask, joinQueryBatch);
return (*this);
}

QueryBatch & QueryBatch::join(const Qst::QueryClause &joinClause,
							  const QString &tableName,
							  const QueryOn &condition)
{
	Q_ASSERT(ServiceJoinClause_Mask & joinClause);
	Q_ASSERT(!tableName.isEmpty());

	join(QueryBatch(joinClause, tableName), condition);
return (*this);
}

QueryBatch & QueryBatch::innerJoin(const QString &tableName,
								   const QueryOn &condition)
{
	Q_ASSERT(!tableName.isEmpty());

	join(QueryBatch(ClauseInnerJoin, tableName), condition);
return (*this);
}

QueryBatch & QueryBatch::leftJoin(const QString &tableName,
								  const QueryOn &condition)
{
	Q_ASSERT(!tableName.isEmpty());

	join(QueryBatch(ClauseLeftJoin, tableName), condition);
return (*this);
}

QueryBatch & QueryBatch::rightJoin(const QString &tableName,
								   const QueryOn &condition)
{
	Q_ASSERT(!tableName.isEmpty());

	join(QueryBatch(ClauseRightJoin, tableName), condition);
return (*this);
}

QueryBatch & QueryBatch::fullJoin(const QString &tableName,
								  const QueryOn &condition)
{
	Q_ASSERT(!tableName.isEmpty());

	join(QueryBatch(ClauseFullJoin, tableName), condition);
return (*this);
}

QueryBatch & QueryBatch::where(const QueryWhere &condition)
{
	(*this) << condition;
return (*this);
}

QueryBatch & QueryBatch::where(const QString &strCond)
{
	Q_ASSERT(!strCond.isEmpty());

	(*this) << QueryWhere(strCond);
return (*this);
}

QueryBatch & QueryBatch::where(const QString &fieldName,
							   const QueryValue &value)
{
	Q_ASSERT(!fieldName.isEmpty());

	(*this) << QueryWhere(fieldName, value);
return (*this);
}

QueryBatch & QueryBatch::where(const QString &fieldName,
							   const QueryValue &value1,
							   const QueryValue &value2)
{
	Q_ASSERT(!fieldName.isEmpty());

	(*this) << QueryWhere(fieldName, value1, value2);
return (*this);
}

QueryBatch & QueryBatch::where(const QString &fieldName,
							   const Qst::QstPlaceholder &placeholder,
							   const Qst::Functor &functor)
{
	Q_ASSERT(!fieldName.isEmpty());

	(*this) << QueryWhere(QueryField(fieldName, placeholder.name(), functor));
return (*this);
}

QueryBatch & QueryBatch::groupBy(const QStringList &fieldNames)
{
	Q_ASSERT(!fieldNames.isEmpty());

	foreach (QString f, fieldNames)
	{
		Q_ASSERT(!f.isEmpty());
		(*this) << QueryField(f, ClauseGroupBy);
	}

return (*this);
}

QueryBatch & QueryBatch::groupBy(const QString &fieldName)
{
	Q_ASSERT(!fieldName.isEmpty());

	(*this) << QueryField(fieldName, ClauseGroupBy);
return (*this);
}

QueryBatch & QueryBatch::having(const QueryHaving &condition)
{
	appendBatch(ClauseHaving, QueryBatch(condition));
return (*this);
}

QueryBatch & QueryBatch::having(const QString &strCond)
{
	Q_ASSERT(!strCond.isEmpty());

	appendBatch(ClauseHaving, QueryBatch(QueryHaving(strCond), ClauseHaving));
return (*this);
}

QueryBatch & QueryBatch::orderBy(const QStringList &fieldNames)
{
	Q_ASSERT(!fieldNames.isEmpty());

	foreach (QString f, fieldNames)
	{
		Q_ASSERT(!f.isEmpty());
		(*this) << QueryField(f, ClauseOrderBy);
	}

return (*this);
}

QueryBatch & QueryBatch::orderBy(const QString &fieldName)
{
	Q_ASSERT(!fieldName.isEmpty());

	(*this) << QueryField(fieldName, ClauseOrderBy);
return (*this);
}

QueryBatch & QueryBatch::insert(const QString &tableName, const QStringList &fieldNames)
{
	Q_ASSERT(queryType() == QueryInsert);
	Q_ASSERT(!tableName.isEmpty());
	Q_ASSERT(!fieldNames.isEmpty());

	QueryBatch batch = QueryBatch(ClauseInsert, tableName);

	foreach (QString f, fieldNames)
	{
		Q_ASSERT(!f.isEmpty());
		batch << QueryField(f, ClauseInsert);
	}

	appendBatch(ClauseInsert, batch);
return (*this);
}

QueryBatch & QueryBatch::values(const QueryFieldList &fieldValues)
{
	Q_ASSERT(!fieldValues.isEmpty());

	QueryBatch batch;
	batch.setFields(fieldValues);
	batch.setQueryClause(ClauseValues);

	appendBatch(ClauseValues, batch);
return (*this);
}

QueryBatch & QueryBatch::values(const Qst::QstPlaceholderList &placeholderList)
{
	Q_ASSERT(!placeholderList.isEmpty());

	QueryFieldList fieldList = _getFieldList(placeholderList,
											 ClauseValues,
											 Qst::NoFunctor);

	QueryBatch batch = QueryBatch(ClauseValues, QString());
	batch.setFields(fieldList);

	appendBatch(ClauseValues, batch);
return (*this);
}

QueryBatch & QueryBatch::values(const QueryValueList &values)
{
	Q_ASSERT(!values.isEmpty());

	QueryFieldList list;

	foreach(QueryValue val, values)
		list << QueryField(val, ClauseValues);

	QueryBatch batch = QueryBatch(ClauseValues, QString());
	batch.setFields(list);

	appendBatch(ClauseValues, batch);
return (*this);
}

QueryBatch & QueryBatch::values(const QVariantList &values)
{
	Q_ASSERT(!values.isEmpty());

	QueryFieldList list;

	foreach(QVariant val, values)
		list << QueryField(QueryValue(val), ClauseValues);

	QueryBatch batch = QueryBatch(ClauseValues, QString());
	batch.setFields(list);

	appendBatch(ClauseValues, batch);
return (*this);
}

QueryBatch & QueryBatch::update(const QString &tableName)
{
	Q_ASSERT(queryType() == QueryUpdate);
	Q_ASSERT(!tableName.isEmpty());

	appendBatch(ClauseUpdate, QueryBatch(ClauseUpdate, tableName));
return (*this);
}

QueryBatch & QueryBatch::set(const QueryFieldList &fields)
{
	Q_ASSERT(!fields.empty());

	if (_batchPacks[ClauseSet].isEmpty())
		appendBatch(ClauseSet, QueryBatch(ClauseSet, QString()));

	QueryFieldList list;
	foreach (QueryField field, fields)
	{
		Q_ASSERT(!field.name().isEmpty());

		field.setClause(ClauseSet);
		list << field;
	}
	Q_ASSERT(!list.isEmpty());

	_batchPacks[ClauseSet].last().setFields(list);

	Q_ASSERT(!_batchPacks[ClauseSet].last().fields(ClauseSet).isEmpty());

return (*this);
}

QueryBatch & QueryBatch::deleteFrom(const QString &tableName)
{
	Q_ASSERT(queryType() == QueryDelete);
	Q_ASSERT(!tableName.isEmpty());

	appendBatch(ClauseDelete, QueryBatch(ClauseDelete, tableName));
return (*this);
}

QueryBatch & QueryBatch::execute(const QString &funcName)
{
	Q_ASSERT(queryType() == QueryExecute);
	Q_ASSERT(!funcName.isEmpty());

	appendBatch(ClauseExecute, QueryBatch(ClauseExecute, funcName));
return (*this);
}

QueryBatch & QueryBatch::parameters(const QVariantList &varList)
{
	Q_ASSERT(!varList.isEmpty());

	QueryFieldList fieldList = _getFieldList(varList,
											 ClauseParameters);

	QueryBatch batch = QueryBatch(ClauseParameters, QString());
	batch.setFields(fieldList);

	appendBatch(ClauseParameters, batch);
return (*this);
}

QueryBatch & QueryBatch::parameters(const Qst::QstPlaceholderList &placeholderList)
{
	Q_ASSERT(!placeholderList.isEmpty());

	QueryFieldList fieldList = _getFieldList(placeholderList,
											 Qst::ClauseParameters,
											 Qst::TypeDependedFunctor);

	QueryBatch batch = QueryBatch(ClauseParameters, QString());
	batch.setFields(fieldList);

	appendBatch(ClauseParameters, batch);
return (*this);
}

void QueryBatch::_addField(const QueryField &field)
{
	_fields.append(field);
}

void QueryBatch::_addCondition(const QueryWhere &cond)
{
	_condition && cond;
}

QueryClause QueryBatch::_clauseInBatchPack(const QueryClause &clause) const
{
	QList<QueryClause> keys = _batchPacks.keys();

	foreach (QueryClause cl, keys)
		if (clause & cl)
			return cl;

return NoClause;
}

QueryFieldList QueryBatch::_getFieldList(const Qst::QstPlaceholderList &plList,
										 const Qst::QueryClause &clause,
										 const Qst::Functor &functor) const
{
	Q_ASSERT(!plList.isEmpty());
	QueryFieldList fieldList;
		foreach (QstPlaceholder pl, plList)
		{
			Q_ASSERT(!pl.names().isEmpty());

			QueryField field = QueryField(pl.name(),
										  pl.name(),
										  functor,
										  clause);
			fieldList.append(field);
		}
	return fieldList;
}

QueryFieldList QueryBatch::_getFieldList(const QVariantList &list,
										 const Qst::QueryClause &clause) const
{
	QueryFieldList fieldList;
	foreach (QVariant var, list)
		fieldList.append(QueryField(QueryValue(var), clause));
	return fieldList;
}
