#include "querybuilddirector.h"

using namespace Qst;

QueryBuildDirector::QueryBuildDirector()
{
}

QueryFrame QueryBuildDirector::build(const QueryBatch &batch,
									 AbstractQueryBuilder *builder)
{
	Q_ASSERT(builder != NULL);

	// Создает глобальный фрейм, в котором будет лежать весь запрос в виде подфреймов.
	QueryFrame frame = builder->makeQueryFrame(batch);

	// Обрабатывает batch как пакет, содержащий подзапрос.
	buildSubquery(batch, &frame, builder);
return frame;
}

void QueryBuildDirector::buildSubquery(const QueryBatch &batch,
									   QueryFrame *frame,
									   AbstractQueryBuilder *builder)
{
	QueryScheme scheme = builder->queryScheme(batch.queryType());
	QueryClause clause = scheme.nextClause();

	while (clause != NoClause)
	{
		QueryBatchList batchList = batch.batches(clause);

		if (!batchList.isEmpty())
			buildClause(clause, batchList, frame, builder);

		clause = scheme.nextClause();
	}
}

void QueryBuildDirector::buildClause(const QueryClause &queryClause,
									 const QueryBatchList &batches,
									 QueryFrame *frame,
									 AbstractQueryBuilder *builder)
{
	QueryBatchList bl = builder->validClauseBatches(queryClause, batches);
	if (bl.isEmpty())
		return;

	// Фрейм, содержащий ключевое слово секции.
	QueryFrame *keywordFrame = frame->appendFrame(builder->makeKeywordFrame(queryClause));

	for (int j = 0; j < bl.count(); ++j)
	{
		/* case batches[j].queryType() of
			   QueryUndefined -> пакет batches[j] - секция.
			   _ -> пакет batches[j] - подзапрос. */

		if (bl[j].queryType() == QueryUndefined)
			keywordFrame->appendFrame(builder->makeClauseItemFrame(bl[j], j < bl.count()-1));
		else
		{
		QueryFrame inclFr = builder->makeQueryFrame(bl[j], true);

			buildSubquery(bl[j], &inclFr, builder);

		keywordFrame->appendFrame(inclFr);
		}
	}
}


