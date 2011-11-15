#ifndef NOTEITEMDELEGATE_H
#define NOTEITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

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

	void _paintItem(const QString &html,
					QPainter *painter,
					const QStyleOptionViewItem &option) const;
};

#endif // NOTEITEMDELEGATE_H
