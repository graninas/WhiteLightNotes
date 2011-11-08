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

#include "qstabstractmodelhandler.h"

#include <QObject>
#include <QDebug>

#include <QSqlRecord>

#include "querygeneration/querybuilddirector.h"

namespace Qst
{

using namespace Qst::Mvc;
using namespace Qst::Special;


AbstractQueryBuilder *QstAbstractModelHandler::_queryBuilder;

void QstAbstractModelHandler::setQueryBuilder(AbstractQueryBuilder *queryBuilder)
{
	_queryBuilder = queryBuilder;
}

AbstractQueryBuilder *QstAbstractModelHandler::queryBuilder()
{
	return _queryBuilder;
}

QstAbstractModelHandler::QstAbstractModelHandler()
	:
	_loaded(false)
{
}

QstAbstractModelHandler::~QstAbstractModelHandler()
{
}

////////////////////////////////////////////////////////////////////////////////

void QstAbstractModelHandler::reload(const QSqlDatabase &db)
{
	_reload(db);
}

void QstAbstractModelHandler::unload()
{
	_unload();
}

bool QstAbstractModelHandler::isLoaded() const
{
	return _loaded;
}

void QstAbstractModelHandler::setQuery(const QstBatch &batch)
{
	if (isLoaded())
		_unload();

	_batch = batch;
}

void QstAbstractModelHandler::setQuery(const QString &queryString)
{
	if (isLoaded())
		_unload();

	QueryBatch qB = QueryBatch(UserDefinedQuery, "");
	qB.setUserDefinedQuery(queryString);

	_batch = QstBatch(qB);
}

void QstAbstractModelHandler::setModel(QstPlainQueryModel *model)
{
	if (isLoaded())
		_unload();

	_modelViewDescriptor.setModel(model, PlainModel);
}

void QstAbstractModelHandler::setModel(QstTreeQueryModel *model)
{
	if (isLoaded())
		_unload();

	_modelViewDescriptor.setModel(model, TreeModel);
}

void QstAbstractModelHandler::setTableView(QTableView *tableView,
										   const SortModel &sortModel)
{
	Q_ASSERT(tableView != NULL);

	Qst::Mvc::ViewAppearance viewApp = _batch.viewAppearance();
	if (sortModel != SortUnchanged)
		viewApp.setSortingEnabled(sortModel == SortEnabled);
	setTableView(tableView, viewApp);
}

void QstAbstractModelHandler::setTreeView(QTreeView *treeView,
										  const SortModel &sortModel)
{
	Q_ASSERT(treeView != NULL);

	Qst::Mvc::ViewAppearance viewApp = _batch.viewAppearance();
	if (sortModel != SortUnchanged)
		viewApp.setSortingEnabled(sortModel == SortEnabled);
	setTreeView(treeView, viewApp);
}

void QstAbstractModelHandler::setListView(QListView *listView,
										  const SortModel &sortModel)
{
	Q_ASSERT(listView != NULL);

	Qst::Mvc::ViewAppearance viewApp = _batch.viewAppearance();
	if (sortModel != SortUnchanged)
		viewApp.setSortingEnabled(sortModel == SortEnabled);
	setListView(listView, viewApp);
}

void QstAbstractModelHandler::setTableView(QTableView *tableView,
										   const Qst::Mvc::ViewAppearance &viewApp)
{
	Q_ASSERT(tableView != NULL);
	ViewAppearance app = viewApp;
	app.setViewType(ViewAppearance::TableView);
	_modelViewDescriptor.setView(tableView, app);
}

void QstAbstractModelHandler::setTreeView(QTreeView *treeView,
										  const Qst::Mvc::ViewAppearance &viewApp)
{
	Q_ASSERT(treeView != NULL);
	ViewAppearance app = viewApp;
	app.setViewType(ViewAppearance::TreeView);
	_modelViewDescriptor.setView(treeView, app);
}

void QstAbstractModelHandler::setListView(QListView *listView,
										  const Qst::Mvc::ViewAppearance &viewApp)
{
	Q_ASSERT(listView != NULL);
	ViewAppearance app = viewApp;
	app.setViewType(ViewAppearance::ListView);
	_modelViewDescriptor.setView(listView, app);
}

void QstAbstractModelHandler::setComboBox(QComboBox * comboBox)
{
	Q_ASSERT(comboBox != NULL);

	ComboBoxSettings sets = _batch.comboBoxSettings();
	_modelViewDescriptor.addComboBox(comboBox, sets);
}

bool QstAbstractModelHandler::detachComboBox(QComboBox * comboBox)
{
	return _modelViewDescriptor.detachComboBox(comboBox);
}


bool QstAbstractModelHandler::detachView(QAbstractItemView *view)
{
	return _modelViewDescriptor.detachView(view);
}

void QstAbstractModelHandler::setViewSetting(QAbstractItemView *view,
											 const QString &fieldName,
											 const ColumnSetting::SettingType &settingType,
											 const QVariant &settingValue)
{
	Q_ASSERT(view != NULL);
	if (view == NULL)
		return;

	int columnIndex = fieldColumnIndex(fieldName);
	_modelViewDescriptor.setViewSetting(view, columnIndex, settingType, settingValue);
}

void QstAbstractModelHandler::clear()
{
	_unload();
}

QModelIndex QstAbstractModelHandler::modelIndex(const QVariant &keyValue,
												const QAbstractItemView *view) const
{
	Q_ASSERT(view != NULL);
	Q_ASSERT(view->model() != NULL);

	if (view == NULL
		|| view->model() == NULL)
	{
		qDebug()	<< "\nWARNING! Cant retreive modelIndex for value : " << keyValue << ".\n"
					<< "view != NULL:" << (view != NULL)
					<< ", view->model() != NULL: " << (view->model() != NULL) << ".";
		return QModelIndex();
	}

	return _getIndex(keyValue, view->model());
}

int QstAbstractModelHandler::fieldColumnIndex(const FieldRole &role) const
{
	Q_ASSERT(role != RoleNone);

	return _batch.columnIndex(role);
}

int QstAbstractModelHandler::fieldColumnIndex(const QString &fieldName) const
{
	Q_ASSERT(!fieldName.isEmpty());

	return _batch.columnIndex(fieldName);
}

void QstAbstractModelHandler::setViewCurrentRow(const QVariant &keyValue,
												QAbstractItemView *view)
{
	QAbstractItemView *v = view;
	if (v == NULL)
		v = _modelViewDescriptor.defaultView();

	Q_ASSERT(_modelViewDescriptor.contains(v));
	Q_ASSERT(isLoaded());

	if (!_modelViewDescriptor.contains(v)
		|| !isLoaded())
		return;

	if (!keyValue.isValid())
		return;

	v->setCurrentIndex(_getIndex(keyValue, _modelViewDescriptor.model()));
}

void QstAbstractModelHandler::setComboBoxCurrentRow(const QVariant &keyValue,
													QComboBox *comboBox)
{
	QComboBox *c = comboBox;
	if (c == NULL)
		c = _modelViewDescriptor.defaultComboBox();

	Q_ASSERT(_modelViewDescriptor.contains(c));
	Q_ASSERT(isLoaded());

	if (!_modelViewDescriptor.contains(c)
		|| !isLoaded())
		return;

	if (!keyValue.isValid())
		return;

	c->setCurrentIndex(_getIndex(keyValue, _modelViewDescriptor.model()).row());
}

QVariantList QstAbstractModelHandler::viewSelectedKeys(const FieldRole &role,
													   QAbstractItemView *view) const
{
	QAbstractItemView *v = view;
	if (v == NULL)
		v = _modelViewDescriptor.defaultView();

	Q_ASSERT(_modelViewDescriptor.contains(v));
	Q_ASSERT(v->model() != NULL);
	Q_ASSERT(isLoaded());

	if (!_modelViewDescriptor.contains(v)
		|| v->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from view for role: " << role << ".\n"
					<< "view exist:" << _modelViewDescriptor.contains(v)
					<< ", model == NULL: " << (v->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariantList();
	}

	QVariantList keysList;

	int keysColumnIndex = fieldColumnIndex(role);
	QModelIndexList indexesList = v->selectionModel()->selectedIndexes();

	for (int i = 0; i < indexesList.size(); ++i)
		if (indexesList[i].column() == keysColumnIndex)
			keysList.append(indexesList[i].data());

return keysList;
}

QVariant QstAbstractModelHandler::viewKeyValue(const FieldRole &role,
											   const QModelIndex &index,
											   QAbstractItemView *view)  const
{
	QAbstractItemView *v = view;
	if (v == NULL)
		v = _modelViewDescriptor.defaultView();

	Q_ASSERT(_modelViewDescriptor.contains(v));
	Q_ASSERT(v->model() != NULL);
	Q_ASSERT(isLoaded());

	QModelIndex realIndex = (index.isValid()) ? index : v->currentIndex();

	if (!_modelViewDescriptor.contains(v)
		|| v->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from view for index: " << realIndex << ".\n"
					<< "view exist:" << _modelViewDescriptor.contains(v)
					<< ", model == NULL: " << (v->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariant();
	}

	return _fieldData(_batch, role, realIndex);
}

QVariant QstAbstractModelHandler::viewFieldValue(const QString &fieldName,
												 const QModelIndex &index,
												 QAbstractItemView *view) const
{
	QAbstractItemView *v = view;
	if (v == NULL)
		v = _modelViewDescriptor.defaultView();

	Q_ASSERT(_modelViewDescriptor.contains(v));
	Q_ASSERT(v->model() != NULL);
	Q_ASSERT(isLoaded());

	QModelIndex realIndex = (index.isValid()) ? index : v->currentIndex();

	if (!_modelViewDescriptor.contains(v)
		|| v->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from view for index: " << realIndex << ".\n"
					<< "view exist:" << _modelViewDescriptor.contains(v)
					<< ", model == NULL: " << (v->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariant();
	}

	return _fieldData(_batch, fieldName, realIndex);
}

QVariantMap QstAbstractModelHandler::viewFieldsValueMap(const QStringList &fieldNames,
														const QModelIndex &index,
														QAbstractItemView *view)  const
{
	QAbstractItemView *v = view;
	if (v == NULL)
		v = _modelViewDescriptor.defaultView();

	Q_ASSERT(_modelViewDescriptor.contains(v));
	Q_ASSERT(v->model() != NULL);
	Q_ASSERT(isLoaded());

	QModelIndex realIndex = (index.isValid()) ? index : v->currentIndex();

	if (!_modelViewDescriptor.contains(v)
		|| v->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from view for index: " << realIndex << ".\n"
					<< "view exist:" << _modelViewDescriptor.contains(v)
					<< ", model == NULL: " << (v->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariantMap();
	}

	QStringList realFieldNames = (fieldNames.isEmpty()) ? _batch.fieldNames() : fieldNames;

	QString fieldName;
	QVariantMap resMap;

	foreach (fieldName, realFieldNames)
		resMap[fieldName] = _fieldData(_batch, fieldName, realIndex);

return resMap;
}

void QstAbstractModelHandler::viewExpandTo(const QVariant &keyValue,
										   QAbstractItemView *view,
										   const bool &setSelected)
{
	QAbstractItemView *v = view;
	if (v == NULL)
		v = _modelViewDescriptor.defaultView();

	Q_ASSERT(_modelViewDescriptor.contains(v));
	Q_ASSERT(v->model() != NULL);
	Q_ASSERT(isLoaded());
	Q_ASSERT(_modelViewDescriptor.viewAppearance(v).viewType() == ViewAppearance::TreeView);

	if (!_modelViewDescriptor.contains(v)
		|| v->model() == NULL
		|| !isLoaded()
		|| _modelViewDescriptor.viewAppearance(v).viewType() != ViewAppearance::TreeView)
	{
		qDebug()	<< "\nWARNING! Cant expand to keyValue : " << keyValue << ".\n"
					<< "view exist:" << _modelViewDescriptor.contains(v)
					<< ", model == NULL: " << (v->model() == NULL)
					<< ", handler loaded: " << isLoaded()
					<< ", is tree view: " << (_modelViewDescriptor.viewAppearance(v).viewType() != ViewAppearance::TreeView) << ".";
		return;
	}

	QModelIndex index = _getIndex(keyValue, v->model());

	_viewExpandTo(index, static_cast<QTreeView*>(v));

	if (setSelected)
		v->setCurrentIndex(index);
}

QVariant QstAbstractModelHandler::comboBoxKeyValue(const FieldRole &role,
												   const int &row,
												   QComboBox *comboBox) const
{
	QComboBox *c = comboBox;
	if (c == NULL)
		c = _modelViewDescriptor.defaultComboBox();

	Q_ASSERT(_modelViewDescriptor.contains(c));
	Q_ASSERT(c->model() != NULL);
	Q_ASSERT(isLoaded());

	QModelIndex index = (row == -1) ? c->model()->index(c->currentIndex(), 0) : c->model()->index(row, 0);

	if (!_modelViewDescriptor.contains(c)
		|| c->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from comboBox for role: " << role << " and index: " << index << ".\n"
					<< "comboBox exist:" << _modelViewDescriptor.contains(c)
					<< ", model == NULL: " << (c->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariant();
	}

	return _fieldData(_batch, role, index);
}

QVariant QstAbstractModelHandler::comboBoxFieldValue(const QString &fieldName,
													 const int &row,
													 QComboBox *comboBox) const
{
	QComboBox *c = comboBox;
	if (c == NULL)
		c = _modelViewDescriptor.defaultComboBox();

	Q_ASSERT(_modelViewDescriptor.contains(c));
	Q_ASSERT(c->model() != NULL);
	Q_ASSERT(isLoaded());

	QModelIndex index = (row == -1) ? c->model()->index(c->currentIndex(), 0) : c->model()->index(row, 0);

	if (!_modelViewDescriptor.contains(c)
		|| c->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from comboBox for index: " << index << ".\n"
					<< "comboBox exist:" << _modelViewDescriptor.contains(c)
					<< ", model == NULL: " << (c->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariant();
	}

	return _fieldData(_batch, fieldName, index);
}

QVariantMap QstAbstractModelHandler::comboBoxFieldsValueMap(const QStringList &fieldNames,
															const int &row,
															QComboBox *comboBox) const
{
	QComboBox *c = comboBox;
	if (c == NULL)
		c = _modelViewDescriptor.defaultComboBox();

	Q_ASSERT(_modelViewDescriptor.contains(c));
	Q_ASSERT(isLoaded());
	Q_ASSERT(c->model() != NULL);

	QModelIndex realIndex = (row == -1) ? c->model()->index(c->currentIndex(),0)
										: c->model()->index(row, 0);

	if (!_modelViewDescriptor.contains(c)
		|| c->model() == NULL
		|| !isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from comboBox for row: " << row << ".\n"
					<< "comboBox exist:" << _modelViewDescriptor.contains(c)
					<< ", model == NULL: " << (c->model() == NULL)
					<< ", handler loaded: " << isLoaded() << ".";
		return QVariantMap();
	}

	QStringList realFieldNames = (fieldNames.isEmpty()) ? _batch.fieldNames() : fieldNames;

	QString fieldName;
	QVariantMap resMap;

	foreach (fieldName, realFieldNames)
		resMap[fieldName] = _fieldData(_batch, fieldName, realIndex);

return resMap;
}

QVariant QstAbstractModelHandler::fieldValue(const QString &fieldName,
											 const QModelIndex &index) const
{
	Q_ASSERT(isLoaded());

	QModelIndex realIndex = ((index.isValid()) ? index : _modelViewDescriptor.model()->index(0,0));

	if (!isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data for field: " << fieldName
					<< " and index: " << realIndex << ". Data model is not loaded.";
		return QVariant();
	}

	return _fieldData(_batch, fieldName, realIndex);
}

QVariantMap QstAbstractModelHandler::fieldsValueMap(const QStringList &fieldNames,
													const QModelIndex &index) const
{
	Q_ASSERT(isLoaded());

	QModelIndex realIndex = (index.isValid() ? index : _modelViewDescriptor.model()->index(0,0));
	QStringList realFieldNames = (fieldNames.isEmpty()) ? _batch.fieldNames()
														: fieldNames;

	if (!isLoaded())
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data for fields: " << realFieldNames
					<< " and index: " << realIndex << ". Data model is not loaded.";
		return QVariantMap();
	}

	QString fieldName;
	QVariantMap resMap;

	foreach (fieldName, realFieldNames)
		resMap[fieldName] = _fieldData(_batch, fieldName, realIndex);

	return resMap;
}

bool QstAbstractModelHandler::isVirtuallyChechingEnabled() const
{
	if (_modelViewDescriptor.modelType() != TreeModel)
	{
		qDebug() <<  "\n WARNING! Virtual checking for rows is not available for Plain Model.";
		return false;
	}

	QstTreeQueryModel *treeModel = static_cast<QstTreeQueryModel*>(_modelViewDescriptor.model());
	return treeModel->isVirtuallyCheckingEnabled();
}

QVariantList QstAbstractModelHandler::virtuallyCheckedKeys(const FieldRole &role) const
{
	if (_modelViewDescriptor.modelType() != TreeModel)
	{
		qDebug() <<  "\n WARNING! Virtual checking for rows is not available for Plain Model.";
		return QVariantList();
	}

	QModelIndexList checkedIndexes = _virtuallyCheckedIndexes(_modelViewDescriptor.model());

	QVariantList resList;

	for (int i = 0; i < checkedIndexes.count(); ++i)
		resList.append(_fieldData(_batch, role, checkedIndexes.at(i)));

return resList;
}

QstVariantListMap QstAbstractModelHandler::virtuallyCheckedFields(const QStringList &fieldNames,
																  const QstWhere &conditions) const
{
	Q_ASSERT(isLoaded());

	if (!isLoaded())
	{
		qDebug()	<< "\n WARNING! Cant retrieve virtually checked fields, "
					<< ", isLoaded: " << isLoaded();
		return QstVariantListMap();
	}

	if (_modelViewDescriptor.modelType() != TreeModel)
	{
		qDebug() <<  "\n WARNING! Virtual checking for rows is not available for Plain Model.";
		return QstVariantListMap();
	}

	return _virtuallyCheckedFields(fieldNames, conditions);
}

QSqlQuery QstAbstractModelHandler::evalQuery(const QString &query,
											 const QSqlDatabase &db)
{
	Q_ASSERT(db.isOpen());
	if (!db.isOpen())
		return false;

	QSqlQuery q(db);

	qDebug() << "\n Execution of the user defined query: ";
	qDebug() << query;

	if (!q.prepare(query) || !q.exec())
		qDebug() << q.lastError().text();

return q;
}

QString QstAbstractModelHandler::generateQuery(const QstBatch &batch)
{
	QueryBuildDirector buildDir;
	QueryFrame frame = buildDir.build(batch.queryBatch(), queryBuilder());
	return frame.toString();
}

QVariant QstAbstractModelHandler::execute(const QstBatch &batch,
										  const QString &returnValueName)
{
	QSqlQuery query = evalQuery(generateQuery(batch));
	QSqlRecord record;

	if (query.isActive() && query.first())
		record = query.record();

return record.value(returnValueName);
}

QVariant QstAbstractModelHandler::execute(const QString &returnValueName) const
{
	return execute(_batch, returnValueName);
}

void QstAbstractModelHandler::updatePlaceholder(const QString &placeholderName,
												const QstValue &qstValue)
{
	Q_ASSERT(_batch != QstBatch());
	_batch.updatePlaceholder(placeholderName, qstValue);
}

void QstAbstractModelHandler::updatePlaceholder(const QString &placeholderName,
												const QVariant &value,
												const Functor &functor,
												const PercentPlaceholders &percentPlaceholders)
{
	Q_ASSERT(_batch != QstBatch());
	_batch.updatePlaceholder(placeholderName, value, functor, percentPlaceholders);
}

void QstAbstractModelHandler::updatePlaceholder(const QString &placeholderName,
												const QVariantList &varList,
												const Functor &functor)
{
	Q_ASSERT(_batch != QstBatch());
	_batch.updatePlaceholder(placeholderName, varList, functor);
}

void QstAbstractModelHandler::updatePlaceholders(const QVariantMap &varMap)
{
	Q_ASSERT(_batch != QstBatch());
	_batch.updatePlaceholders(varMap);
}

void QstAbstractModelHandler::resetPlaceholders()
{
	_batch.resetPlaceholders();
}

ModelViewDescriptor *QstAbstractModelHandler::modelViewDescriptor()
{
	return &_modelViewDescriptor;
}

QAbstractItemModel *QstAbstractModelHandler::model() const
{
	return _modelViewDescriptor.model();
}

QstBatch QstAbstractModelHandler::batch() const
{
	return _batch;
}

bool QstAbstractModelHandler::_reload(const QSqlDatabase &db)
{
	Q_ASSERT(db.isOpen());
	Q_ASSERT(_modelViewDescriptor.isValid());
	if (!db.isOpen()
		|| !_modelViewDescriptor.isValid())
		return false;

	_loaded = false;

// Загружается модель, содержащая реальные данные.
bool success = _loadModel(_batch,
						  _modelViewDescriptor.model(),
						  _modelViewDescriptor.modelType(),
						  db);

if (!success)
	return false;

_modelViewDescriptor.setModel(_modelViewDescriptor.model(),
							  _modelViewDescriptor.modelType());
_loaded = true;
return true;
}

void QstAbstractModelHandler::_unload()
{
	_modelViewDescriptor.clear();
	_loaded = false;
}

bool QstAbstractModelHandler::_loadModel(const QstBatch &batch,
										 QAbstractItemModel *model,
										 const ModelType &modelType,
										 const QSqlDatabase &db)
{
	if (modelType == PlainModel)
		return _loadModel(batch, (QstPlainQueryModel*)model, db);
	else
		return _loadModel(batch, (QstTreeQueryModel*)model, db);
}

bool  QstAbstractModelHandler::_loadModel(const QstBatch &batch,
										  QstPlainQueryModel *model,
										  const QSqlDatabase &db)
{
	QString query = generateQuery(batch);
	qDebug() << "\n For the _loadModel function, query will be:\n" << query;

	return _setQuery(model, query, db);
}

bool  QstAbstractModelHandler::_loadModel(const QstBatch &batch,
										  QstTreeQueryModel  *model,
										  const QSqlDatabase &db)
{
	QString query = generateQuery(batch);
	qDebug() << "\n For the _loadModel function, query will be:\n" << query;

	model->setFieldRoleIndexMap(batch.fieldRoleIndexMap());

	return _setQuery(model, query, db);
}

QVariant QstAbstractModelHandler::_fieldData(const QstBatch &batch,
											 const QString &fieldName,
											 const QModelIndex &index) const
{
	int columnIndex = batch.columnIndex(fieldName);
	Q_ASSERT(columnIndex != -1);

	if (columnIndex == -1)
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from model for field: " << fieldName << " and index: " << index << ".\n"
					<< "index.isValid(): " << index.isValid()
					<< ", field exist: " << (columnIndex != -1) << ".";
		return QVariant();
	}

	QVariant res =
		index.model()->data(index.model()->index(index.row(), columnIndex, index.parent()));
return res;
}

QVariant QstAbstractModelHandler::_fieldData(const QstBatch &batch,
											 const FieldRole &role,
											 const QModelIndex &index) const
{
	int columnIndex = batch.columnIndex(role);

	Q_ASSERT(index.isValid());
	Q_ASSERT(columnIndex != -1);

	if (!index.isValid()
		|| columnIndex == -1)
	{
		qDebug()	<< "\nWARNING! Cant retrieve field data from model for role: " << role << " and index: " << index << ".\n"
					<< "index.isValid():" <<index.isValid()
					<< ", field exist: " << (columnIndex != -1) << ".";
		return QVariant();
	}

	QVariant res =
		index.model()->data(index.model()->index(index.row(), columnIndex, index.parent()));
return res;
}

bool QstAbstractModelHandler::_setQuery(QstPlainQueryModel *model,
										const QString &query,
										const QSqlDatabase &db)
{
	model->setQuery(query, db);

	if (model->lastError().isValid())
	{
		qDebug() << model->lastError().text();
		return false;
	}
return true;
}

bool QstAbstractModelHandler::_setQuery(QstTreeQueryModel *model,
										const QString &query,
										const QSqlDatabase &db)
{
	model->setQuery(query, db);

	if (model->lastError().isValid())
	{
		qDebug() << model->lastError().text();
		return false;
	}
return true;
}

QModelIndexList QstAbstractModelHandler::_virtuallyCheckedIndexes(QAbstractItemModel *model) const
{
	QstTreeQueryModel *treeModel = static_cast<QstTreeQueryModel*>(model);
	return treeModel->virtuallyCheckedIndexes();
}

QstVariantListMap QstAbstractModelHandler::_virtuallyCheckedFields(const QStringList &fieldNames,
																   const QstWhere &conditions) const
{
//	QModelIndexList checkedIndexes = _virtuallyCheckedIndexes(_modelViewDescriptor.model());
//	QStringList		realFieldNames = (fieldNames.isEmpty()) ? _batch.fieldNames() : fieldNames;

	QstVariantListMap resMap;

//	foreach (QString fieldName, realFieldNames)
//	{
//		QVariantList list;
//		foreach (QModelIndex index, checkedIndexes)
//		{
//			bool pass = true;
//			foreach (QstField conditionField, conditions)
//			{
//				if (!conditionField.testValue(_fieldData(btch, conditionField.name(), index)))
//				{
//					pass = false;
//					break;
//				}
//			}

//			if (pass)
//				list.append(_fieldData(btch, fieldName, index));
//		}
//		resMap[fieldName] = list;
//	}
return resMap;
}

QModelIndex QstAbstractModelHandler::_getIndex(const QVariant &keyValue, QAbstractItemModel *model) const
{
	Q_ASSERT(model != NULL);

	QModelIndexList list;

	list = model->match(QModelIndex(),
						Qt::DisplayRole,
						keyValue,
						1,
						Qt::MatchExactly);

	if (list.isEmpty() || !list.first().isValid())
		return QModelIndex();

return list.first();
}

void QstAbstractModelHandler::_viewExpandTo(const QModelIndex &index,
											QTreeView *view)
{
	if (index.isValid())
		_viewExpandTo(index.parent(), view);

	view->expand(index);
}

}	// End of namespace Qst
