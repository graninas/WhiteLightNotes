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
