#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"
#include "types.h"

class NoteHandler : public Qst::QstAbstractModelHandler
{
public:
    NoteHandler();

	static QVariant createNote(const QString   &title,
							   const QString   &noteHtmlText,
							   const QString   &noteSimpleText,
							   const QDateTime &date,
							   const QString   &theme,
							   const QString   &complexData);

	static QVariant updateNote(const QVariant  &noteID,
							   const QString   &title,
							   const QString   &noteHtmlText,
							   const QString   &noteSimpleText,
							   const QDateTime &date,
							   const QString   &theme,
							   const QString   &complexData);
};

Qst::QstBatch noteBatch(const StringListMap &filters);

QString filterCondition(const QString &filterName, const QStringList &filterItems);

#endif // NOTEHANDLER_H
