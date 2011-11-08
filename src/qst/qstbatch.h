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

#ifndef QSTBATCH_H
#define QSTBATCH_H

#include <QStringList>
#include <QList>
#include <QMap>

#include "querygeneration/querybatch.h"
#include "qstfield.h"
#include "qstwhere.h"

#include "qstrolevisibility.h"
#include "qstif.h"

#include "qst/mvc/viewappearance.h"
#include "qst/mvc/comboboxsettings.h"

#include "qst/qstabstractitemnameextractor.h"
#include "qst/qstdefaultitemnameextractor.h"

#include "qst/qstvalue.h"
#include "qst/qstplaceholder.h"

namespace Qst
{

typedef QstIf<QstField> QstFieldIf;
typedef QstIf<QString>	QstSourceIf;
typedef QMap<QString, QString> QstStringMap;

class QstBatch	// FIX ME: documentation // FULL REWRITE
{
private:

	QstAbstractItemNameExtractor *_itemNameExtractor;
	static QstDefaultItemNameExtractor _defaultExtractor;

	QueryBatch                  _queryBatch;
	Qst::Mvc::ViewAppearance    _viewAppearance;

	QStringList  _fieldNames;
	QstStringMap _extractedFieldNames;

	FieldRoleIndexMap _fieldRoleIndexMap;

public:
	QstBatch();

	explicit QstBatch(const QueryType &queryType,
					  const QString name = QString());

	explicit QstBatch(const QueryBatch &queryBatch,
					  const Qst::Mvc::ViewAppearance &appearance = Qst::Mvc::ViewAppearance());

	void addSource(const QString &source);
	void addSource(const QstSourceIf &sourceIf);

	void addField(const QstField &field);
	void addField(const QstFieldIf &fieldIf);

	void addCondition(const QstWhere &cond);

	void setQueryBatch(const QueryBatch &queryBatch);
	QueryBatch queryBatch() const;

	void setItemNameExtractor(QstAbstractItemNameExtractor *extractor);

	Qst::Mvc::ViewAppearance   viewAppearance() const;
	Qst::Mvc::ComboBoxSettings comboBoxSettings() const;	// FIX ME

	FieldRoleIndexMap fieldRoleIndexMap() const;
	QStringList       fieldNames(const bool &extracted = true) const;
	QstStringMap      extractedFieldNames() const;

	int columnIndex(const FieldRole &role) const;
	int columnIndex(const QString &fieldName) const;

	QstBatch & updatePlaceholder(const QString &placeholderName,
								 const QstValue &qstValue);

	QstBatch & updatePlaceholder(const QString &placeholderName,
								 const QVariant &value,
								 const Functor &functor = NoFunctor,
								 const PercentPlaceholders &percentPlaceholders = LeftRightPercents);

	QstBatch & updatePlaceholder(const QString &placeholderName,
								 const QVariantList &varList,
								 const Functor &functor = NoFunctor);

	QstBatch & updatePlaceholders(const QVariantMap &newValues);
	void resetPlaceholders();

	QstBatch & operator<<(const QString &source);
	QstBatch & operator<<(const QstSourceIf &sourceIf);

	QstBatch & operator<<(const QstField &field);
	QstBatch & operator<<(const QstFieldIf &fieldIf);

	QstBatch & operator<<(const QstWhere &cond);

	QstBatch & select(const QstField &field);
	QstBatch & from(const QString &source);

	QstBatch & where(const QstWhere &condition);
	QstBatch & where(const QString &strCond);

	QstBatch & where(const QString &fieldName,
					 const QstPlaceholder &placeholder,
					 const Functor &functor = NoFunctor);

	QstBatch & where(const QString &fieldName,
					 const QueryValue &value1,
					 const QueryValue &value2);

	QstBatch & where(const QueryIn &in);

	QstBatch & join(const QueryBatch &batch, const QueryOn &condition);
	QstBatch & join(const Qst::QueryClause &joinClause,
					const QString &tableName,
					const QueryOn &condition);
	QstBatch & innerJoin(const QString &tableName, const QueryOn &condition);
	QstBatch & leftJoin(const QString &tableName, const QueryOn &condition);
	QstBatch & rightJoin(const QString &tableName, const QueryOn &condition);
	QstBatch & fullJoin(const QString &tableName, const QueryOn &condition);
	QstBatch & groupBy(const QString &fieldName);
	QstBatch & having(const QueryHaving &condition);
	QstBatch & having(const QString &strCond);
	QstBatch & orderBy(const QString &fieldName);

	QstBatch & insert(const QString &tableName,
						const QStringList &fieldNames = QStringList());
	QstBatch & values(const QueryFieldList &fieldValues);
	QstBatch & values(const QueryValueList &values);
	QstBatch & values(const QVariantList &values);

	QstBatch & update(const QString &tableName);
	QstBatch & set(const QueryFieldList &fields);

	QstBatch & deleteFrom(const QString &tableName);

	QstBatch & execute(const QString &funcName);
	QstBatch & parameters(const QstPlaceholderList &placeholderList);
	QstBatch & parameters(const QstPlaceholder &placeholder);

	friend bool operator == (const QstBatch &val1, const QstBatch &val2)
	{
		return val1._queryBatch == val2._queryBatch
				&& val1._viewAppearance == val2._viewAppearance;
	}

	friend bool operator != (const QstBatch &val1, const QstBatch &val2)
	{
		return !(val1 == val2);
	}
};

} // End of namespace Qst

#endif // QSTBATCH_H
