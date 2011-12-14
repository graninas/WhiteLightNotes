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

#include "tagsmodel.h"

TagsModel::TagsModel()
{
}

void TagsModel::setTagSelectable(const QString &tag,
								 const bool &selectable)
{
	_selectableTagMap.insert(tag, selectable);
}

void TagsModel::setTagColumnIndex(const int &columnIndex)
{
	_tagColumnIndex = columnIndex;
}

// index - индекс поля tag_info, где также присутствует количество записей
// в скобках. _selectableTagMap содержит имена тегов без количества.
// В цикле проверяется, о том ли теге идет речь.
// Пример:
// index.data().toString() == "All (5)"
// _selectableTagMap["All"] = false
// "All" == "All (5)" ?
Qt::ItemFlags TagsModel::flags ( const QModelIndex & index ) const
{
	if (index.column() != _tagColumnIndex)
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	QString tag = index.data().toString();
	SelectableTagMap::const_iterator iter = _selectableTagMap.begin();
	while (iter != _selectableTagMap.end())
	{
		if (tag.contains(iter.key()))
		{
			if (iter.value()) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
			else return Qt::ItemIsEnabled;
		}
		iter++;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TagsModel::data(const QModelIndex &item, int role) const
{
	if (item.column() == _tagColumnIndex && role == Qt::ToolTipRole)
	{
		QString tag = item.data().toString();
		SelectableTagMap::const_iterator iter = _selectableTagMap.begin();
		while (iter != _selectableTagMap.end())
		{
			if (tag.contains(iter.key()))
				return QString("'" + iter.key() + "' is autotag.");
			iter++;
		}
	}
	return QstPlainQueryModel::data(item, role);
}
