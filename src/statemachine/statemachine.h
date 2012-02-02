/****************************************************************************
** WhiteLight Notes 0.9 rc2
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

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "transtable.h"
#include "types.h"

class StateMachine
{
private:

	TransTable _table;

	struct TransitionResult
	{
		QString collected;
		QString filter;
		StringListMap resMap;
	};

public:
	StateMachine();
	StateMachine(const TransTable &table);

	StringListMap process(const QString &str,
						  const State &startState,
						  const QString &defSpecificator) const;

private:

	TransitionResult _getTransitionResult(const TransitionResult &prevResult,
										  const Action &action,
										  const QChar &ch,
										  const QString &defSpecificator) const;
};

#endif // STATEMACHINE_H
