#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "transtable.h"
#include <QStringList>

typedef QMap<QString, QStringList> StringListMap;

class StateMachine
{
private:

	TransTable _table;
	State      _startState;
	QString    _defSpecificator;

	struct TransitionResult
	{
		QString collected;
		QString filter;
		StringListMap resMap;
	};

public:
	StateMachine();
	StateMachine(const TransTable &table,
				 const State &startState,
				 const QString &defSpecificator);

	StringListMap process(const QString &str);

private:

	TransitionResult _getTransitionResult(const TransitionResult &prevResult,
										  const Action &action,
										  const QChar &ch) const;
};

#endif // STATEMACHINE_H
