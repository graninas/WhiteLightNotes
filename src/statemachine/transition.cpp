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
