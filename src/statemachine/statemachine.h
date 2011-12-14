#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "transtable.h"
#include "types.h"

class StateMachine
{
private:

	TransTable _table;

	struct TransitionResult
	{
		QString collected;
		QString filter;
		StringListMap resMap;
	};

public:
	StateMachine();
	StateMachine(const TransTable &table);

	StringListMap process(const QString &str,
						  const State &startState,
						  const QString &defSpecificator) const;

private:

	TransitionResult _getTransitionResult(const TransitionResult &prevResult,
										  const Action &action,
										  const QChar &ch,
										  const QString &defSpecificator) const;
};

#endif // STATEMACHINE_H
