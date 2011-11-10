/****************************************************************************
** QST 0.6.2 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the QueryGeneration module of the QsT SQL Tools.
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

#include "queryframeaccesory.h"

QueryAccessory::QueryAccessory(const QString &clauseWord,
							   const QString &subqueryBrackets)
	:
	_clauseWord(clauseWord),
	_subqueryBrackets(subqueryBrackets)
{
	if (!subqueryBrackets.isEmpty())
	{
		Q_ASSERT(subqueryBrackets.count() == 2);
	}
}

QString QueryAccessory::clauseWord() const
{
	return _clauseWord;
}

QString QueryAccessory::leftSubqueryBracket() const
{
	if (_subqueryBrackets.count() > 0)
		return _subqueryBrackets[0];
return QString();
}

QString QueryAccessory::rightSubqueryBracket() const
{
	if (_subqueryBrackets.count() > 1)
		return _subqueryBrackets[1];
return QString();
}


