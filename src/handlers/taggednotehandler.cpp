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

QStringList TaggedNoteHandler::tagList(const QVariant &noteID)
{
	QstBatch selB;
	selB.select("t.name");
	selB.from("tagged_note tn");
	selB.innerJoin("tag t", QueryWhere("t.id = tn.tag_id"));
	selB.where("tn.note_id", noteID, Equal);
	QstPlainQueryModel model;
	TaggedNoteHandler th;
	th.setModel(&model);
	th.setQuery(selB);
	th.reload();
	QStringList l;
	foreach(QVariant v, th.columnValuesList("name"))
		l.append(v.toString());
	return l;
}

