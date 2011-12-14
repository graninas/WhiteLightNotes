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
