#ifndef TAGHANDLER_H
#define TAGHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class TagHandler : public Qst::QstAbstractModelHandler
{
public:
    TagHandler();

	static QVariant createTag(const QString &tagName,
							  const QVariant &priority);
};

Qst::QstBatch tagBatch();
Qst::QstBatch linkedTagsBatch(const QStringList &tagList);


#endif // TAGHANDLER_H
