#include "taghandler.h"

using namespace Qst;

TagHandler::TagHandler()
{
}

QVariant TagHandler::createTag(const QString &tagName) const
{
	QstBatch b;
	b.insert("tag", QStringList() << "name");
	b.values(QVariantList() << QVariant(tagName));
	TagHandler th;
	th.execute(b);

	QstPlainQueryModel model;
	th.setModel(&model);
	th.setQuery(tagBatch());
	th.updatePlaceholder("name", tagName);
	th.reload();
	return th.fieldValue("id");
}

Qst::QstBatch tagBatch()
{
	QstBatch b;
	b	<< "tag"
		<< QstField(RolePrimaryKey, "id")
		<< QstField("name");
	b.where("name", QstPlaceholder());
	return b;
}
