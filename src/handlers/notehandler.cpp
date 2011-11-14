#include "notehandler.h"

using namespace Qst;

NoteHandler::NoteHandler()
{
}

QVariant NoteHandler::createNote(const QVariant &noteHtmlText,
								 const QVariant &date)
{
	QstBatch b;
	b.insert("note", QStringList() << "html_text" << "date");
	b.values(QVariantList()
			 << noteHtmlText
			 << date);
	NoteHandler::execute(b);

	Qst::QstPlainQueryModel model;
	NoteHandler th;
	th.setQuery(noteBatch());
	th.setModel(&model);
	th.updatePlaceholder("html_text", noteHtmlText, Qst::Equal);
	th.updatePlaceholder("date", date, Qst::Equal);
	th.reload();
	return th.fieldValue("id");
}

Qst::QstBatch noteBatch()
{
	QstBatch b;
	b.select(QstField(RolePrimaryKey, "n.id", FieldInvisible));
	b.select(QstField("n.html_text", FieldVisible, "Note name"));
	b.select(QstField("n.date"));
	b.select(QstField("count(tn.tag_id) as tag_cnt"));
	b.from("note n");
	b.innerJoin("tagged_note tn", QueryWhere("tn.note_id = n.id"));
	b.where("html_text", QstPlaceholder());
	b.where("date", QstPlaceholder());
	b.where("tn.tag_id", QstPlaceholder("selected_tags"), Qst::InList);
	b.groupBy("n.id, n.html_text, n.date");

	b.setModelColumn("html_text");
	return b;
}


