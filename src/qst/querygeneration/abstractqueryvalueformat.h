#ifndef ABSTRACTQUERYVALUEFORMAT_H
#define ABSTRACTQUERYVALUEFORMAT_H

#include "queryvalue.h"

#include <QDate>
#include <QDateTime>
#include <QString>

class AbstractQueryValueFormat	// FIX ME: documentation // FULL REWRITE
{
public:
    AbstractQueryValueFormat();
	virtual ~AbstractQueryValueFormat() = 0;

	virtual QString toString(const QueryValue &queryValue,
							 const Qst::ApostropheBorderingFlags &borderingFlags = Qst::NotBordered,
							 const Qst::PercentPlaceholders &placeholders = Qst::NoPlaceholders,
							 const bool &substituteByNULL = false) const = 0;

	virtual QString toDateString(const QDate &date,
								 const bool &apostropheBorder,
								 const Qst::PercentPlaceholders &percentPlaceholders,
								 const QString &dateFormat,
								 const bool &substituteByNULL) const = 0;

	virtual QString toTimeString(const QTime &time,
								 const bool &apostropheBorder,
								 const Qst::PercentPlaceholders &percentPlaceholders,
								 const QString &timeFormat,
								 const bool &substituteByNULL) const = 0;

	virtual QString toDateTimeString(const QDateTime &dateTime,
									 const bool &apostropheBorder,
									 const Qst::PercentPlaceholders &percentPlaceholders,
									 const QString &dateTimeFormat,
									 const bool &substituteByNULL) const = 0;

	virtual QString percentPlaceholdersTemplate
					(const Qst::PercentPlaceholders &percentPlaceholders) const = 0;

	virtual QString format(const QString &string,
						   const bool &apostropheBorder,
						   const Qst::PercentPlaceholders &percentPlaceholders) const = 0;
};

#endif // ABSTRACTQUERYVALUEFORMAT_H
