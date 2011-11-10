/****************************************************************************
** QST 0.6.2 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the Qst module of the QsT SQL Tools.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: http://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** author (graninas@gmail.com).
**
****************************************************************************/

#include "qstplaceholder.h"

namespace Qst
{

QstPlaceholder::QstPlaceholder()
{
}

QstPlaceholder::QstPlaceholder(const QString &placeholderName)
{
	_names.append(placeholderName);
}

QstPlaceholder::QstPlaceholder(const QString &placeholderName,
							   const ValueCheckFunctor &valueCheckFunctor)
{
	_names.append(placeholderName);
	Q_UNUSED(valueCheckFunctor);
}

void QstPlaceholder::addName(const QString &placeholderName)
{
	Q_ASSERT(!placeholderName.isEmpty());

	_names.append(placeholderName);
}

int QstPlaceholder::position(const QString &placeholderName) const
{
	return _names.indexOf(placeholderName);
}

QStringList QstPlaceholder::names() const
{
	return _names;
}

QString QstPlaceholder::name() const
{
	if (_names.isEmpty())
		return QString();
return _names.first();
}

}
