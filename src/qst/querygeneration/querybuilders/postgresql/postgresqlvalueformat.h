#ifndef POSTGRESQLVALUEFORMAT_H
#define POSTGRESQLVALUEFORMAT_H

#include "qst/querygeneration/abstractqueryvalueformat.h"

class PostgreSqlValueFormat : public AbstractQueryValueFormat
{
public:
    PostgreSqlValueFormat();
	~PostgreSqlValueFormat();

	QString toString(const QueryValue &queryValue,
					 const Qst::ApostropheBorderingFlags &borderingFlags = Qst::NotBordered,
					 const Qst::PercentPlaceholders &placeholders = Qst::NoPlaceholders,
					 const bool &substituteByNULL = false) const;

	QString toDateString(const QDate &date,
						 const bool &apostropheBorder,
						 const Qst::PercentPlaceholders &percentPlaceholders,
						 const QString &dateFormat,
						 const bool &substituteByNULL) const;

	QString toTimeString(const QTime &time,
						 const bool &apostropheBorder,
						 const Qst::PercentPlaceholders &percentPlaceholders,
						 const QString &timeFormat,
						 const bool &substituteByNULL) const;

	QString toDateTimeString(const QDateTime &dateTime,
							 const bool &apostropheBorder,
							 const Qst::PercentPlaceholders &percentPlaceholders,
							 const QString &dateTimeFormat,
							 const bool &substituteByNULL) const;

	QString percentPlaceholdersTemplate(const Qst::PercentPlaceholders &percentPlaceholders) const;

	QString format(const QString &string,
				   const bool &apostropheBorder,
				   const Qst::PercentPlaceholders &percentPlaceholders) const;
};

#endif // POSTGRESQLVALUEFORMAT_H
