#ifndef TAGGEDNOTEHANDLER_H
#define TAGGEDNOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TaggedNoteHandler : public Qst::QstAbstractModelHandler
{
public:
    TaggedNoteHandler();

	static void createTaggedNote(const QVariant &tagID,
								 const QVariant &noteID);
	static void deleteTaggedNotes(const QVariant &noteID);
	static void updateNoteTags(const QVariant &noteID,
							   const QStringList &tagList);
	static QStringList tagList(const QVariant &noteID);

};

#endif // TAGGEDNOTEHANDLER_H
