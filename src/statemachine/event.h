#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QList>

class Event
{
private:

	QString _eventElements;

public:
    Event();
	Event(const QString &eventElements);

	bool isEventChar(const QChar &ch) const;

	friend bool operator <(const Event &e1, const Event &e2)
	{
		return e1._eventElements < e2._eventElements;
	}

	friend bool operator !=(const Event &e1, const Event &e2)
	{
		return e1._eventElements != e2._eventElements;
	}
};
typedef QList<Event> EventList;

#endif // EVENT_H
