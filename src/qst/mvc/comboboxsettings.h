/****************************************************************************
** QST 0.6.0 pre-alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the Qst module of the QsT SQL Tools.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: http://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** author (graninas@gmail.com).
**
****************************************************************************/

#ifndef COMBOBOXSETTINGS_H
#define COMBOBOXSETTINGS_H

#include <QMap>
#include <QComboBox>

namespace Qst
{
namespace Mvc
{


class ComboBoxSettings
{
private:

	int _currentIndex;
	int _modelColumn;

public:
	ComboBoxSettings();

	void setCurrentIndex(const int &index);
	int currentIndex() const;

	void setModelColumn(const int &column);
	int modelColumn() const;

	bool isValid() const;
};

//--------------------------------------------------------------------------------

typedef QMap<QComboBox *, ComboBoxSettings> ComboBoxSettingsMap;

//--------------------------------------------------------------------------------


} // End of namespace Mvc
} // End of namespace Qst

#endif // COMBOBOXSETTINGS_H
