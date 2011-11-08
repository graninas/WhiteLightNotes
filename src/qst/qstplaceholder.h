#ifndef QSTPLACEHOLDER_H
#define QSTPLACEHOLDER_H

#include <QString>
#include <QList>
#include <QStringList>

#include "qstglobal.h"

namespace Qst
{

class QstPlaceholder
{
private:

	QStringList  _names;

public:
	QstPlaceholder();
	explicit QstPlaceholder(const QString &placeholderName);

	QstPlaceholder(const QString &placeholderName,
				   const ValueCheckFunctor &valueCheckFunctor);

	void addName(const QString &placeholderName);

	int position(const QString &placeholderName) const;
	QStringList names() const;

	QString name() const;
};

////////////////////////////////////////////////////////////////////////////////

typedef QList<QstPlaceholder> QstPlaceholderList;

////////////////////////////////////////////////////////////////////////////////

} // End of namespace Qst

#endif // QSTPLACEHOLDER_H
