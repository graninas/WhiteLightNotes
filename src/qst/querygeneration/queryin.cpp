#include "queryin.h"


using namespace Qst;

QueryIn::QueryIn()
{
}

QueryIn::QueryIn(const QString &fieldName,
				 const QVariantList &varList,
				 const Qst::Functor &functor)
	:
	  _field(QueryField(fieldName, QueryValueList(), functor, Qst::ClauseWhere))
{
	Q_ASSERT(functor == Qst::InList
			 || functor == Qst::NotInList);

	foreach (QVariant var, varList)
		_field.addValue(QueryValue(var));
}

QueryIn::QueryIn(const QString &fieldName,
				 const QstPlaceholder &placeholder,
				 const Qst::Functor &functor)
	:
	  _field(QueryField(fieldName, placeholder.name(), functor))
{
	Q_ASSERT(functor == Qst::InList
			 || functor == Qst::NotInList);
}

QueryField QueryIn::field() const
{
	return _field;
}
