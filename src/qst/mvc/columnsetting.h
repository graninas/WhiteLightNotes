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

#ifndef COLUMNSETTING_H
#define COLUMNSETTING_H

#include <QString>
#include <QMap>

namespace Qst
{
namespace Mvc
{

class ColumnSetting
{
public:

	typedef enum
	{
		Visibility,
		Shown,
		Hidden,
		Width,
		Orientation,
		Title
	} SettingType;

private:

	bool     _visible;
	QString  _title;
	int      _width;
	Qt::Orientation _orientation;

public:
	ColumnSetting();
	ColumnSetting(const bool &visible,
					 const QString &title,
					 const int &width,
					 const Qt::Orientation &orientation);

	bool isVisible() const;
	void setVisible(const bool &visible);
	void setHidden(const bool &hidden);

	QString title() const;
	void setTitle(const QString &title);

	int width() const;
	void setWidth(const int &width);

	Qt::Orientation orientation() const;
	void setOrientation(const Qt::Orientation &orientation);

	friend bool operator==(const ColumnSetting &val1, const ColumnSetting &val2)
	{
		return val1._visible == val2._visible
				&& val1._title == val2._title
				&& val1._width == val2._width
				&& val1._orientation == val2._orientation
				;
	}
};

//===================================================================================//

typedef QMap<int, ColumnSetting> ColumnSettingsMap;

//===================================================================================//

} // End of namespace Mvc;
} // End of namespace Qst;

#endif // COLUMNSETTING_H
