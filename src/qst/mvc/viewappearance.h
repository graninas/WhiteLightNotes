/****************************************************************************
** QST 0.6.2 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the Qst::Mvc module of the QsT SQL Tools.
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
#ifndef VIEWAPPEARANCE_H
#define VIEWAPPEARANCE_H

#include "qst/mvc/columnsetting.h"

#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QMap>

namespace Qst
{
namespace Mvc
{

class ViewAppearance	// FIX ME: documentation // FULL REWRITE
{
public:

	typedef enum
	{
		TableView,
		TreeView,
		ListView,
		InvalidView
	} ViewType;

private:

	ColumnSettingsMap _columnsSettingMap;

	bool _sortingEnabled;
	int  _currentIndex;
	ViewType _viewType;

	QSortFilterProxyModel *_sortFilterProxyModel;

public:
	ViewAppearance();

	void setColumnSettingsMap(const ColumnSettingsMap &columnSettingsMap);
	ColumnSettingsMap columnSettingsMap() const;

	void setSortingEnabled(const bool &sortFilteringEnabled);
	bool sortingEnabled() const;

	void setCurrentIndex(const int &index);
	int currentIndex() const;

	void setViewType(const ViewType &viewType);
	ViewType viewType() const;

	void setColumnSetting(const int &columnIndex,
						  const ColumnSetting::SettingType &settingType,
						  const QVariant &settingValue);

	ColumnSetting columnSetting(const int &columnIndex) const;

	QSortFilterProxyModel *createSortFilterProxyModel(QAbstractItemModel *model);
	void deleteSortFilterProxyModel();

	bool isValid() const;

	friend bool operator==(const ViewAppearance &ap1, const ViewAppearance &ap2)
	{
		return ap1._sortingEnabled == ap2._sortingEnabled
				&& ap1._currentIndex == ap2._currentIndex
				&& ap1._viewType == ap2._viewType
				&& ap1._sortFilterProxyModel == ap2._sortFilterProxyModel
				&& ap1._columnsSettingMap == ap2._columnsSettingMap
				;
	}
};

// --------------------------------------------------------------------------------- //

typedef QMap<QAbstractItemView *, ViewAppearance> ViewAppearanceMap;

// --------------------------------------------------------------------------------- //

}
}

#endif // VIEWAPPEARANCE_H
