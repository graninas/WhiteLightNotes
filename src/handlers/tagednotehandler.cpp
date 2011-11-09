#include "tagednotehandler.h"

using namespace Qst;

TagedNoteHandler::TagedNoteHandler()
{
}


void TagedNoteHandler::createTagedNote(const QVariant &tagID,
									   const QVariant &noteID)
{
	QstBatch b;
	b.insert("taged_note", QStringList() << "tag_id" << "note_id");
	b.values(QVariantList() << tagID << noteID);
	execute(b);
}

void TagedNoteHandler::deleteTagedNotes(const QVariant &noteID)
{
	QstBatch b;
	b.deleteFrom("taged_note");
	b.where("note_id", noteID);
	execute(b);
}


Qst::QstBatch tagedNoteBatch()
{
	QstBatch batch;
	batch << "taged_note"
		  << QstField(RolePrimaryKey, "id")
		  << QstField("tag_id")
		  << QstField("note_id");
	return batch;
}
