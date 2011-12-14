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

#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

#include <QList>

typedef enum
{
	N = 0, // No action
	C = 1, // Collect
	F = 2, // Filter item
	S = 3, // Specificator item
	A = 4  // Abort
} Action;

QString actionToString(const Action &a);

class Transition
{
private:
	Action _action;
	State  _state;

public:
	Transition();
	Transition(const Action &action, const State &state);

	State  state() const;
	Action action() const;
};

typedef QList<Transition> TransitionList;

#endif // TRANSITION_H
