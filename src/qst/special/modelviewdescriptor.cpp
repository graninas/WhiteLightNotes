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

#include "modelviewdescriptor.h"

#include <QDebug>

namespace Qst
{
namespace Special
{

using namespace Qst::Mvc;

/*!
\class ModelViewDescriptor
\brief
\lang_Russian
	Служебный класс для хранения модели данных, представлений (QTableView,
	QTreeView, QListView, QComboBox) и настроек этих представлений.

	Класс используется в QstAbstractModelHandler.
\endlang

\lang_English
	Service class. Stores data model, Qt's views (QTableView,
	QTreeView, QListView, QComboBox) and them settings.

	Used in QstAbstractModelHandler.
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
ModelViewDescriptor::ModelViewDescriptor()
	:
	_model(NULL),
	_modelType(PlainModel)
{
}

/*!
\lang_Russian
	Конструктор, принимающий модель данных и ее вид (плоская, иерархическая).
\endlang

\lang_English
	Constructor takes data model and model type (plain, tree).
\endlang
*/
ModelViewDescriptor::ModelViewDescriptor(QAbstractItemModel* model,
											   const ModelType & modelType)
	:
	_model(model),
	_modelType(modelType)
{
	Q_ASSERT(model != NULL);
}

/*!
\lang_Russian
	Деструктор.
\endlang

\lang_English
	Destructor.
\endlang
*/
ModelViewDescriptor::~ModelViewDescriptor()
{
}

/*!
\lang_Russian
	Возвращает указатель на модель данных.
\endlang

\lang_English
	Returns data model.
\endlang
*/
QAbstractItemModel *ModelViewDescriptor::model()
{
	return _model;
}

/*!
\lang_Russian
	Возвращает константный указатель на модель данных.
\endlang

\lang_English
	Returns const pointer to data model.
\endlang
*/
QAbstractItemModel *ModelViewDescriptor::model() const
{
	return _model;
}

/*!
\lang_Russian
	Устанавливает модель данных и ее вид (плоская, древовидная).
\endlang

\lang_English
	Sets data model and model type (plain, tree).
\endlang
*/
void ModelViewDescriptor::setModel(QAbstractItemModel *model,
								   const ModelType &modelType)
{
	Q_ASSERT(model != NULL);
	if (model == NULL)
		return;

	demodelizeViews();
	demodelizeComboBoxes();

	_model = model;
	_modelType = modelType;

	modelizeViews();
	modelizeComboBoxes();

	setupViews();
	setupComboBoxes();
}

/*!
\lang_Russian
	Добавляет представление и его настройки в массив представлений и возвращает его итератор.
\endlang

\lang_English
	Adds view and it's settings to the view map. Returns it's iterator.
\endlang
*/
void ModelViewDescriptor::setView(QAbstractItemView *view,
								  const ViewAppearance &viewAppearance)
{
	Q_ASSERT(view != NULL);
	_viewAppearanceMap.insert(view, viewAppearance);
}

/*!
\lang_Russian
	Возвращает первое возможное представление.
\endlang

\lang_English
	Returns first taken view.
\endlang
*/
QAbstractItemView *ModelViewDescriptor::defaultView() const
{
	if (_viewAppearanceMap.isEmpty())
		return NULL;

return _viewAppearanceMap.begin().key();
}

/*!
\lang_Russian
	Возвращает настройки представления.
\endlang

\lang_English
	Returns view's settings.
\endlang
*/
ViewAppearance ModelViewDescriptor::viewAppearance(QAbstractItemView *view) const
{
	return _viewAppearanceMap.value(view);
}

/*!
\lang_Russian
	Устанавливает и применяет настройки представления.
\endlang

\lang_English
	Sets and applies view's settings.
\endlang
*/
void ModelViewDescriptor::setViewSetting(QAbstractItemView *view,
										 const int &columnIndex,
										 const ColumnSetting::SettingType &settingType,
										 const QVariant &settingValue)
{
	Q_ASSERT(_viewAppearanceMap.contains(view));
	if (!_viewAppearanceMap.contains(view))
		return;

	_viewAppearanceMap[view].setColumnSetting(columnIndex, settingType, settingValue);

	_setupView(view,
			   columnIndex,
			   _viewAppearanceMap[view].viewType(),
			   _viewAppearanceMap[view].columnSetting(columnIndex),
			   _viewAppearanceMap[view].sortingEnabled());
}

/*!
\lang_Russian
	Добавляет QComboBox в массив объектов QComboBox и возвращает его итератор.
\endlang

\lang_English
	Adds comboBox and it's settings to the comboBox map. Returns it's iterator.
\endlang
*/
ComboBoxSettingsMap::iterator
		ModelViewDescriptor::addComboBox(QComboBox *comboBox,
										 const ComboBoxSettings &settings)
{
	Q_ASSERT(comboBox != NULL);
	if (comboBox == NULL)
		return _comboBoxSettingsMap.end();

	return _comboBoxSettingsMap.insert(comboBox, settings);
}

/*!
\lang_Russian
	Возвращает первый возможный comboBox.
\endlang

\lang_English
	Returns first taken comboBox.
\endlang
*/
QComboBox *ModelViewDescriptor::defaultComboBox() const
{
	if (_comboBoxSettingsMap.isEmpty())
		return NULL;

return _comboBoxSettingsMap.begin().key();
}

/*!
\lang_Russian
	Возвращает true, если view есть в массиве представлений.
\endlang

\lang_English
	Returns true if view it is in the view map.
\endlang
*/
bool ModelViewDescriptor::contains(QAbstractItemView *view) const
{
	return _viewAppearanceMap.contains(view);
}

/*!
\lang_Russian
	Возвращает true, если comboBox есть в массиве представлений.
\endlang

\lang_English
	Returns true if comboBox it is in the comboBox map.
\endlang
*/
bool ModelViewDescriptor::contains(QComboBox *comboBox) const
{
	return _comboBoxSettingsMap.contains(comboBox);
}

/*!
\lang_Russian
	Отсоединяет view, удаляет его из массива.
\endlang

\lang_English
	Detaches view, removes it from the view array.
\endlang
*/
bool ModelViewDescriptor::detachView(QAbstractItemView *view)
{
	if (view == NULL)
		return false;

	view->setModel(NULL);

	_disconnectSignal(_model, view);

	return _viewAppearanceMap.remove(view) > 0;
}

/*!
\lang_Russian
	Отсоединяет comboBox, удаляет его из массива.
\endlang

\lang_English
	Detaches comboBox, removes it from the comboBox array.
\endlang
*/
bool ModelViewDescriptor::detachComboBox(QComboBox *comboBox)
{
	if (comboBox == NULL)
		return false;

//	if (_comboBoxSettingsMap.contains(comboBox))
//		comboBox->setModel(_comboBoxSettingsMap[comboBox].dummyModel());

	comboBox->clear();
	return _comboBoxSettingsMap.remove(comboBox) > 0;
}

/*!
\lang_Russian
	Возвращает тип модели.
\endlang

\lang_English
	Returns model type.
\endlang
*/
ModelType ModelViewDescriptor::modelType() const
{
	return _modelType;
}

/*!
\lang_Russian
	Устанавливает тип модели.
\endlang

\lang_English
	Sets model type.
\endlang
*/
void ModelViewDescriptor::setModelType(const ModelType & modelType)
{
	_modelType = modelType;
}

/*!
\lang_Russian
	Привязывает представления к модели.
	Восстанавливает текущую позицию в представлении.
\endlang

\lang_English
	Binds views to models. Restores last current index in views.
\endlang
*/
void ModelViewDescriptor::modelizeViews()
{
	Q_ASSERT(_model != NULL);
	if (_model == NULL)
		return;

	ViewAppearanceMap::iterator iter = _viewAppearanceMap.begin();
	for (; iter != _viewAppearanceMap.end(); ++iter)
	{
		if (iter.value().sortingEnabled())
		{
			QSortFilterProxyModel * sortModel = iter.value().createSortFilterProxyModel(_model);
			iter.key()->setModel(sortModel);
			iter.key()->setCurrentIndex(sortModel->index(iter.value().currentIndex(), 0, QModelIndex()));
		}
		else
		{
			iter.key()->setModel(_model);
			iter.key()->setCurrentIndex(_model->index(iter.value().currentIndex(), 0, QModelIndex()));
		}

	_connectSignal(_model, iter.key());
	}
}

/*!
\lang_Russian
	Отвязывает модели от представлений.
	Запоминает текущую позицию в представлении.
\endlang

\lang_English
	Disconnects models and views. Remembers last current index in view.
\endlang
*/
void ModelViewDescriptor::demodelizeViews()
{
	ViewAppearanceMap::iterator iter = _viewAppearanceMap.begin();
	for (; iter != _viewAppearanceMap.end(); ++iter)
	{
		iter.value().setCurrentIndex(iter.key()->currentIndex().row());
		iter.value().deleteSortFilterProxyModel();
		iter.key()->setModel(NULL);

		_disconnectSignal(_model, iter.key());
	}
}

/*!
\lang_Russian
	Настраивает представления.
\endlang

\lang_English
	Setups views.
\endlang
*/
void ModelViewDescriptor::setupViews()
{
	QAbstractItemView *view;
	ColumnSettingsMap map;
	ColumnSettingsMap::iterator columnSettingIter;

	ViewAppearance viewAppearance;
	ColumnSetting columnSetting;

	ViewAppearanceMap::iterator viewSettingIter = _viewAppearanceMap.begin();
	for (; viewSettingIter != _viewAppearanceMap.end(); ++viewSettingIter)
	{
		view = viewSettingIter.key();
		viewAppearance = viewSettingIter.value();
		Q_ASSERT(view->model() != NULL);

		map = viewAppearance.columnSettingsMap();
		columnSettingIter = map.begin();

		for (; columnSettingIter != map.end(); ++columnSettingIter)
		{
			columnSetting = columnSettingIter.value();

			_setupView(view,
					   columnSettingIter.key(),
					   viewAppearance.viewType(),
					   columnSetting,
					   viewAppearance.sortingEnabled());
		}
	}
}

/*!
\lang_Russian
	Привязывает выпадающие списки к модели.
	Восстанавливает текущую позицию в представлении.
\endlang

\lang_English
	Binds comboBoxes to models. Restores last current index in comboBoxes.
\endlang
*/
void ModelViewDescriptor::modelizeComboBoxes()
{
	Q_ASSERT(_model != NULL);
	if (_model == NULL)
		return;

	ComboBoxSettingsMap::iterator iter = _comboBoxSettingsMap.begin();
	for (; iter != _comboBoxSettingsMap.end(); ++iter)
	{
		iter.key()->setModel(_model);
		iter.key()->setCurrentIndex(iter.value().currentIndex());
	}
}

/*!
\lang_Russian
	Отвязывает модели от выпадающих списков.
	Запоминает текущую позицию в каждом списке.
\endlang

\lang_English
	Disconnects models and comboBoxes. Remembers last current index in comboBoxes.
\endlang
*/
void ModelViewDescriptor::demodelizeComboBoxes()
{
	ComboBoxSettingsMap::iterator iter = _comboBoxSettingsMap.begin();
	for (; iter != _comboBoxSettingsMap.end(); ++iter)
	{
		iter.value().setCurrentIndex(iter.key()->currentIndex());
//		iter.key()->setModel(iter.value().dummyModel());
		iter.key()->clear();
	}
}

/*!
\lang_Russian
	Настраивает comboBoxes.
\endlang

\lang_English
	Setups comboBoxes.
\endlang
*/
void ModelViewDescriptor::setupComboBoxes()
{
	ComboBoxSettingsMap::iterator iter = _comboBoxSettingsMap.begin();
	for (; iter != _comboBoxSettingsMap.end(); ++iter)
	{
		iter.key()->setModelColumn(iter.value().modelColumn());
		iter.key()->setCurrentIndex(iter.value().currentIndex());
	}
}

/*!
\lang_Russian
	Возвращает true, если модель не NULL.
\endlang

\lang_English
	Returns true if model is not NULL.
\endlang
*/
bool ModelViewDescriptor::isValid() const
{
	return _model != NULL;
}

/*!
\lang_Russian
	Очищает списки представлений.
\endlang

\lang_English
	Clears all views and comboBoxes.
\endlang
*/
void ModelViewDescriptor::clear()
{
	demodelizeViews();
	demodelizeComboBoxes();

	_viewAppearanceMap.clear();
	_comboBoxSettingsMap.clear();
}

void ModelViewDescriptor::_setupView(QAbstractItemView *view,
									 const int &columnIndex,
									 const ViewAppearance::ViewType &viewType,
									 const ColumnSetting &columnSetting,
									 const bool &sortFilteringEnabled)
{
	view->model()->setHeaderData(columnIndex,
								 columnSetting.orientation(),
								 columnSetting.title(),
								 Qt::DisplayRole);

	switch (viewType)
	{
	case ViewAppearance::InvalidView:
		Q_ASSERT(false);
		break;
	case ViewAppearance::TableView:
		_setupTableView((QTableView*)view,
						columnIndex,
						columnSetting.isVisible(),
						columnSetting.width(),
						sortFilteringEnabled);
	break;

	case ViewAppearance::TreeView:
		_setupTreeView((QTreeView*)view,
					   columnIndex,
					   columnSetting.isVisible(),
					   columnSetting.width(),
					   sortFilteringEnabled);
	break;
	case ViewAppearance::ListView:
		_setupListView((QListView*)view,
					   columnIndex,
					   columnSetting.isVisible());
	break;
	}

}

void ModelViewDescriptor::_setupTableView(QTableView * view,
										  const int &columnIndex,
										  const bool &visible,
										  const int &width,
										  const bool &sortFilteringEnabled)
{
	view->setColumnHidden(columnIndex, !visible);
	view->setColumnWidth(columnIndex, width);
	view->setSortingEnabled(sortFilteringEnabled);
}

void ModelViewDescriptor::_setupTreeView(QTreeView * view,
										 const int &columnIndex,
										 const bool &visible,
										 const int &width,
										 const bool &sortFilteringEnabled)
{
	view->setColumnHidden(columnIndex, !visible);
	view->setColumnWidth(columnIndex, width);
	view->setSortingEnabled(sortFilteringEnabled);
}

void ModelViewDescriptor::_setupListView(QListView * view,
										 const int &columnIndex,
										 const bool &visible)
{
	Q_UNUSED(view);
	Q_UNUSED(columnIndex);
	Q_UNUSED(visible);
}

void ModelViewDescriptor::_connectSignal(QAbstractItemModel *model,
										 QAbstractItemView *view)
{
	QObject::connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
					 view, SLOT(dataChanged(QModelIndex,QModelIndex)));
}

void ModelViewDescriptor::_disconnectSignal(QAbstractItemModel *model,
											QAbstractItemView *view)
{
	QObject::disconnect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
						view, SLOT(dataChanged(QModelIndex,QModelIndex)));
}

}	// End of namespace Special
}	// End of namespace Qst
