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
