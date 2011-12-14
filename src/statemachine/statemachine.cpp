#include "statemachine.h"

#include <QDebug>

StateMachine::StateMachine()
{
}

StateMachine::StateMachine(const TransTable &table,
						   const State &startState,
						   const QString &defSpecificator)
	:
	  _table(table),
	  _startState(startState),
	  _defSpecificator(defSpecificator)
{
}

StringListMap StateMachine::process(const QString &str)
{
	qDebug() << "\n\nStart state machine.";

	Transition t = Transition(N, _startState);
	TransitionResult transRes;
	for (int i = 0; i < str.count(); ++i)
	{
		t = _table.transition(t.state(), str[i]);
		transRes = _getTransitionResult(transRes, t.action(), str[i]);
		qDebug() << "Event char: " << str[i];
		qDebug() << "Transition: (" +actionToString(t.action()) + ", " + t.state().name() + ")";
		qDebug() << "Transition result: " << transRes.collected << ", " << transRes.filter;
	}

	t = _table.transition(t.state(), '\n');
	transRes = _getTransitionResult(transRes, t.action(), '\n');
	return transRes.resMap;
}

StateMachine::TransitionResult StateMachine::_getTransitionResult
	(const TransitionResult &prevRes,
	 const Action &action,
	 const QChar &ch) const
{
	TransitionResult newResult = prevRes;
	switch (action)
	{
	case C: newResult.collected += ch; break;
	case F:
		if (!newResult.filter.isEmpty())
			 newResult.resMap[newResult.filter].append(newResult.collected);
		else
			 newResult.resMap[_defSpecificator].append(newResult.collected);
		newResult.collected = "";
		newResult.filter = "";
		break;
	case S:
		newResult.filter = newResult.collected + ch;
		newResult.collected = "";
		break;
	case N: break;
	case A:
		newResult.filter = "";
		newResult.collected = "";
		break;
	}
	return newResult;
}
