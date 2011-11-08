#ifndef QSTVALUE_H
#define QSTVALUE_H

#include "qst/querygeneration/queryvalue.h"

namespace Qst
{

class QstValue
{
private:

	QueryValue _queryValue;
	Functor    _functor;

public:

	QstValue();

	QstValue(const QVariant &value,
			 const Functor &functor,
			 const Qst::PercentPlaceholders &percentPlaceholders = LeftRightPercents);

	QueryValue queryValue() const;
	Functor    functor() const;
};

} // End of namespace Qst

#endif // QSTVALUE_H
