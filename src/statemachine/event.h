#ifndef EVENT_H
#define EVENT_H

#include <QString>

class Event
{
private:

	QString _eventElements;

public:
    Event();
	Event(const QString &eventElements);

	friend bool operator <(const Event &e1, const Event &e2)
	{
		return e1._eventElements < e2._eventElements;
	}
};

#endif // EVENT_H
