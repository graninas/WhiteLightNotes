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

#include "noteitemdelegate.h"

#include <QRect>
#include <QTextDocument>

// http://stackoverflow.com/questions/1956542/how-to-make-item-view-render-rich-html-text-in-qt

NoteItemDelegate::NoteItemDelegate(QObject *parent)
	:
	  QStyledItemDelegate(parent)
{
}

NoteItemDelegate::~NoteItemDelegate()
{
}

void NoteItemDelegate::paint(QPainter *painter,
							 const QStyleOptionViewItem &option,
							 const QModelIndex &index) const
{
	QString htmlText = index.data().toString();
	QString oldTheme = _noteTheme.getThemePrefix(htmlText);
	QString newTheme = oldTheme;

	if (option.state & QStyle::State_Selected)
	{
		if (!oldTheme.contains("selected"))
			newTheme += ".selected";
		htmlText = _noteTheme.colorize(htmlText, _noteTheme.supportedTokens(), oldTheme, newTheme);
	}
	else
	{
		if (oldTheme.contains("selected"))
			newTheme.chop(8);
		htmlText = _noteTheme.colorize(htmlText, _noteTheme.supportedTokens(), oldTheme, newTheme);
	}

	QStyleOptionViewItemV4 options = option;
	initStyleOption(&options, index);
	options.text = "";
	options.state & 0;

	QRect clip(0, 0, options.rect.width(), options.rect.height());
	QTextDocument doc;
	doc.setHtml(htmlText);
	doc.setTextWidth(options.rect.width());

	painter->save();
	painter->translate(options.rect.left(), options.rect.top());
	doc.drawContents(painter, clip);
	painter->restore();
}

QSize NoteItemDelegate::sizeHint(const QStyleOptionViewItem &option,
								 const QModelIndex &index) const
{
	QStyleOptionViewItemV4 options = option;
	QTextDocument doc;

	initStyleOption(&options, index);
	doc.setHtml(index.data().toString());
	doc.setTextWidth(options.rect.width());
	return QSize(doc.idealWidth(), doc.size().height());
}
