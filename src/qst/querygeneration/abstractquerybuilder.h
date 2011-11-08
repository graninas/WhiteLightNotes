#ifndef ABSTRACTQUERYBUILDER_H
#define ABSTRACTQUERYBUILDER_H

#include "qst/qstfield.h"
#include "stringtemplate.h"

#include "queryframe.h"
#include "queryframeaccesory.h"

#include "querybatch.h"
#include "queryscheme.h"

#include "querywhere.h"

#include <QStringList>
#include <QMap>


typedef QMap<Qst::QueryClause, QueryAccessory> QueryClauseAccessoryMap;


class AbstractQueryBuilder
{
protected:

	QueryClauseAccessoryMap _accessories;

public:
	AbstractQueryBuilder();

	virtual QueryScheme queryScheme(const Qst::QueryType &queryType) const = 0;

	virtual QueryFrame makeQueryFrame(const QueryBatch &queryBatch,
									  const bool &isSubquery = false) const = 0;
	virtual QueryFrame makeKeywordFrame(const Qst::QueryClause &queryClause) const = 0;
	virtual QueryFrame makeClauseItemFrame(const QueryBatch &batch,
										   const bool &delimiterEnded) const = 0;

	virtual QueryBatchList validClauseBatches(const Qst::QueryClause &queryClause,
											  const QueryBatchList &batchList) const;

protected:

	virtual void _addQueryAccessory(const Qst::QueryClause &clause,
									const QueryAccessory &accessory);
	virtual QueryAccessory _queryAccessory(const Qst::QueryClause &clause) const;

	virtual StringTemplate _conditionTemplate(const Qst::Functor &functor) const;

	virtual QString _itemsDelimiter(const Qst::QueryClause &clause) const;
	virtual QString _boolOperator(const Qst::Relation &boolOperator) const;
};


#endif // ABSTRACTQUERYBUILDER_H

