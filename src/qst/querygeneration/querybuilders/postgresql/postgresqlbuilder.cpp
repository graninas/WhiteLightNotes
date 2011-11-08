#include "postgresqlbuilder.h"

#include "postgresqlformat.h"

#include <QDebug>

using namespace Qst;

PostgreSqlBuilder::PostgreSqlBuilder()
{
	_addQueryAccessory(ClauseSelect,    QueryAccessory(SQL_SELECT,     "()"));
	_addQueryAccessory(ClauseFrom,      QueryAccessory(SQL_FROM,       "()"));
	_addQueryAccessory(ClauseLeftJoin,  QueryAccessory(SQL_LEFT_JOIN,  "()"));
	_addQueryAccessory(ClauseRightJoin, QueryAccessory(SQL_RIGHT_JOIN, "()"));
	_addQueryAccessory(ClauseFullJoin,  QueryAccessory(SQL_FULL_JOIN,  "()"));
	_addQueryAccessory(ClauseInnerJoin, QueryAccessory(SQL_INNER_JOIN, "()"));
	_addQueryAccessory(ClauseOn,        QueryAccessory(SQL_ON,         "()"));
	_addQueryAccessory(ClauseWhere,     QueryAccessory(SQL_WHERE,      "()"));
	_addQueryAccessory(ClauseGroupBy,   QueryAccessory(SQL_GROUP_BY,   "()"));
	_addQueryAccessory(ClauseHaving,    QueryAccessory(SQL_HAVING,     "()"));
	_addQueryAccessory(ClauseOrderBy,   QueryAccessory(SQL_ORDER_BY,   "()"));

	_addQueryAccessory(ClauseInsert,     QueryAccessory(SQL_INSERT,     ""));
	_addQueryAccessory(ClauseValues,     QueryAccessory(SQL_VALUES,     ""));
	_addQueryAccessory(ClauseUpdate,     QueryAccessory(SQL_UPDATE,     ""));
	_addQueryAccessory(ClauseSet,        QueryAccessory(SQL_SET,        ""));
	_addQueryAccessory(ClauseDelete,     QueryAccessory(SQL_DELETE,     ""));
	_addQueryAccessory(ClauseExecute,    QueryAccessory(SQL_EXECUTE,    ""));
	_addQueryAccessory(ClauseParameters, QueryAccessory(SQL_PARAMETERS, ""));

	_addQueryAccessory(ServiceJoinClause_Mask, QueryAccessory("",  ""));
	_addQueryAccessory(UserDefinedClauses, QueryAccessory("", ""));
}

QueryScheme PostgreSqlBuilder::queryScheme(const QueryType &queryType) const
{
	return AbstractQueryBuilder::queryScheme(queryType);
}

QueryFrame PostgreSqlBuilder::makeQueryFrame(const QueryBatch &queryBatch,
											 const bool &isSubquery) const
{
	return AbstractQueryBuilder::makeQueryFrame(queryBatch, isSubquery);
}

QueryFrame PostgreSqlBuilder::makeKeywordFrame(const QueryClause &queryClause) const
{
	return AbstractQueryBuilder::makeKeywordFrame(queryClause);
}

/*! Компонует один фрейм для одного элемента секции. */
QueryFrame PostgreSqlBuilder::makeClauseItemFrame(const QueryBatch &batch,
												  const bool &delimiterEnded) const
{
	switch (batch.queryClause())
	{
	case ClauseSelect:       return _commonClauseFrame(batch.fieldNames(), _itemsDelimiter(ClauseSelect), delimiterEnded);
	case ClauseFrom:         return _commonClauseFrame(batch.sourceNames(), _itemsDelimiter(ClauseFrom), delimiterEnded);
	case ClauseOn:
	case ClauseHaving:
	case ClauseWhere:        return _conditionClauseFrame(batch.condition(true), delimiterEnded ? _boolOperator(And) : "");
	case ClauseGroupBy:
	case ClauseOrderBy:      return _commonClauseFrame(batch.fieldNames(), _itemsDelimiter(ClauseOrderBy), delimiterEnded);
	case ClauseUpdate:       return _statementClauseFrame(batch.name(), QStringList(), "");
	case ClauseDelete:       return _statementClauseFrame(batch.name(), QStringList(), "");
	case ClauseExecute:      return _statementClauseFrame(batch.name(), QStringList(), "");
	case ClauseInsert:       return _statementClauseFrame(batch.name(), batch.fieldNames(), _itemsDelimiter(ClauseInsert));
	case ClauseValues:       return _valuesClauseFrame(batch.fields(ClauseValues), _itemsDelimiter(ClauseValues));
	case ClauseSet:          return _setClauseFrame(batch.fields(ClauseSet), _itemsDelimiter(ClauseSet));
	case ClauseParameters:   return _parametersClauseFrame(batch.fields(ClauseParameters), _itemsDelimiter(ClauseParameters));
	case ClauseLeftJoin:     return _joinClauseFrame(batch.name());
	case ClauseRightJoin:    return _joinClauseFrame(batch.name());
	case ClauseFullJoin:     return _joinClauseFrame(batch.name());
	case ClauseInnerJoin:    return _joinClauseFrame(batch.name());
	case UserDefinedClauses: return QueryFrame(batch.name(), "", "");

	case NoClause:
	case ClauseAll_Mask:
	case ClauseValued_Mask:
	case ClauseModifying_Mask:
	case ClauseHasFieldName_Mask:
	case ClauseAllButSelect_Mask:
	case ServiceJoinClause_Mask:
	default: Q_ASSERT(false);
	}
return QueryFrame();
}

