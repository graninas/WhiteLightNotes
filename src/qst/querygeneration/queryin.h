#ifndef QUERYIN_H
#define QUERYIN_H

#include <QString>
#include <QVariantList>

#include "queryfield.h"
#include "qst/qstplaceholder.h"

class QueryIn
{
private:

	QueryField _field;

public:
    QueryIn();

	QueryIn(const QString &fieldName,
			const QVariantList &varList,
			const Qst::Functor &functor = Qst::InList);

	QueryIn(const QString &fieldName,
			const Qst::QstPlaceholder &placeholder,
			const Qst::Functor &functor = Qst::InList);

	QueryField field() const;
};

#endif // QUERYIN_H
