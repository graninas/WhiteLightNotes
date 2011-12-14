#include "event.h"

Event::Event()
{
}

Event::Event(const QString &eventElements)
	:
	  _eventElements(eventElements)
{
}

bool Event::isEventChar(const QChar &ch) const
{
	return _eventElements.contains(ch);
}
