#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class NoteHandler : public Qst::QstAbstractModelHandler
{
public:
    NoteHandler();

	static QVariant createNote(const QString &title,
							   const QString &noteHtmlText,
							   const QString &noteSimpleText,
							   const QDateTime &date,
							   const QString &complexData);
};

Qst::QstBatch noteBatch(const Qst::QstVariantListMap &filters = Qst::QstVariantListMap());

#endif // NOTEHANDLER_H
