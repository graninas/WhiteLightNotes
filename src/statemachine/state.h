#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QList>

class State
{
private:
	QString _name;

public:
    State();
	State(const QString &name);
};

typedef QList<State> StateList;

#endif // STATE_H
