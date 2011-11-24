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
