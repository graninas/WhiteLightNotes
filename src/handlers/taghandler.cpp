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
	b.orderBy("tag_info.tag_cnt DESC");
	b.setModelColumn("info_tag");
	return b;
}

Qst::QstBatch linkedTagsBatch(const QStringList &tagList)
{
	QueryBatch b = QueryBatch(QuerySelect, "linked tags batch");
	b.from("tagged_note tn2");
	b.innerJoin("tag t2", QueryWhere("t2.id = tn2.tag_id"));
	b.where("t2.name <> 'All'");
	b.groupBy("t2.id, t2.name");
	b.orderBy("count(t2.id) DESC");

	QString includeClause  = "note_id IN (SELECT tn1.note_id FROM tagged_note tn1 INNER JOIN tag t ON t.id = tn1.tag_id";
	QString excludeClause = "";
	QString tag;
	for (int i = 0; i < tagList.count(); ++i)
	{
		tag = "'" + tagList[i] + "'";

		if (i == 0)
		{
			excludeClause += " t2.name NOT LIKE " + tag;
			includeClause += " WHERE t.name LIKE " + tag;
		}
		else
		{
			excludeClause += " AND t2.name NOT LIKE " + tag;
			includeClause += " OR t.name LIKE "   + tag;
		}
	}

	includeClause += ") ";
	b.where(includeClause);
	b.where(excludeClause);

	QstBatch batch;
	batch.setQueryBatch(b);
	batch.select(QstField(RolePrimaryKey, "t2.id"));
	batch.select(QstField("t2.name", FieldInvisible, "Tag name"));
	batch.select("info_tag",
				 "name || ' (' || count(t2.id) || ')'",
				 "Tag"); // Column title
	batch.setModelColumn("info_tag");
	return batch;
}
