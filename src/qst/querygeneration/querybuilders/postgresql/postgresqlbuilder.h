#ifndef POSTGRESQLBUILDER_H
#define POSTGRESQLBUILDER_H

#include "qst/querygeneration/abstractquerybuilder.h"
#include "postgresqlvalueformat.h"

class PostgreSqlBuilder : public AbstractQueryBuilder
{
private:

	PostgreSqlValueFormat _valueFormat;

public:
    PostgreSqlBuilder();

	virtual QueryScheme queryScheme(const Qst::QueryType &queryType) const;

	virtual QueryFrame makeQueryFrame(const QueryBatch &queryBatch,
									  const bool &isSubquery = false) const;
	virtual QueryFrame makeKeywordFrame(const Qst::QueryClause &queryClause) const;
	virtual QueryFrame makeClauseItemFrame(const QueryBatch &batch,
										   const bool &delimiterEnded) const;

	QueryBatchList validClauseBatches(const Qst::QueryClause &queryClause,
									  const QueryBatchList &batchList) const;

private:

	virtual QString _composeCondition(const QueryField &field) const;

	virtual QueryFrame _commonClauseFrame(QStringList itemsList,
										  QString delimiter,
										  const bool &delimiterEnded,
										  const QString &leftBracket = QString(),
										  const QString &rightBracket = QString()) const;

	virtual QueryFrame _conditionClauseFrame(const QueryWhere &whereCondition,
											 const QString &delimiter) const;
	virtual QueryFrame _joinClauseFrame(const QueryBatch &batch) const;
	virtual QueryFrame _statementClauseFrame(const QString &tableName,
											 const QStringList &fieldNames,
											 const QString &delimiter) const;
	virtual QueryFrame _valuesClauseFrame(const QueryFieldList &fieldValues,
										  const QString &delimiter) const;
	virtual QueryFrame _setClauseFrame(const QueryFieldList &fieldValues,
									   const QString &delimiter) const;
	virtual QueryFrame _parametersClauseFrame(const QueryFieldList &fieldValues,
											  const QString &delimiter) const;

	virtual QString _betweenCondition(const QueryField &field,
									  const StringTemplate &strTempl) const;

	virtual QString _inListCondition(const QueryField &field,
									 const StringTemplate &strTempl) const;
};

#endif // POSTGRESQLBUILDER_H
