#include "transtable.h"

TransTable::TransTable()
{
}

TransTable &TransTable::operator<<(const State &state)
{
	_stateList.append(state);
	return *this;
}

TransTable &TransTable::operator<<(const Event &event)
{
	_currentEvent = event;
	return *this;
}

TransTable &TransTable::operator<<(const Transition &transition)
{
	_transitionMap[_currentEvent].append(transition);
	return *this;
}
