#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class NoteHandler : public Qst::QstAbstractModelHandler
{
public:
    NoteHandler();

	static QVariant createNote(const QVariant &noteHtmlText,
							   const QVariant &noteSimpleText,
							   const QVariant &date);
};

Qst::QstBatch noteBatch(const Qst::QstVariantListMap &filters = Qst::QstVariantListMap());

#endif // NOTEHANDLER_H
