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

#ifndef QUICKFILTERPARSER_H
#define QUICKFILTERPARSER_H

#include <QMap>
#include <QString>
#include <QStringList>

#include "statemachine/statemachine.h"

class QuickFilterParser
{
public:
    QuickFilterParser();

	static StringListMap parse(const QString &filterString,
							   const QString &defaultSpecificator);
};

#endif // QUICKFILTERPARSER_H
