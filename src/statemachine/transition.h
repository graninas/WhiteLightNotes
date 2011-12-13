#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

#include <QList>

typedef enum
{
	C, // Collect
	N, // No action
	F, // Filter item
	S  // Specificator item
} Action;

class Transition
{
private:
	Action _action;
	State  _state;

public:
	Transition();
	Transition(const Action &action, const State &state);
};

typedef QList<Transition> TransitionList;

#endif // TRANSITION_H
