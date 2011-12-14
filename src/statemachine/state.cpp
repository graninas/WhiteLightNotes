#include "state.h"

State::State()
{
}

State::State(const QString &name)
	:
	  _name(name)
{
}

QString State::name() const
{
	return _name;
}
