#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TagHandler : public Qst::QstAbstractModelHandler
{
public:
    TagHandler();

	static QVariant createTag(const QString &tagName);
};

Qst::QstBatch tagBatch();


#endif // TAGHANDLER_H
