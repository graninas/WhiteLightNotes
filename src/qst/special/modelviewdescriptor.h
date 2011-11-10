/****************************************************************************
** QST 0.6.2 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the Special module of the QsT SQL Tools.
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

#ifndef MODELVIEWDESCRIPTOR_H
#define MODELVIEWDESCRIPTOR_H

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include <QAbstractItemView>
#include <QComboBox>
#include <QListView>
#include <QList>
#include <QMap>
#include <QVector>

#include <QTableView>
#include <QTreeView>
#include <QListView>

#include "qst/qstglobal.h"
#include "qst/mvc/viewappearance.h"
#include "qst/mvc/comboboxsettings.h"

namespace Qst
{
namespace Special
{

class ModelViewDescriptor
{
private:

	QAbstractItemModel *_model;
	ModelType _modelType;

	Qst::Mvc::ViewAppearanceMap    _viewAppearanceMap;
	Qst::Mvc::ComboBoxSettingsMap  _comboBoxSettingsMap;

public:

	ModelViewDescriptor();
	ModelViewDescriptor(QAbstractItemModel* model,
					   const ModelType & modelType);
	~ModelViewDescriptor();

	QAbstractItemModel *model();
	QAbstractItemModel *model() const;

	void setModel(QAbstractItemModel *model,
				  const ModelType &modelType);

	void setView(QAbstractItemView *view,
				 const Qst::Mvc::ViewAppearance &viewAppearance);

	QAbstractItemView *defaultView() const;

	Qst::Mvc::ViewAppearance viewAppearance(QAbstractItemView *view) const;
	void setViewSetting(QAbstractItemView *view,
						const int &columnIndex,
						const Qst::Mvc::ColumnSetting::SettingType &settingType,
						const QVariant &settingValue);

	Qst::Mvc::ComboBoxSettingsMap::iterator addComboBox(QComboBox *comboBox,
														const Qst::Mvc::ComboBoxSettings &settings);

	QComboBox *defaultComboBox() const;

	bool contains(QAbstractItemView *view) const;
	bool contains(QComboBox *comboBox) const;

	bool detachView(QAbstractItemView *view);
	bool detachComboBox(QComboBox *comboBox);

	ModelType modelType() const;
	void setModelType(const ModelType & modelType);

	void modelizeViews();
	void demodelizeViews();
	void setupViews();

	void modelizeComboBoxes();
	void demodelizeComboBoxes();
	void setupComboBoxes();

	bool isValid() const;

	void clear();

private:

	void _setupView(QAbstractItemView *view,
					const int &columnName,
					const Qst::Mvc::ViewAppearance::ViewType &viewType,
					const Qst::Mvc::ColumnSetting &columnSetting,
					const bool &sortFilteringEnabled);

	void _setupTableView(QTableView * view,
						 const int &columnIndex,
						 const bool &visible,
						 const int &width,
						 const bool &sortingEnabled);

	void _setupTreeView(QTreeView * view,
						const int &columnIndex,
						const bool &visible,
						const int &width,
						const bool &sortingEnabled);

	void _setupListView(QListView * view,
						const int &columnIndex,
						const bool &visible);

	void _connectSignal(QAbstractItemModel *model, QAbstractItemView *view);
	void _disconnectSignal(QAbstractItemModel *model, QAbstractItemView *view);
};



}	// End of namespace Special
}	// End of namespace Qst

#endif // MODELVIEWDESCRIPTOR_H
