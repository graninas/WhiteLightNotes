#include "taghandler.h"

using namespace Qst;

TagHandler::TagHandler()
{
}

void TagHandler::createTag(const QString &tagName)
{
	QstBatch b;
	b.insert("tag", QStringList() << "name");
	b.values(QVariantList() << QVariant(tagName));
	TagHandler th;
	th.execute(b);
}

Qst::QstBatch tagBatch()
{
	QstBatch b;
	b	<< "tag t"
		<< QstField(RolePrimaryKey, "id", FieldInvisible)
		<< QstField("name", FieldVisible, "Tag name");
	b.select("info_tag",
			 "t.name || ' (' || (SELECT count(id) FROM tagged_note tn WHERE tn.tag_id = t.id) || ')'",
			 "Tag"
			 );
	b.where("name", QstPlaceholder());

	b.setModelColumn("info_tag");

	return b;
}
