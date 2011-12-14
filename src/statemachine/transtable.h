/****************************************************************************
** WhiteLight Notes 0.9 rc1
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

#ifndef TRANSTABLE_H
#define TRANSTABLE_H

#include "event.h"
#include "state.h"
#include "transition.h"

#include <QMap>

typedef QMap<Event, TransitionList> TransitionMap;

class TransTable
{
private:

	StateList      _stateList;
	EventList      _eventList;
	TransitionMap  _transitionMap;

	Event          _currentEvent;

public:
    TransTable();

	Transition transition(const State &state, const QChar &ch) const;

	TransTable &operator<<(const State &state);
	TransTable &operator<<(const Event &event);
	TransTable &operator<<(const Transition &transition);

private:

	Event _getEvent(const QChar &ch) const;
};

#endif // TRANSTABLE_H