QueryBatchList PostgreSqlBuilder::validClauseBatches(const QueryClause &queryClause,
													 const QueryBatchList &batchList) const
{
	QueryBatchList list;

	if (queryClause == ClauseWhere || queryClause == ClauseHaving)
	{
		foreach (QueryBatch batch, batchList)
		{
			QueryWhere cond = batch.condition(true);

			if (cond.isValid())
				list.append(QueryBatch(cond, queryClause));
		}
	}
	else
		list = batchList;

return list;
}

QString PostgreSqlBuilder::_composeCondition(const QueryField &field) const
{
	if (field.isValuesValid())
	{
		Functor functor = field.functor();
		StringTemplate conditionTemplate = _conditionTemplate(functor);

			switch (functor)
			{
			case Between: return _betweenCondition(field, conditionTemplate);
			case InList:
			case NotInList: return _inListCondition(field, conditionTemplate);

			default: break;
			};

		QString strCondition = _valueFormat.toString(field.value(0),
													 StringBordering | DateBordering | TimeBordering | DateTimeBordering,
													 NoPlaceholders,
													 true);
		return conditionTemplate.string(field.name(), strCondition);
	}
	else
		if (!field.placeholderName().isEmpty())
			return QString();
return field.name();
}

QueryFrame PostgreSqlBuilder::_commonClauseFrame(QStringList itemsList,
												 QString delimiter,
												 const bool &delimiterEnded,
												 const QString &leftBracket,
												 const QString &rightBracket) const
{
	QueryFrame frame("", leftBracket, rightBracket);

	for (int i = 0; i < itemsList.count(); ++i)
		frame << itemsList[i] + ( (i < itemsList.count()-1) || delimiterEnded ? delimiter + " " : "");

return frame;
}

QueryFrame PostgreSqlBuilder::_conditionClauseFrame(const QueryWhere &whereCondition,
													const QString &delimiter) const
{
	QueryFrame frame;

	QueryWhere::ConditionList list = whereCondition.conditionList();
	int count = list.count();

	if (count > 0)
	{
		frame = QueryFrame("", "(", ")" + delimiter);

		for (int i = 0; i < count-1; ++i)
			frame << _conditionClauseFrame(list[i], _boolOperator(whereCondition.relation()));

		frame << _conditionClauseFrame(list.last(), "");
	}
	else
	{
		frame = QueryFrame(_composeCondition(whereCondition.field()) + " " + delimiter, " ", "");
	}
return frame;
}

QueryFrame PostgreSqlBuilder::_joinClauseFrame(const QueryBatch &batch) const
{
	return QueryFrame(batch.name() + " " + batch.alias(), "", "");
}

QueryFrame PostgreSqlBuilder::_statementClauseFrame(const QString &tableName,
													const QStringList &fieldNames,
													const QString &delimiter) const
{
	if (fieldNames.isEmpty())
		return QueryFrame(tableName, "", "");

	QueryFrame frame("", tableName + "(", ")");

	for (int i = 0; i < fieldNames.count(); ++i)
		frame << fieldNames[i] + ( (i < fieldNames.count()-1) ? delimiter + " " : "");

return frame;
}

QueryFrame PostgreSqlBuilder::_valuesClauseFrame(const QueryFieldList &fieldValues,
												 const QString &delimiter) const
{
	Q_ASSERT(!fieldValues.isEmpty());

	QStringList list;

	foreach (QueryField field, fieldValues)
		list << _valueFormat.toString(field.value(),
									  StringBordering | DateBordering | TimeBordering | DateTimeBordering,
									  NoPlaceholders,
									  true);

return _commonClauseFrame(list, delimiter, false, "(", ")");
}

QueryFrame PostgreSqlBuilder::_setClauseFrame(const QueryFieldList &fieldValues,
											  const QString &delimiter) const
{
	QStringList list;

	foreach (QueryField field, fieldValues)
		list << field.name() + " = " + _valueFormat.toString(field.value(),
															 StringBordering | DateBordering | TimeBordering | DateTimeBordering,
															 NoPlaceholders,
															 true);
return _commonClauseFrame(list, delimiter, false);
}

QueryFrame PostgreSqlBuilder::_parametersClauseFrame(const QueryFieldList &fieldValues,
													 const QString &delimiter) const
{
	QStringList list;

	foreach (QueryField field, fieldValues)
		list << _valueFormat.toString(field.value(),
									  StringBordering | DateBordering | TimeBordering | DateTimeBordering,
									  NoPlaceholders,
									  true);

return _commonClauseFrame(list, delimiter, false, "(", ") " + SQL_AS_RETURN_VALUE);
}

QString PostgreSqlBuilder::_betweenCondition(const QueryField &field,
											 const StringTemplate &strTempl) const
{
	QueryValue val1 = field.value(LeftValue, QueryValue());
	QueryValue val2 = field.value(RightValue, QueryValue());

	QString strVal1 = _valueFormat.toString(val1,
											StringBordering | DateBordering | TimeBordering | DateTimeBordering,
											val1.percentPlaceholders(),
											true);

	QString strVal2 = _valueFormat.toString(val2,
											StringBordering | DateBordering | TimeBordering | DateTimeBordering,
											val2.percentPlaceholders(),
											true);

	return strTempl.string(field.name(), strVal1, strVal2);
}

QString PostgreSqlBuilder::_inListCondition(const QueryField &field,
											const StringTemplate &strTempl) const
{
	Q_ASSERT(!field.valueList().isEmpty());

	QStringList list;
	foreach (QueryValue val, field.valueList())
		list << _valueFormat.toString(val,
									  StringBordering | DateBordering | TimeBordering | DateTimeBordering,
									  NoPlaceholders,
									  true);

	return strTempl.string(field.name(), _commonClauseFrame(list, ",", false).toString());
}
