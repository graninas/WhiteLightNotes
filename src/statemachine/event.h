/****************************************************************************
** WhiteLight Notes 0.9 rc2
** Copyright (C)  Granin A.S. 2011
** 
**
** This file is part of the WhiteLight Notes project.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** authors.
**
** Author: Granin, Alexandr
** graninas@gmail.com
****************************************************************************/

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
