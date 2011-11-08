#ifndef QUERYFIELD_H
#define QUERYFIELD_H

#include "qst/qstglobal.h"
#include "queryvalue.h"


#include <QList>

class QueryField // FIX ME: documentation
{

private:

	QString            _name;
	QueryValueList     _valueList;
	Qst::Functor       _functor;
	Qst::QueryClause   _clause;

	QString _placeholderName;

public:

	QueryField();
	QueryField(const QString &name);

	QueryField(const QString &name,
			   const QueryValue &value,
			   const Qst::Functor &functor = Qst::TypeDependedFunctor,
			   const Qst::QueryClause clause = Qst::ClauseValued_Mask);

	QueryField(const QString &name,
			   const QueryValue &value1,
			   const QueryValue &value2,
			   const Qst::QueryClause clause = Qst::ClauseWhere);

	explicit QueryField(const QueryValue &value,
						const Qst::QueryClause clause = Qst::ClauseParameters);

	QueryField(const QString &name,
			   const Qst::QueryClause clause);

	QueryField(const QString &name,
			   const QueryValueList &valList,
			   const Qst::Functor &functor,
			   const Qst::QueryClause &clause);

	QueryField(const QString &name,
			   const QString &placeholderName,
			   const Qst::Functor &functor /*= Qst::TypeDependedFunctor*/,
			   const Qst::QueryClause &clause = Qst::ClauseWhere);

	QString name() const;
	void setName(const QString &name);

	bool testClause(const Qst::QueryClause &clause) const;
	void setClause(const Qst::QueryClause &clause);
	Qst::QueryClause clause() const;

	QueryValue value(const Qst::BetweenFilterValueOrder &order,
					 const QueryValue &defaultValue = QueryValue()) const;
	QueryValue value(const int &index = 0,
					 const QueryValue &defaultValue = QueryValue()) const;

	void addValue(const QueryValue &value);

	QueryValueList valueList() const;
	void setValueList(const QueryValueList &list);

	Qst::Functor functor() const;
	void setFunctor(const Qst::Functor &functor);

	bool hasValue(const Qst::BetweenFilterValueOrder &order = Qst::LeftValue) const;
	bool hasValue(const int &index = 0) const;

	bool isValuesValid() const;
	bool isValid() const;

	void updatePlaceholder(const QString &placeholderName,
						   const QueryValue &value,
						   const Qst::Functor &functor);

	void updatePlaceholder(const QString &placeholderName,
						   const QVariantList &varList,
						   const Qst::Functor &functor);

	void resetPlaceholder();

	QString placeholderName() const;

	friend bool operator == (const QueryField &val1, const QueryField &val2)
	{
		return	(val1._name == val2._name)
				&& val1._functor == val2._functor
				&& val1._valueList == val2._valueList
				;
	}

private:

	void _setFunctor(const Qst::Functor &functor);
	void _setTypeDependedFunctor();

};

////////////////////////////////////////////////////////////////////////////////

typedef QList<QueryField>	QueryFieldList;

////////////////////////////////////////////////////////////////////////////////

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const QueryField &);
#endif


#endif // QUERYFIELD_H
