#include "taghandler.h"

using namespace Qst;

TagHandler::TagHandler()
{
}

Qst::QstBatch tagBatch()
{
	QstBatch b;
	b	<< "tag"
		<< QstField(RolePrimaryKey, "id")
		<< QstField("name");
	return b;
}
