#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"

class NoteHandler : public Qst::QstAbstractModelHandler
{
public:
    NoteHandler();
};

Qst::QstBatch noteBatch();

#endif // NOTEHANDLER_H
