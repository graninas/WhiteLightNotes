#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TagHandler : public Qst::QstAbstractModelHandler
{
public:
    TagHandler();

	static void createTag(const QString &tagName);
};

Qst::QstBatch tagBatch();


#endif // TAGHANDLER_H
