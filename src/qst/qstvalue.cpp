#include "qstvalue.h"

namespace Qst
{

QstValue::QstValue()
{

}

QstValue::QstValue(const QVariant &value,
				   const Functor &functor,
				   const Qst::PercentPlaceholders &percentPlaceholders)
	:
	  _queryValue(QueryValue(value, percentPlaceholders)),
	  _functor(functor)
{
}

QueryValue QstValue::queryValue() const
{
	return _queryValue;
}

Functor QstValue::functor() const
{
	return _functor;
}




} // End of namespace Qst
