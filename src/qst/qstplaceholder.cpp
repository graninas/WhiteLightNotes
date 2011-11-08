#include "qstplaceholder.h"

namespace Qst
{

QstPlaceholder::QstPlaceholder()
{
}

QstPlaceholder::QstPlaceholder(const QString &placeholderName)
{
	_names.append(placeholderName);
}

QstPlaceholder::QstPlaceholder(const QString &placeholderName,
							   const ValueCheckFunctor &valueCheckFunctor)
{
	_names.append(placeholderName);
	Q_UNUSED(valueCheckFunctor);
}

void QstPlaceholder::addName(const QString &placeholderName)
{
	Q_ASSERT(!placeholderName.isEmpty());

	_names.append(placeholderName);
}

int QstPlaceholder::position(const QString &placeholderName) const
{
	return _names.indexOf(placeholderName);
}

QStringList QstPlaceholder::names() const
{
	return _names;
}

QString QstPlaceholder::name() const
{
	if (_names.isEmpty())
		return QString();
return _names.first();
}

}
