#ifndef QUERYVALUE_H
#define QUERYVALUE_H

#include "qst/qstglobal.h"

#include <QVariant>
#include <QList>

class QueryValue // FIX ME: documentation // Full rewrite
{

private:

	QVariant _value;

	Qst::PercentPlaceholders	 _percentPlacehodlers;

public:

	QueryValue();

	explicit QueryValue(const QVariant &value,
						const Qst::PercentPlaceholders &percentPlaceholders = Qst::NoPlaceholders);

	QVariant value() const;
	void     setValue(const QVariant &value);

	Qst::PercentPlaceholders percentPlaceholders() const;
	void setPercentPlaceholders(const Qst::PercentPlaceholders &percentPlaceholders);

	bool isNull() const;
	bool isValid() const;

	friend bool operator==(const QueryValue &val1, const QueryValue val2)
	{
		return val1._value == val2._value
				&& val1._percentPlacehodlers == val2._percentPlacehodlers;
	}
};

////////////////////////////////////////////////////////////////////////////////

typedef QList<QueryValue>         QueryValueList;
typedef QMap<QString, QueryValue> QueryValueMap;

////////////////////////////////////////////////////////////////////////////////

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const QueryValue &);
#endif


#endif // QUERYVALUE_H
