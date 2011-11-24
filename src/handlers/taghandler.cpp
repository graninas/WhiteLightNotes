#include "taghandler.h"

using namespace Qst;

TagHandler::TagHandler()
{
}

QVariant TagHandler::createTag(const QString &tagName,
							   const QVariant &priority)
{
	Qst::QstBatch selB = tagBatch();
	selB.updatePlaceholder("name", tagName);
	QVariant tagID = TagHandler::fieldValue(selB, "id");

	if (tagID.isNull())
	{
		QstBatch insB;
		insB.insert("tag", QStringList() << "name" << "priority");
		insB.values(QVariantList() << QVariant(tagName) << QVariant(priority));
		TagHandler::execute(insB);
		return TagHandler::fieldValue(selB, "id");
	}
	return tagID;
}

Qst::QstBatch tagBatch()
{
	QstBatch b;
	b	<< "tag t"
		<< QstField(RolePrimaryKey, "id", FieldInvisible)
		<< QstField("name", FieldInvisible, "Tag name");
	b.select("info_tag",
			 "name || ' (' || CASE WHEN tag_info.tag_cnt IS NULL THEN 0 ELSE tag_info.tag_cnt END || ')'",
			 "Tag"); // Column title
	b.leftJoin("(SELECT tn.tag_id as tag_id, count(tn.note_id) as tag_cnt FROM tag t INNER JOIN tagged_note tn ON tn.tag_id = t.id GROUP BY tn.tag_id) tag_info",
			   QueryOn("tag_info.tag_id = t.id"));
	b.where("name", QstPlaceholder());
	b.orderBy("priority");
	b.orderBy("tag_info.tag_cnt");

	b.setModelColumn("info_tag");

	return b;
}
