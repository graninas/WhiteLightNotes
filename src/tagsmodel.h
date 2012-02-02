/****************************************************************************
** WhiteLight Notes 0.9 rc2
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

#ifndef TAGSMODEL_H
#define TAGSMODEL_H

#include "qst/mvc/qstplainquerymodel.h"

class TagsModel : public Qst::QstPlainQueryModel
{
public:
    TagsModel();

	void setTagSelectable(const QString &tag, const bool &selectable);
	void setTagColumnIndex(const int &columnIndex);

	Qt::ItemFlags flags ( const QModelIndex & index ) const;
	QVariant data(const QModelIndex &item, int role) const;

private:

	typedef QMap<QString, bool> SelectableTagMap;

	SelectableTagMap _selectableTagMap;
	int _tagColumnIndex;
};

#endif // TAGSMODEL_H
