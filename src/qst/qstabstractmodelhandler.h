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

#ifndef QSTABSTRACTMODELHANDLER_H
#define QSTABSTRACTMODELHANDLER_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QComboBox>

#include <QAbstractItemView>

#include <QMap>
#include <QVariantMap>

#include "qstglobal.h"

#include "qst/special/modelviewdescriptor.h"

#include "qst/mvc/qstplainquerymodel.h"
#include "qst/mvc/qsttreequerymodel.h"

#include "querygeneration/abstractquerybuilder.h"
#include "qstbatch.h"
#include "qstvalue.h"

namespace Qst
{

typedef QMap<QString, QVariantList> QstVariantListMap;

class QstAbstractModelHandler	//FIX ME: documentation // FULL REWRITE
{
protected:

	static AbstractQueryBuilder *_queryBuilder;

	Qst::Special::ModelViewDescriptor	_modelViewDescriptor;

	QstBatch _batch;

	bool _loaded;

public:

	static void setQueryBuilder(AbstractQueryBuilder *queryBuilder);
	static AbstractQueryBuilder *queryBuilder();

	QstAbstractModelHandler();
	virtual ~QstAbstractModelHandler() = 0;

	virtual void reload(const QSqlDatabase &db = QSqlDatabase::database());

	virtual void unload();

	virtual bool isLoaded() const;

	virtual void setQuery(const QstBatch &batch);
	virtual void setQuery(const QString &queryString);
	virtual void setModel(QstPlainQueryModel *model);
	virtual void setModel(QstTreeQueryModel *model);

	virtual void setTableView(QTableView *tableView,
							  const SortModel &sortModel = SortUnchanged);
	virtual void setTreeView(QTreeView *treeView,
							 const SortModel &sortModel = SortUnchanged);
	virtual void setListView(QListView *listView,
							 const SortModel &sortModel = SortUnchanged);
	virtual void setTableView(QTableView *tableView,
							  const Qst::Mvc::ViewAppearance &viewApp);
	virtual void setTreeView(QTreeView *treeView,
							 const Qst::Mvc::ViewAppearance &viewApp);
	virtual void setListView(QListView *listView,
							 const Qst::Mvc::ViewAppearance &viewApp);

	virtual void setComboBox(QComboBox *comboBox);

	virtual bool detachComboBox(QComboBox *comboBox = NULL);
	virtual bool detachView(QAbstractItemView *view = NULL);

	virtual void setViewSetting(QAbstractItemView *view,
								const QString &fieldName,
								const Qst::Mvc::ColumnSetting::SettingType &settingType,
								const QVariant &settingValue);

	virtual void clear();

// ------------------------------------------------------------------------ //

	virtual QModelIndex modelIndex(const QVariant &keyValue,
								   const QAbstractItemView *view) const; // FIX ME: documentation. view for the sortFilterModel.

	virtual int fieldColumnIndex(const FieldRole &role) const;
	virtual int fieldColumnIndex(const QString &fieldName) const;

	virtual void setViewCurrentRow(const QVariant &keyValue,
								   QAbstractItemView *view = NULL);

	virtual void setComboBoxCurrentRow(const QVariant &keyValue,
									   QComboBox *comboBox = NULL);

// ------------------------------------------------------------------------ //
// Группа функций, извлекающих поля из модели для указанной
// или текущей строки во view (comboBox).

	virtual QVariantList	viewSelectedKeys(const FieldRole &role = RolePrimaryKey,
											 QAbstractItemView *view = NULL) const;

	virtual QVariant		viewKeyValue(const FieldRole &role = RolePrimaryKey,
										 const QModelIndex &index = QModelIndex(),
										 QAbstractItemView *view = NULL)  const;

	virtual QVariant		viewFieldValue(const QString &fieldName,
										   const QModelIndex &index = QModelIndex(),
										   QAbstractItemView *view = NULL)  const;

	virtual QVariantMap		viewFieldsValueMap(const QStringList &fieldNames = QStringList(),
											   const QModelIndex &index = QModelIndex(),
											   QAbstractItemView *view = NULL)  const;

