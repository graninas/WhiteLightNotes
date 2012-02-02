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

#include "transtable.h"

TransTable::TransTable()
{
}

Transition TransTable::transition(const State &state, const QChar &ch) const
{
	int stateIdx = _stateList.indexOf(state);
	Event e = _getEvent(ch);
	Q_ASSERT(stateIdx > -1);
	Q_ASSERT(e != Event());
	Q_ASSERT(_transitionMap.contains(e));
	Q_ASSERT(stateIdx < _transitionMap[e].count());
	return _transitionMap[e][stateIdx];
}

TransTable &TransTable::operator<<(const State &state)
{
	_stateList.append(state);
	return *this;
}

TransTable &TransTable::operator<<(const Event &event)
{
	_eventList.append(event);
	_currentEvent = event;
	return *this;
}

TransTable &TransTable::operator<<(const Transition &transition)
{
	_transitionMap[_currentEvent].append(transition);
	return *this;
}

Event TransTable::_getEvent(const QChar &ch) const
{
	foreach(Event e, _eventList)
		if (e.isEventChar(ch))
			return e;
	return Event();
}
