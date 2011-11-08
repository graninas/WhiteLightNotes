#ifndef TAGEDNOTEHANDLER_H
#define TAGEDNOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TagedNoteHandler : public Qst::QstAbstractModelHandler
{
public:
    TagedNoteHandler();

	void deleteTagedNotes(const QVariant &noteID) const;
	void createTagedNote(const QVariant &tagID,
						 const QVariant &noteID) const;
};

Qst::QstBatch tagedNoteBatch();

#endif // TAGEDNOTEHANDLER_H
