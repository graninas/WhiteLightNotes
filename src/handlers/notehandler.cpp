#include "notehandler.h"

using namespace Qst;

#include "notetheme.h"

NoteHandler::NoteHandler()
{
}

QVariant NoteHandler::createNote(const QString &title,
								 const QString &noteHtmlText,
								 const QString &noteSimpleText,
								 const QDateTime &date,
								 const QString &theme,
								 const QString &complexData)
{
	QstBatch b1;
	b1.insert("note", QStringList() << "title" << "html_text" << "simple_text" << "date" << "theme" << "complex_data");
	b1.values(QVariantList() << title << noteHtmlText << noteSimpleText << date << theme << complexData);
	NoteHandler::execute(b1);

	QstBatch b2;
	b2.select(QstField("id"));
	b2.from("note");
	b2.where("html_text", QstPlaceholder());         // For value escaping.
	b2.where("date", date);
	b2.updatePlaceholder("html_text", noteHtmlText); // For value escaping.
	return NoteHandler::fieldValue(b2, "id");
}

Qst::QstBatch noteBatch(const QstVariantListMap &filters)
{
	QstBatch b;
	b.select(QstField(RolePrimaryKey, "n.id", FieldInvisible));
	b.select(QstField("n.html_text",    FieldInvisible, "Note HTML"));
	b.select(QstField("n.simple_text",  FieldInvisible, "Note Simple"));
	b.select(QstField("n.complex_data", FieldVisible, "Note Complex"));
	b.select(QstField("n.date",         FieldInvisible, "Note Datetime"));
	b.select(QstField("n.theme",        FieldInvisible, "Note Theme"));
	b.select(QstField("count(tn.tag_id) as tag_cnt", FieldInvisible));
	b.from("note n");
	b.innerJoin("tagged_note tn", QueryWhere("tn.note_id = n.id"));
	b.innerJoin("tag t",          QueryWhere("t.id = tn.tag_id"));
	b.where("tn.tag_id", QstPlaceholder("selected_tags"), Qst::InList);
	b.groupBy("n.id, n.html_text, n.date");
	b.orderBy("n.date");

	b.setModelColumn("complex_data");
	return b;
}


