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
#include "viewappearance.h"

namespace Qst
{
namespace Mvc
{


/*!
\class ViewAppearance
\brief
\lang_Russian
	Содержит настройки представлений (QTreeView, QTableView, QListView).
\endlang

\lang_English
	Contains settings for views (QTreeView, QTableView, QListView).
\endlang
*/


/*!
\lang_Russian
	Конструктор по умолчанию.
\endlang

\lang_English
	Default constructor.
\endlang
*/
ViewAppearance::ViewAppearance()
	:
	_sortingEnabled(false),
	_currentIndex(0),
	_viewType(InvalidView),
	_sortFilterProxyModel(NULL)
{
}

/*!
\lang_Russian
	Устанавливает настройки колонок.
\endlang

\lang_English
	Sets column settings.
\endlang
*/
void ViewAppearance::setColumnSettingsMap(const ColumnSettingsMap &columnSettingsMap)
{
	_columnsSettingMap = columnSettingsMap;
}

/*!
\lang_Russian
	Возвращает настройки колонок.
\endlang

\lang_English
	Returns column settings.
\endlang
*/
ColumnSettingsMap ViewAppearance::columnSettingsMap() const
{
	return _columnsSettingMap;
}

/*!
\lang_Russian
	Включает или выключает сортировку.
\endlang

\lang_English
	Enables or disables sorting.
\endlang
*/
void ViewAppearance::setSortingEnabled(const bool &sortFilteringEnabled)
{
	_sortingEnabled = sortFilteringEnabled;
}

/*!
\lang_Russian
	Возвращает true, если сортировка включена.
\endlang

\lang_English
	Returns true if sorting is enabled.
\endlang
*/
bool ViewAppearance::sortingEnabled() const
{
	return _sortingEnabled;
}

/*!
\lang_Russian
	Сохраняет индекс текущей строки.
\endlang

\lang_English
	Saves view current inndex.
\endlang
*/
void ViewAppearance::setCurrentIndex(const int &index)
{
	_currentIndex = index;
}

/*!
\lang_Russian
	Возвращает индекс текущей строки.
\endlang

\lang_English
	Returns view current inndex.
\endlang
*/
int ViewAppearance::currentIndex() const
{
	return _currentIndex;
}

/*!
\lang_Russian
	Устанавливает вид представления: TableView, TreeView, ListView.
\endlang

\lang_English
	Sets view type: TableView, TreeView, ListView.
\endlang
*/
void ViewAppearance::setViewType(const ViewType &viewType)
{
	_viewType = viewType;
}

/*!
\lang_Russian
	Возвращает вид представления.
\endlang

\lang_English
	Returns view type.
\endlang
*/
ViewAppearance::ViewType ViewAppearance::viewType() const
{
	return _viewType;
}

/*!
\lang_Russian
	Устанавливает настройки колонки.
\endlang

\lang_English
	Sets column settings.
\endlang
*/
void ViewAppearance::setColumnSetting(const int &columnIndex,
									   const ColumnSetting::SettingType &settingType,
									   const QVariant &settingValue)
{
	bool ok;
	int intval;

	switch (settingType)
	{
	case ColumnSetting::Title:
		_columnsSettingMap[columnIndex].setTitle(settingValue.toString());
		break;

	case ColumnSetting::Width:
		intval = settingValue.toInt(&ok);

		if (ok) _columnsSettingMap[columnIndex].setWidth(intval);
		break;

	case ColumnSetting::Orientation:
		intval = settingValue.toInt(&ok);

		if (ok) _columnsSettingMap[columnIndex].setOrientation((Qt::Orientation)intval);
		break;

	case ColumnSetting::Shown:
		_columnsSettingMap[columnIndex].setVisible(true);
		break;

	case ColumnSetting::Hidden:
		_columnsSettingMap[columnIndex].setVisible(false);
		break;

	case ColumnSetting::Visibility:
		_columnsSettingMap[columnIndex].setVisible(settingValue.toBool());
		break;
	}
}

/*!
\lang_Russian
	Возвращает настройки колонки.
\endlang

\lang_English
	Returns column settings.
\endlang
*/
ColumnSetting ViewAppearance::columnSetting(const int &columnIndex) const
{
	return _columnsSettingMap.value(columnIndex);
}

/*!
\lang_Russian
	Создает модель QSortFilterProxyModel и возвращает указатель на нее.
	Указатель так же сохраняется в классе ViewAppearance. Если модель была создана ранее,
	она замещается новой.
\endlang

\lang_English
	Creates a model QSortFilterProxyModel and returns a pointer to it.
	Pointer also stored in the class ViewAppearance. If a model was created earlier, it is replaced by a new one.
\endlang
*/
QSortFilterProxyModel *ViewAppearance::createSortFilterProxyModel(QAbstractItemModel *model)
{
	if (_sortFilterProxyModel != NULL)
		deleteSortFilterProxyModel();

	_sortFilterProxyModel = new QSortFilterProxyModel(model);
	_sortFilterProxyModel->setSourceModel(model);
	Q_ASSERT(_sortFilterProxyModel != NULL);

return _sortFilterProxyModel;
}

/*!
\lang_Russian
	Удаляет ранее созданную модель QSortFilterProxyModel.
\endlang

\lang_English
	Deletes previously created model QSortFilterProxyModel.
\endlang
*/
void ViewAppearance::deleteSortFilterProxyModel()
{
	delete _sortFilterProxyModel;
	_sortFilterProxyModel = NULL;
}

bool ViewAppearance::isValid() const
{
	return _viewType != InvalidView;
}




}
}
