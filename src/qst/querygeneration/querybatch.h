#ifndef QUERYBATCH_H
#define QUERYBATCH_H

#include <QMap>
#include <QList>
#include <QString>
#include <QStringList>

#include "queryfield.h"
#include "querywhere.h"

class QueryBatch;

typedef QList<QueryBatch> QueryBatchList;

typedef QMap<Qst::QueryClause, QueryBatchList> QueryBatchPack;

class QueryBatch
{
public:

	typedef enum
	{
		StringSource = 1,
		BatchSource = 2
	} SourceType;

private:

	QString				_name;

	SourceType			_sourceType;
	Qst::QueryType		_queryType;

	QueryBatchPack		_batchPacks;
	QueryFieldList		_fields;

	QueryWhere			_condition;

	Qst::QueryClause    _queryClause;

public:

	QueryBatch();

	QueryBatch(const Qst::QueryType &queryType,
			   const QString &name = QString(),
			   const Qst::QueryClause &queryClause = Qst::NoClause);

	QueryBatch(const Qst::QueryClause &queryClause,
			   const QString &name);

	QueryBatch(const QString &name);

	QueryBatch(const QueryWhere &condition,
			   const Qst::QueryClause &queryClause = Qst::ClauseWhere);

	void    setName(const QString &name);
	QString name() const;
	QString alias() const;

	void             setQueryClause(const Qst::QueryClause &queryClause);
	Qst::QueryClause queryClause() const;

	void           setQueryType(const Qst::QueryType &queryType);
	Qst::QueryType queryType() const;

	QueryBatchPack batchPack() const;
	QueryBatchList batches(const Qst::QueryClause queryClause = Qst::ClauseSelect) const;

	void appendBatch(const Qst::QueryClause packClause, const QueryBatch &batch);

	QueryWhere condition(const bool &validOnly = false) const;

	bool contains(const QueryField &field) const;

	QStringList fieldNames() const;
	QStringList sourceNames() const;

	void setFields(const QueryFieldList &fields);
	QueryFieldList fields(const Qst::QueryClause &queryClause) const;

	QueryBatch & updatePlaceholder(const QString &placeholderName,
								   const QueryValue &value,
								   const Qst::Functor &functor = Qst::NoFunctor);

	QueryBatch & updatePlaceholder(const QString &placeholderName,
								   const QVariantList &varList,
								   const Qst::Functor &functor = Qst::NoFunctor);

	QueryBatch & updatePlaceholder(const QVariantMap &varMap);

	void resetPlaceholders();

	QueryBatch & operator<<(const QueryBatch &batch);
	QueryBatch & operator<<(const QueryWhere &condition);
	QueryBatch & operator<<(const QueryField &field);
	QueryBatch & operator<<(const QString &sourceName);

//////////////////////////////////////////////////////////////////

	QueryBatch & setUserDefinedQuery(const QString &query);

	QueryBatch & select(const QueryBatch &batch);
	QueryBatch & select(const QueryFieldList &fields);
	QueryBatch & select(const QStringList &fieldNames);
	QueryBatch & select(const QString &fieldName);
	QueryBatch & from(const QueryBatch &batch);
	QueryBatch & from(const QString &source);
	QueryBatch & join(const QueryBatch &batch, const QueryOn &condition);
	QueryBatch & join(const Qst::QueryClause &joinClause,
					  const QString &tableName,
					  const QueryOn &condition);
	QueryBatch & innerJoin(const QString &tableName, const QueryOn &condition);
	QueryBatch & leftJoin(const QString &tableName, const QueryOn &condition);
	QueryBatch & rightJoin(const QString &tableName, const QueryOn &condition);
	QueryBatch & fullJoin(const QString &tableName, const QueryOn &condition);

	QueryBatch & where(const QueryWhere &condition);
	QueryBatch & where(const QString &strCond);
	QueryBatch & where(const QString &fieldName,
					   const QueryValue &value);
	QueryBatch & where(const QString &fieldName,
					   const QueryValue &value1,
					   const QueryValue &value2);

	QueryBatch & where(const QString &fieldName,
					   const Qst::QstPlaceholder &placeholder,
					   const Qst::Functor &functor = Qst::TypeDependedFunctor);

	QueryBatch & groupBy(const QStringList &fieldNames);
	QueryBatch & groupBy(const QString &fieldName);
	QueryBatch & having(const QueryHaving &condition);
	QueryBatch & having(const QString &strCond);
	QueryBatch & orderBy(const QStringList &fieldNames);
	QueryBatch & orderBy(const QString &fieldName);

	QueryBatch & insert(const QString &tableName,
						const QStringList &fieldNames = QStringList());
	QueryBatch & values(const QueryFieldList &fieldValues);
	QueryBatch & values(const QueryValueList &values);
	QueryBatch & values(const QVariantList &values);

	QueryBatch & update(const QString &tableName);
	QueryBatch & set(const QueryFieldList &fields);

	QueryBatch & deleteFrom(const QString &tableName);

	QueryBatch & execute(const QString &funcName);

	QueryBatch & parameters(const QVariantList &varList);
	QueryBatch & parameters(const Qst::QstPlaceholderList &placeholderList);


	friend bool operator==(const QueryBatch &btch1, const QueryBatch btch2)
	{
		return btch1._name == btch2._name
				&& btch1._sourceType == btch2._sourceType
				&& btch1._queryType == btch2._queryType
				&& btch1._queryClause == btch2._queryClause
				&& btch1._fields == btch2._fields
				&& btch1._condition == btch2._condition
				&& btch1._batchPacks == btch2._batchPacks;
	}

private:

	void _addField(const QueryField &field);
	void _addCondition(const QueryWhere &cond);
	Qst::QueryClause _clauseInBatchPack(const Qst::QueryClause &clause) const;
};

#endif // QUERYBATCH_H
