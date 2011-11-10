/****************************************************************************
** QST 0.6.2 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the QueryGeneration module of the QsT SQL Tools.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: http://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** author (graninas@gmail.com).
**
****************************************************************************/

#include "querybuilddirector.h"

using namespace Qst;

QueryBuildDirector::QueryBuildDirector()
{
}

// Создает глобальный фрейм, в котором будет лежать весь запрос в виде подфреймов.
// Обрабатывает batch как пакет, содержащий подзапрос.
QueryFrame QueryBuildDirector::build(const QueryBatch &batch,
									 AbstractQueryBuilder *builder)
{
	Q_ASSERT(builder != NULL);

	QueryFrame frame = builder->makeQueryFrame(batch);
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
		QueryBatchList batchList = batch.batchList(clause);

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


