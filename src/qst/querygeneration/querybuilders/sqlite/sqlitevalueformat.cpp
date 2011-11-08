#include "sqlitevalueformat.h"

using namespace Qst;

SqLiteValueFormat::SqLiteValueFormat()
{
}

SqLiteValueFormat::~SqLiteValueFormat()
{
}

QString SqLiteValueFormat::toString(const QueryValue &queryValue,
						const Qst::ApostropheBorderingFlags &borderingFlags,
						const Qst::PercentPlaceholders &placeholders,
						const bool &substituteByNULL) const
{
	return AbstractQueryValueFormat::toString(queryValue,
											  borderingFlags,
											  placeholders,
											  substituteByNULL);
}

QString SqLiteValueFormat::toDateString(const QDate &date,
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

QString SqLiteValueFormat::toTimeString(const QTime &time,
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

QString SqLiteValueFormat::toDateTimeString(const QDateTime &dateTime,
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

QString SqLiteValueFormat::percentPlaceholdersTemplate
		(const Qst::PercentPlaceholders &percentPlaceholders) const
{
	return AbstractQueryValueFormat::percentPlaceholdersTemplate(percentPlaceholders);
}

QString SqLiteValueFormat::format(const QString &string,
									  const bool &apostropheBorder,
									  const Qst::PercentPlaceholders &percentPlaceholders) const
{
	return AbstractQueryValueFormat::format(string,
											apostropheBorder,
											percentPlaceholders);
}
