#ifndef QUERYBUILDDIRECTOR_H
#define QUERYBUILDDIRECTOR_H

#include "abstractquerybuilder.h"
#include "qst/qstglobal.h"


class QueryBuildDirector
{
private:

	AbstractQueryBuilder *_builder;

public:
    QueryBuildDirector();

	QueryFrame build(const QueryBatch &batch, AbstractQueryBuilder *builder);

	void buildSubquery(const QueryBatch &batch,
					   QueryFrame *frame,
					   AbstractQueryBuilder *builder);

	void buildClause(const Qst::QueryClause &queryClause,
					 const QueryBatchList &batches,
					 QueryFrame *frame,
					 AbstractQueryBuilder *builder);
};

#endif // QUERYBUILDDIRECTOR_H
