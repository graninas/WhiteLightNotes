#include "taggednotehandler.h"

using namespace Qst;

TaggedNoteHandler::TaggedNoteHandler()
{
}


void TaggedNoteHandler::createTaggedNote(const QVariant &tagID,
										 const QVariant &noteID)
{
	QstBatch b;
	b.insert("tagged_note", QStringList() << "tag_id" << "note_id");
	b.values(QVariantList() << tagID << noteID);
	execute(b);
}

void TaggedNoteHandler::deleteTaggedNotes(const QVariant &noteID)
{
	QstBatch b;
	b.deleteFrom("tagged_note");
	b.where("note_id", noteID);
	execute(b);
}


Qst::QstBatch taggedNoteBatch()
{
	QstBatch batch;
	batch << "tagged_note"
		  << QstField(RolePrimaryKey, "id")
		  << QstField("tag_id")
		  << QstField("note_id");
	return batch;
}
