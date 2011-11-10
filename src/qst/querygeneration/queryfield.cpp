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

#include "queryfield.h"

#include <QDebug>

using namespace Qst;

QueryField::QueryField()
	:
	  _name(QString()),
	  _functor(NoFunctor),
	  _clause(NoClause)
{
}

QueryField::QueryField(const QString &name)
	:
	  _name(name),
	  _functor(NoFunctor),
	  _clause(ClauseSelect)
{
}

QueryField::QueryField(const QString &name,
					   const QueryValue &value,
					   const Functor &functor,
					   const QueryClause clause)
	:
	  _name(name),
	  _functor(functor),
	  _clause(clause)
{
	_valueList.append(value);

	if (functor == TypeDependedFunctor)
		_setTypeDependedFunctor();
}

QueryField::QueryField(const QString &name,
					   const QueryValue &value1,
					   const QueryValue &value2,
					   const QueryClause clause)
	:
	  _name(name),
	  _functor(Between),
	  _clause(clause)
{
	Q_ASSERT(value1.value().type() == value2.value().type());
	Q_ASSERT(!value1.isNull());
	Q_ASSERT(!value2.isNull());

	QueryValue val = QueryValue(value1);

	_valueList.append(val);
	_valueList.append(value2);
}

QueryField::QueryField(const QueryValue &value,
					   const QueryClause clause)
	:
	  _name(QString()),
	  _functor(NoFunctor),
	  _clause(clause)
{
	_valueList.append(value);
}

QueryField::QueryField(const QString &name,
					   const QueryClause clause)
	:
	  _name(name),
	  _clause(clause)
{
}

QueryField::QueryField(const QString &name,
					   const QueryValueList &valList,
					   const Qst::Functor &functor,
					   const QueryClause &clause)
	:
	  _name(name),
	  _valueList(valList),
	  _functor(functor),
	  _clause(clause)
{
}

QueryField::QueryField(const QString &name,
					   const QString &placeholderName,
					   const Qst::Functor &functor,
					   const Qst::QueryClause &clause)
	:
	  _name(name),
	  _functor(functor),
	  _clause(clause),
	  _placeholderName(placeholderName)
{
	if (_placeholderName.isEmpty())
		_placeholderName = name;

	_valueList.append(QueryValue());
}

QString QueryField::name() const
{
	return _name;
}

void QueryField::setName(const QString &name)
{
	_name = name;
}

bool QueryField::testClause(const QueryClause &clause) const
{
	return _clause & clause;
}

void QueryField::setClause(const QueryClause &clause)
{
	_clause = clause;
}

QueryClause	QueryField::clause() const
{
	return _clause;
}

QueryValue QueryField::value(const BetweenFilterValueOrder &order,
							 const QueryValue &defaultValue) const
{
	if (!hasValue(order))
	{
		qDebug() << "Warring! Trying to get unexisted value by QueryField::value() function.";
		return defaultValue;
	}

	return _valueList.value((int)order, QueryValue());
}

QueryValue QueryField::value(const int &index,
							 const QueryValue &defaultValue) const
{
	return _valueList.value(index, defaultValue);
}

void QueryField::addValue(const QueryValue &value)
{
	_valueList.append(value);
}

QueryValueList QueryField::valueList() const
{
	return _valueList;
}

void QueryField::setValueList(const QueryValueList &list)
{
	_valueList = list;
}

Functor QueryField::functor() const
{
	return _functor;
}

void QueryField::setFunctor(const Qst::Functor &functor)
{
	_functor = functor;
}

bool QueryField::hasValue(const BetweenFilterValueOrder &order) const
{
	return hasValue((int)order);
}

bool QueryField::hasValue(const int &index) const
{
	return index < _valueList.count() && index >= 0;
}

bool QueryField::isValuesValid() const
{
	if (_valueList.empty())
		return false;

	for (int i = 0; i < _valueList.size(); ++i)
		if (!_valueList[i].isValid())
			return false;

return true;
}

bool QueryField::isValid() const
{
	if (_name.isEmpty() && !isValuesValid())
		return false;

	if ((_clause & ClauseValued_Mask) && !isValuesValid())
		return false;

	if ((_clause & ClauseHasFieldName_Mask) && _name.isEmpty())
		return false;

return true;
}

void QueryField::updatePlaceholder(const QString &placeholderName,
								   const QueryValue &value,
								   const Qst::Functor &functor)
{
	if (placeholderName != _placeholderName)
		return;

	_valueList.clear();
	_valueList.append(value);

	if (functor != Qst::NoFunctor)
		_setFunctor(functor);
	else
		if (_functor == Qst::TypeDependedFunctor)
			_setTypeDependedFunctor();
}

void QueryField::updatePlaceholder(const QString &placeholderName,
								   const QVariantList &varList,
								   const Qst::Functor &functor)
{
	Q_ASSERT(functor == Qst::InList
			 || functor == Qst::NotInList
			 || functor == Qst::NoFunctor);

	if (placeholderName != _placeholderName)
		return;

	_valueList.clear();
	foreach (QVariant var, varList)
		_valueList.append(QueryValue(var));

	if (functor == Qst::InList || functor == Qst::NotInList)
		_functor = functor;
	else
		if (_functor != Qst::InList && _functor != Qst::NotInList)
			_functor = Qst::InList;
}

void QueryField::resetPlaceholder()
{
	_placeholderName = QString();
}

QString QueryField::placeholderName() const
{
	return _placeholderName;
}

void QueryField::_setFunctor(const Qst::Functor &functor)
{
	Q_ASSERT(functor != Qst::NoFunctor);

	if (functor == Qst::TypeDependedFunctor)
		_setTypeDependedFunctor();
	else
		_functor = functor;
}

void QueryField::_setTypeDependedFunctor()
{
	if (_valueList.count() > 1)
		_functor = Qst::InList;
	else
		switch (_valueList.first().value().type())
		{
		case QVariant::ByteArray:
		case QVariant::String:
			_functor = Like;
			_valueList.first().setPercentPlaceholders(LeftRightPercents);
			break;
		default:
			_functor = Equal;
		};
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QueryField &f)
{
#ifndef Q_BROKEN_DEBUG_STREAM
	dbg.nospace() << "QueryField(name = " << f.name();
	dbg.nospace() << ", valueList = " << f.valueList();
	dbg.nospace() << ", functor = " << f.functor();
	dbg.nospace() << ", clause = " << f.clause() << ").";

	return dbg.space();
#else
	qWarning("This compiler doesn't support streaming QueryField to QDebug");
	return dbg;
	Q_UNUSED(f);
#endif
}
#endif
