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

#ifndef NOTEITEMDELEGATE_H
#define NOTEITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "notetheme.h"

class NoteItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	NoteItemDelegate(QObject *parent = 0);
	~NoteItemDelegate();

	virtual void paint(QPainter *painter,
					   const QStyleOptionViewItem &option,
					   const QModelIndex &index) const;

	virtual QSize sizeHint(const QStyleOptionViewItem &option,
						   const QModelIndex &index) const;

private:

	NoteTheme _noteTheme;
};

#endif // NOTEITEMDELEGATE_H
