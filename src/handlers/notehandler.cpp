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
	b << "note"
	  << QstField(RolePrimaryKey, "id")
	  << QstField("html_text")
	  << QstField("date");

	b.where("html_text", QstPlaceholder());
	b.where("date", QstPlaceholder());
	return b;
}


