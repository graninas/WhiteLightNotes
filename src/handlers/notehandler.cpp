#include "notehandler.h"

using namespace Qst;

NoteHandler::NoteHandler()
{
}

QVariant NoteHandler::createNote(const QVariant &noteHtmlText,
								 const QVariant &noteSimpleText,
								 const QVariant &date)
{
	QstBatch b1;
	b1.insert("note", QStringList() << "html_text" << "simple_text" << "date");
	b1.values(QVariantList()
			 << noteHtmlText
			 << noteSimpleText
			 << date);
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
//	QueryWhere whereCond;
//	QueryWhere havingCond;
//	foreach(QVariant var, filters["n:"])
//		whereCond || QueryField("simple_text",
//								QueryValue(var, Qst::LeftRightPercents),
//								Qst::Like, ClauseWhere);
//	foreach(QVariant var, filters["d:"])
//		whereCond || QueryField("date",
//								QueryValue(var, Qst::NoPlaceholders),
//								Qst::Equal, ClauseWhere);
//	foreach(QVariant var, filters["t:"])
//		havingCond || QueryField("t.name",
//								 QueryValue(var, Qst::LeftRightPercents),
//								 Qst::Like, ClauseHaving);

	QstBatch b;
	b.select(QstField(RolePrimaryKey, "n.id", FieldInvisible));
	b.select(QstField("n.html_text", FieldInvisible, "Note HTML"));
	b.select(QstField("n.simple_text", FieldVisible, "Note Simple"));
	b.select(QstField("n.date", FieldInvisible));
	b.select(QstField("count(tn.tag_id) as tag_cnt", FieldInvisible));
	b.from("note n");
	b.innerJoin("tagged_note tn", QueryWhere("tn.note_id = n.id"));
	b.innerJoin("tag t", QueryWhere("t.id = tn.tag_id"));
//	b.where("simple_text", QstPlaceholder());
//	b.where("date", QstPlaceholder());
	b.where("tn.tag_id", QstPlaceholder("selected_tags"), Qst::InList);
//	b.where(whereCond);
	b.groupBy("n.id, n.html_text, n.date");
//	b.having(havingCond);
	b.orderBy("n.date");

	b.setModelColumn("html_text");
	return b;
}


