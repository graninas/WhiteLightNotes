/****************************************************************************
** WhiteLight Notes 0.9 rc1
** Copyright (C)  Granin A.S. 2011
** 
**
** This file is part of the WhiteLight Notes project.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** authors.
**
** Author: Granin, Alexandr
** graninas@gmail.com
****************************************************************************/

#include "notehandler.h"

using namespace Qst;

#include "notetheme.h"

NoteHandler::NoteHandler()
{
}

QVariant NoteHandler::createNote(const QString   &title,
								 const QString   &noteHtmlText,
								 const QString   &noteSimpleText,
								 const QDateTime &date,
								 const QString   &theme,
								 const QString   &complexData)
{
	QstBatch insB;
	insB.insert("note", QStringList() << "title" << "html_text" << "simple_text" << "date" << "theme" << "complex_data");
	insB.values(QVariantList() << title << noteHtmlText << noteSimpleText << date << theme << complexData);
	NoteHandler::execute(insB);

	QstBatch selB;
	selB.select(QstField("id"));
	selB.from("note");
	selB.where("html_text", QstPlaceholder());         // For value escaping.
	selB.where("date", date, Equal);
	selB.updatePlaceholder("html_text", noteHtmlText); // For value escaping.
	return NoteHandler::fieldValue(selB, "id");
}

QVariant NoteHandler::updateNote(const QVariant  &noteID,
								 const QString   &title,
								 const QString   &noteHtmlText,
								 const QString   &noteSimpleText,
								 const QDateTime &date,
								 const QString   &theme,
								 const QString   &complexData)
{
	Q_ASSERT(!noteID.isNull());
	QstBatch updB;
	updB.update("note");
	updB.set(QueryFieldList()
			 << QueryField("title",        QstPlaceholder("title"))
			 << QueryField("html_text",    QstPlaceholder("noteHtmlText"))
			 << QueryField("simple_text",  QstPlaceholder("noteSimpleText"))
			 << QueryField("date",         QstPlaceholder("date"))
			 << QueryField("theme",        QstPlaceholder("theme"))
			 << QueryField("complex_data", QstPlaceholder("complexData")));
	updB.where("id", noteID, Equal);
	updB.updatePlaceholder("title", title); // For value escaping.
	updB.updatePlaceholder("noteHtmlText", noteHtmlText);
	updB.updatePlaceholder("noteSimpleText", noteSimpleText);
	updB.updatePlaceholder("date", date);
	updB.updatePlaceholder("theme", theme);
	updB.updatePlaceholder("complexData", complexData);
	NoteHandler::execute(updB);
	return noteID;
}

Qst::QstBatch noteBatch(const StringListMap &filters)
{
	QstBatch b;
	b.select(QstField(RolePrimaryKey, "n.id", FieldInvisible));
	b.select(QstField("n.title",              FieldInvisible, "Note Title"));
	b.select(QstField("n.html_text",          FieldInvisible, "Note HTML"));
	b.select(QstField("n.simple_text",        FieldInvisible, "Note Simple"));
	b.select(QstField("n.complex_data",       FieldVisible,   "Note Complex"));
	b.select(QstField("n.date",               FieldInvisible, "Note Datetime"));
	b.select(QstField("n.theme",              FieldInvisible, "Note Theme"));
	b.select(QstField("count(tn.tag_id) as tag_cnt", FieldInvisible));
	b.from     ("note n");
	b.innerJoin("tagged_note tn", QueryWhere    ("tn.note_id = n.id"));
	b.innerJoin("tag t",          QueryWhere    ("t.id = tn.tag_id"));
	b.where    ("tn.tag_id",      QstPlaceholder("selected_tags"));
	b.groupBy  ("n.id, n.html_text, n.date");
	b.orderBy  ("n.date");

	QString noteCond  = filterCondition("n.simple_text", filters["n:"]);
	QString dateCond  = filterCondition("n.date",        filters["d:"]);
	QString colorCond = filterCondition("n.theme",       filters["c:"]);
	if (!noteCond.isEmpty())   b.where(noteCond);
	if (!dateCond.isEmpty())   b.where(dateCond);
	if (!colorCond.isEmpty())  b.where(colorCond);

	b.setModelColumn("complex_data");
	return b;
}

QString filterCondition(const QString &filterName, const QStringList &filterItems)
{
	if (filterItems.isEmpty())
		return QString();

	QString res =  "(" + filterName + " LIKE '" + filterItems.first() + "')";
	for (int i = 1; i < filterItems.count(); ++i)
		res += " OR (" + filterName + " LIKE '" + filterItems[i] + "')";

	return res;
}


