#include "abstractquerybuilder.h"

using namespace Qst;

AbstractQueryBuilder::AbstractQueryBuilder()
{
}

QueryScheme AbstractQueryBuilder::queryScheme(const QueryType &queryType) const
{
	switch (queryType)
	{
	case QuerySelect:
		return QueryScheme()
				<< ClauseSelect
				<< ClauseFrom
				<< ServiceJoinClause_Mask
				<< ClauseWhere
				<< ClauseGroupBy
				<< ClauseHaving
				<< ClauseOrderBy
				;

	// Все join-пакеты отделены друг от друга, в каждом пакете только один JOIN.
	// Только один из ClauseXYZJoin будет задействован при обработке каждого пакета.
	case ServiceQueryJoin:
		return QueryScheme()
				<< ClauseLeftJoin
				<< ClauseRightJoin
				<< ClauseInnerJoin
				<< ClauseFullJoin
				<< ClauseOn
				;

	case QueryInsert:
		return QueryScheme()
				<< ClauseInsert
				<< ClauseValues
				;

	case QueryUpdate:
		return QueryScheme()
				<< ClauseUpdate
				<< ClauseSet
				<< ClauseWhere
				;

	case QueryDelete:
		return QueryScheme()
				<< ClauseDelete
				<< ClauseWhere
				;

	case QueryExecute:
		return QueryScheme()
				<< ClauseExecute
				<< ClauseParameters
				;

	case UserDefinedQuery:
		return QueryScheme()
				<< UserDefinedClauses;

	default: Q_ASSERT(false);
	}
return QueryScheme();
}

QueryFrame AbstractQueryBuilder::makeQueryFrame(const QueryBatch &queryBatch,
												const bool &isSubquery) const
{
	if (!isSubquery)
		return QueryFrame();

return QueryFrame("",
				  _queryAccessory(queryBatch.queryClause()).leftSubqueryBracket(),
				  _queryAccessory(queryBatch.queryClause()).rightSubqueryBracket() + queryBatch.alias());
}

QueryFrame AbstractQueryBuilder::makeKeywordFrame(const QueryClause &queryClause) const
{
	return QueryFrame(" "+this->_queryAccessory(queryClause).clauseWord()+" ", "", "");
}

/*! Компонует один фрейм для одного элемента секции. */
QueryFrame AbstractQueryBuilder::makeClauseItemFrame(const QueryBatch &batch,
													 const bool &delimiterEnded) const
{
	Q_UNUSED(batch)
	Q_UNUSED(delimiterEnded)

	return QueryFrame();
}

QueryBatchList AbstractQueryBuilder::validClauseBatches(const QueryClause &queryClause,
														const QueryBatchList &batchList) const
{
	Q_UNUSED(queryClause)
	Q_UNUSED(batchList)

	return QueryBatchList();
}

void AbstractQueryBuilder::_addQueryAccessory(const Qst::QueryClause &clause,
											  const QueryAccessory &accessory)
{
	_accessories[clause] = accessory;
}

QueryAccessory AbstractQueryBuilder::_queryAccessory(const QueryClause &clause) const
{
	Q_ASSERT(clause != NoClause);
	Q_ASSERT(_accessories.contains(clause));

	return _accessories.value(clause, QueryAccessory());
}

StringTemplate AbstractQueryBuilder::_conditionTemplate(const Functor &functor) const
{
	//Здесь %1 - поле, %2 - значение1, %3 - значение2.

		switch(functor)
		{
		case Like:			return StringTemplate(2, "%1 LIKE %2");
		case Equal:			return StringTemplate(2, "%1 = %2");
		case NotEqual:		return StringTemplate(2, "%1 <> %2");
		case Less:			return StringTemplate(2, "%1 < %2");
		case Greater:		return StringTemplate(2, "%1 > %2");
		case LessEqual:		return StringTemplate(2, "%1 <= %2");
		case GreaterEqual:	return StringTemplate(2, "%1 >= %2");
		case Between:		return StringTemplate(3, "%1 BETWEEN %2 AND %3");
		case IsNull:		return StringTemplate(1, "%1 IS NULL");
		case IsNotNull:		return StringTemplate(1, "%1 IS NOT NULL");
		case NotEqualOrNull:		return StringTemplate(2, "(%1 <> %2 OR %1 IS NULL)");
		case EqualOrNull:			return StringTemplate(2, "(%1 == %2 OR %1 IS NULL)");
		case LessOrNull:			return StringTemplate(2, "(%1 < %2 OR %1 IS NULL)");
		case GreaterOrNull:			return StringTemplate(2, "(%1 > %2 OR %1 IS NULL)");
		case LessEqualOrNull:		return StringTemplate(2, "(%1 <= %2 OR %1 IS NULL)");
		case GreaterEqualOrNull:	return StringTemplate(2, "(%1 >= %2 OR %1 IS NULL)");
		case LikeOrNull:			return StringTemplate(2, "(%1 LIKE %2 OR %1 IS NULL)");
		case BitwiseOr:				return StringTemplate(2, "%1 | %2");
		case BitwiseAnd:			return StringTemplate(2, "%1 & %2");
		case BitwiseXor:			return StringTemplate(2, "%1 # %2");
		case BitwiseNot:			return StringTemplate(1, "~%1");
		case BitwiseShiftLeft:		return StringTemplate(2, "%1 << %2");
		case BitwiseShiftRight:		return StringTemplate(2, "%1 >> %2");
		case InList:				return StringTemplate(2, "%1 IN (%2)");
		case NotInList:				return StringTemplate(2, "%1 NOT IN (%2)");

		case TypeDependedFunctor: Q_ASSERT(false);
		case NoFunctor:	Q_ASSERT(false);
		};
	return StringTemplate();
}

QString AbstractQueryBuilder::_itemsDelimiter(const QueryClause &clause) const
{
	switch (clause)
	{
	case ClauseSelect:
	case ClauseFrom:
	case ClauseOrderBy: return ",";

	case ClauseInsert:
	case ClauseSet:
	case ClauseParameters:
	case ClauseValues: return ",";

	default: Q_ASSERT(false);
	}
return QString();
}

QString AbstractQueryBuilder::_boolOperator(const Relation &boolOperator) const
{
	switch (boolOperator)
	{
	case And: return "AND";
	case Or: return "OR";

	default: Q_ASSERT(false);
	}
return QString();
}

