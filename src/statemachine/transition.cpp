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

#include "transition.h"

QString actionToString(const Action &a)
{
	switch (a)
	{
	case N: return "N";
	case C: return "C";
	case F: return "F";
	case S: return "S";
	case A: return "A";
	};
	return QString();
}

Transition::Transition()
{
}

Transition::Transition(const Action &action, const State &state)
	:
	  _action(action),
	  _state(state)
{
}

State Transition::state() const
{
	return _state;
}

Action Transition::action() const
{
	return _action;
}
