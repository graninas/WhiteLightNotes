#ifndef TAGEDNOTEHANDLER_H
#define TAGEDNOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TagedNoteHandler : public Qst::QstAbstractModelHandler
{
public:
    TagedNoteHandler();

	static void createTagedNote(const QVariant &tagID,
								const QVariant &noteID);
	static void deleteTagedNotes(const QVariant &noteID);

};

Qst::QstBatch tagedNoteBatch();

#endif // TAGEDNOTEHANDLER_H
