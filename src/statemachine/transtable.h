#ifndef TRANSTABLE_H
#define TRANSTABLE_H

#include "event.h"
#include "state.h"
#include "transition.h"

#include <QMap>

class TransTable
{
private:

	typedef QMap<Event, TransitionList> TransitionMap;

	StateList      _stateList;
	TransitionMap  _transitionMap;
	Event          _currentEvent;

public:
    TransTable();

	TransTable &operator<<(const State &state);
	TransTable &operator<<(const Event &event);
	TransTable &operator<<(const Transition &transition);
};

#endif // TRANSTABLE_H
