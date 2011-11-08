#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TagHandler : public Qst::QstAbstractModelHandler
{
public:
    TagHandler();

	QVariant createTag(const QString &tagName) const;
};

Qst::QstBatch tagBatch();


#endif // TAGHANDLER_H
