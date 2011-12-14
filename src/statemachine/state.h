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

	QString name() const;

	friend bool operator==(const State &s1, const State &s2)
	{
		return s1._name == s2._name;
	}
};

typedef QList<State> StateList;

#endif // STATE_H
