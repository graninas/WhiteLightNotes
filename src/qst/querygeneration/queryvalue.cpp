#include "queryvalue.h"

#include <QDebug>

using namespace Qst;

QueryValue::QueryValue()
	:
	  _value(QVariant()),
	  _percentPlacehodlers(NoPlaceholders)
{
}

QueryValue::QueryValue(const QVariant &value,
					   const PercentPlaceholders &percentPlaceholders)
	:
	  _value(value),
	  _percentPlacehodlers(percentPlaceholders)
{
}

QVariant QueryValue::value() const
{
	return _value;
}

void QueryValue::setValue(const QVariant &value)
{
	_value = value;
}

PercentPlaceholders QueryValue::percentPlaceholders() const
{
	return _percentPlacehodlers;
}

void QueryValue::setPercentPlaceholders(const PercentPlaceholders &percentPlaceholders)
{
	_percentPlacehodlers = percentPlaceholders;
}

bool QueryValue::isNull() const
{
	return _value.isNull();
}

bool QueryValue::isValid() const
{
	return _value.isValid();
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QueryValue &v)
{
#ifndef Q_BROKEN_DEBUG_STREAM
	dbg.nospace() << "QueryValue(value = " << v.value();
	dbg.nospace() << ", percentPlaceholders = " << v.percentPlaceholders();

	return dbg.space();
#else
	qWarning("This compiler doesn't support streaming QueryValue to QDebug");
	return dbg;
	Q_UNUSED(v);
#endif
}
#endif