	virtual void			viewExpandTo(const QVariant &keyValue,
										 QAbstractItemView *view = NULL,
										 const bool &setSelected = true); // FIX ME: documentation. // not work for sortfiltering.


	virtual QVariant		comboBoxKeyValue(const FieldRole &role = RolePrimaryKey,
											 const int &row = -1,
											 QComboBox *comboBox = NULL) const;

	virtual QVariant		comboBoxFieldValue(const QString &fieldName,
											   const int &row = -1,
											   QComboBox *comboBox = NULL) const;

	virtual QVariantMap		comboBoxFieldsValueMap(const QStringList &fieldNames = QStringList(),
												   const int &row = -1,
												   QComboBox *comboBox = NULL) const;

	virtual QVariant		fieldValue(const QString &fieldName,
									   const QModelIndex &index = QModelIndex()) const;

	virtual QVariantMap		fieldsValueMap(const QStringList &fieldNames = QStringList(),
										   const QModelIndex &index = QModelIndex()) const;

	// FIX ME: documentation
	virtual bool				isVirtuallyChechingEnabled() const;
	virtual QVariantList		virtuallyCheckedKeys(const FieldRole &role = RolePrimaryKey) const;		// FIX ME
	virtual QstVariantListMap	virtuallyCheckedFields(const QStringList &fieldNames,	// FIX ME
													   const QstWhere &conditions) const;

	static  QSqlQuery evalQuery(const QString &query,
								const QSqlDatabase &db = QSqlDatabase::database());

	static QString generateQuery(const QstBatch &batch);
	static QVariant execute(const QstBatch &batch,
							const QString &returnValueName = QString("return_value"));
	QVariant execute(const QString &returnValueName = QString("return_value")) const;

// -------------------------------------------------------------------------- //

	virtual void updatePlaceholder(const QString &placeholderName,
								   const QstValue &qstValue);

	virtual void updatePlaceholder(const QString &placeholderName,
								   const QVariant &value,
								   const Functor &functor = NoFunctor,
								   const PercentPlaceholders &percentPlaceholders = LeftRightPercents);

	virtual void updatePlaceholder(const QString &placeholderName,
								   const QVariantList &varList,
								   const Functor &functor = NoFunctor);

	virtual void updatePlaceholders(const QVariantMap &varMap);
	virtual void resetPlaceholders();

// -------------------------------------------------------------------------- //

	virtual Qst::Special::ModelViewDescriptor *modelViewDescriptor();
	virtual QAbstractItemModel *model() const;
	virtual QstBatch batch() const;

protected:

	virtual bool _reload(const QSqlDatabase &db);

	virtual void _unload();

	virtual bool _loadModel(const QstBatch &batch,
							QAbstractItemModel * model,
							const ModelType &modelType,
							const QSqlDatabase &db);

	virtual bool _loadModel(const QstBatch &batch,
							QstPlainQueryModel * model,
							const QSqlDatabase &db);

	virtual bool _loadModel(const QstBatch &batch,
							QstTreeQueryModel * model,
							const QSqlDatabase &db);

	virtual QVariant _fieldData(const QstBatch &batch,
								const QString &fieldName,
								const QModelIndex &index) const;

	virtual QVariant _fieldData(const QstBatch &batch,
								const FieldRole &role,
								const QModelIndex &index) const;

	virtual bool _setQuery(QstPlainQueryModel *model,
						   const QString &query,
						   const QSqlDatabase &db);
	virtual bool _setQuery(QstTreeQueryModel *model,
						   const QString &query,
						   const QSqlDatabase &db);

	virtual QModelIndexList		_virtuallyCheckedIndexes(QAbstractItemModel *model) const;	// FIX ME
	virtual QstVariantListMap	_virtuallyCheckedFields(const QStringList &fieldNames,		// FIX ME
														const QstWhere &conditions) const;

	virtual QModelIndex _getIndex(const QVariant &keyValue,
								  QAbstractItemModel *model) const;

	virtual void _viewExpandTo(const QModelIndex &index,
							   QTreeView *view); // FIX ME: documentation
};

}

#endif // QSTABSTRACTMODELHANDLER_H
