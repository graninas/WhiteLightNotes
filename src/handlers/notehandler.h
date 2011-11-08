#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class NoteHandler : public Qst::QstAbstractModelHandler
{
public:
    NoteHandler();

	static QVariant createNote(const QVariant &noteHtmlText,
							   const QVariant &date);
};

Qst::QstBatch noteBatch();

#endif // NOTEHANDLER_H
