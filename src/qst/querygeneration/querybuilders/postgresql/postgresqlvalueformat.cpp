#include "postgresqlvalueformat.h"

using namespace Qst;

PostgreSqlValueFormat::PostgreSqlValueFormat()
{
}

PostgreSqlValueFormat::~PostgreSqlValueFormat()
{
}

QString PostgreSqlValueFormat::toString(const QueryValue &queryValue,
						const Qst::ApostropheBorderingFlags &borderingFlags,
						const Qst::PercentPlaceholders &placeholders,
						const bool &substituteByNULL) const
{
	return AbstractQueryValueFormat::toString(queryValue,
											  borderingFlags,
											  placeholders,
											  substituteByNULL);
}

QString PostgreSqlValueFormat::toDateString(const QDate &date,
											const bool &apostropheBorder,
											const Qst::PercentPlaceholders &percentPlaceholders,
											const QString &dateFormat,
											const bool &substituteByNULL) const
{
	return AbstractQueryValueFormat::toDateString(date,
												  apostropheBorder,
												  percentPlaceholders,
												  dateFormat,
												  substituteByNULL);
}

QString PostgreSqlValueFormat::toTimeString(const QTime &time,
											const bool &apostropheBorder,
											const Qst::PercentPlaceholders &percentPlaceholders,
											const QString &timeFormat,
											const bool &substituteByNULL) const
{
	return AbstractQueryValueFormat::toTimeString(time,
												  apostropheBorder,
												  percentPlaceholders,
												  timeFormat,
												  substituteByNULL);
}

QString PostgreSqlValueFormat::toDateTimeString(const QDateTime &dateTime,
												const bool &apostropheBorder,
												const Qst::PercentPlaceholders &percentPlaceholders,
												const QString &dateTimeFormat,
												const bool &substituteByNULL) const
{
	return AbstractQueryValueFormat::toDateTimeString(dateTime,
													  apostropheBorder,
													  percentPlaceholders,
													  dateTimeFormat,
													  substituteByNULL);
}

QString PostgreSqlValueFormat::percentPlaceholdersTemplate
		(const Qst::PercentPlaceholders &percentPlaceholders) const
{
	return AbstractQueryValueFormat::percentPlaceholdersTemplate(percentPlaceholders);
}

QString PostgreSqlValueFormat::format(const QString &string,
									  const bool &apostropheBorder,
									  const Qst::PercentPlaceholders &percentPlaceholders) const
{
	return AbstractQueryValueFormat::format(string,
											apostropheBorder,
											percentPlaceholders);
}
