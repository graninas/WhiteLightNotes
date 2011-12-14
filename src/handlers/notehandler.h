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

#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include "qst/qstabstractmodelhandler.h"
#include "types.h"

class NoteHandler : public Qst::QstAbstractModelHandler
{
public:
    NoteHandler();

	static QVariant createNote(const QString   &title,
							   const QString   &noteHtmlText,
							   const QString   &noteSimpleText,
							   const QDateTime &date,
							   const QString   &theme,
							   const QString   &complexData);

	static QVariant updateNote(const QVariant  &noteID,
							   const QString   &title,
							   const QString   &noteHtmlText,
							   const QString   &noteSimpleText,
							   const QDateTime &date,
							   const QString   &theme,
							   const QString   &complexData);
};

Qst::QstBatch noteBatch(const StringListMap &filters);

QString filterCondition(const QString &filterName, const QStringList &filterItems);

#endif // NOTEHANDLER_H
