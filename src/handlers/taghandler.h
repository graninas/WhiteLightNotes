/****************************************************************************
** WhiteLight Notes 0.9 rc1
** Copyright (C)  Granin A.S. 2011
** 
**
** This file is part of the WhiteLight Notes project.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** authors.
**
** Author: Granin, Alexandr
** graninas@gmail.com
****************************************************************************/

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
