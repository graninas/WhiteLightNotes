#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

#include <QList>

typedef enum
{
	N = 0, // No action
	C = 1, // Collect
	F = 2, // Filter item
	S = 3, // Specificator item
	A = 4  // Abort
} Action;

QString actionToString(const Action &a);

class Transition
{
private:
	Action _action;
	State  _state;

public:
	Transition();
	Transition(const Action &action, const State &state);

	State  state() const;
	Action action() const;
};

typedef QList<Transition> TransitionList;

#endif // TRANSITION_H
