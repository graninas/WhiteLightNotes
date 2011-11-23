#include "noteitemdelegate.h"

#include <QRect>
#include <QTextDocument>
#include <QLabel>

#include <QAbstractTextDocumentLayout>

// http://stackoverflow.com/questions/1956542/how-to-make-item-view-render-rich-html-text-in-qt

const int TAGS_FIELD_HEIGHT = 20;

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
	QStyleOptionViewItemV4 options = option;
	initStyleOption(&options, index);
	QRect clip(0, 0, options.rect.width(), options.rect.height());

	painter->save();
	options.text = "";
	options.widget->style()->drawControl(QStyle::CE_ItemViewItem,
										 &options,
										 painter);
	QTextDocument doc;
	doc.setHtml(htmlText);
	painter->translate(options.rect.left(), options.rect.top());
	doc.drawContents(painter, clip);
	painter->restore();
}

QSize NoteItemDelegate::sizeHint(const QStyleOptionViewItem &option,
								 const QModelIndex &index) const
{
	QString htmlText = index.data().toString();
	QStyleOptionViewItemV4 options = option;
	QTextDocument doc;

	initStyleOption(&options, index);
	doc.setHtml(htmlText);
	doc.setTextWidth(options.rect.width());
	return QSize(doc.idealWidth(), doc.size().height());
}
