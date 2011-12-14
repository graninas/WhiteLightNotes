#ifndef TRANSTABLE_H
#define TRANSTABLE_H

#include "event.h"
#include "state.h"
#include "transition.h"

#include <QMap>

typedef QMap<Event, TransitionList> TransitionMap;

class TransTable
{
private:

	StateList      _stateList;
	EventList      _eventList;
	TransitionMap  _transitionMap;

	Event          _currentEvent;

public:
    TransTable();

	Transition transition(const State &state, const QChar &ch) const;

	TransTable &operator<<(const State &state);
	TransTable &operator<<(const Event &event);
	TransTable &operator<<(const Transition &transition);

private:

	Event _getEvent(const QChar &ch) const;
};

#endif // TRANSTABLE_H
