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
