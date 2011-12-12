#include "taggednotehandler.h"

#include "taghandler.h"

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
	b.where("note_id", noteID, Equal);
	execute(b);
}

void TaggedNoteHandler::updateNoteTags(const QVariant    &noteID,
									   const QStringList &tagList)
{
	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TaggedNoteHandler::deleteTaggedNotes(noteID);

	QVariant tagID;
	QVariant tagPriority;
	foreach (QString tag, tagList)
	{
		if (tag == "All")           tagPriority = 0;
		else if (tag == "Untagged") tagPriority = 1;
		else                        tagPriority = 2;
		tagID = TagHandler::createTag(tag, tagPriority);
		Q_ASSERT(!tagID.isNull());
		createTaggedNote(tagID, noteID);
	}
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
