#include "notehandler.h"

using namespace Qst;

NoteHandler::NoteHandler()
{
}

Qst::QstBatch noteBatch()
{
	QstBatch b;
	b << "note"
	  << QstField(RolePrimaryKey, "id")
	  << QstField("title")
	  << QstField("text")
	  << QstField("date");
	return b;
}
