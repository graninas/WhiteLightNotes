#include "transition.h"

Transition::Transition()
{
}

Transition::Transition(const Action &action, const State &state)
	:
	  _action(action),
	  _state(state)
{
}
