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

#include "statemachine.h"

StateMachine::StateMachine()
{
}

StateMachine::StateMachine(const TransTable &table)
	:
	  _table(table)
{
}

StringListMap StateMachine::process(const QString &str,
									const State &startState,
									const QString &defSpecificator) const
{
	Transition t = Transition(N, startState);
	TransitionResult transRes;
	for (int i = 0; i < str.count(); ++i)
	{
		t = _table.transition(t.state(), str[i]);
		transRes = _getTransitionResult(transRes, t.action(), str[i], defSpecificator);
	}

	t = _table.transition(t.state(), '\n');
	transRes = _getTransitionResult(transRes, t.action(), '\n', defSpecificator);
	return transRes.resMap;
}

StateMachine::TransitionResult StateMachine::_getTransitionResult
	(const TransitionResult &prevRes,
	 const Action &action,
	 const QChar &ch,
	 const QString &defSpecificator) const
{
	TransitionResult newResult = prevRes;
	switch (action)
	{
	case C: newResult.collected += ch; break;
	case F:
		if (!newResult.filter.isEmpty())
			 newResult.resMap[newResult.filter].append(newResult.collected);
		else
			 newResult.resMap[defSpecificator].append(newResult.collected);
		newResult.collected = "";
		newResult.filter = "";
		break;
	case S:
		newResult.filter = newResult.collected + ch;
		newResult.collected = "";
		break;
	case N: break;
	case A:
		newResult.filter = "";
		newResult.collected = "";
		break;
	}
	return newResult;
}
