#include "noteitemdelegate.h"

#include <QTextEdit>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "private/qtextdocumentlayout_p.h"
#include "private/qtextcontrol_p.h"

#include <QPaintEngine>
#include <QRect>

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
	if (qVariantCanConvert<QString>(index.data()))
	{
		QString data = qVariantValue<QString>(index.data());

		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.text());

		_paintItem(data, painter, option);
	} else
		QStyledItemDelegate::paint(painter, option, index);
}
QSize NoteItemDelegate::sizeHint(const QStyleOptionViewItem &option,
								 const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}

void NoteItemDelegate::_paintItem(const QString &html,
								  QPainter *painter,
								  const QStyleOptionViewItem &option) const
{
	QTextControl *control = new QTextControl();
	control->setHtml(html);
	QTextDocument *doc = control->document();
	QTextDocumentLayout *layout = qobject_cast<QTextDocumentLayout *>(doc->documentLayout());

	QRect rect = option.rect;

	if (layout)
		layout->setViewport(rect);

		painter->save();
		if (rect.isValid())
			painter->setClipRect(rect, Qt::IntersectClip);
		QAbstractTextDocumentLayout::PaintContext ctx;
		ctx.clip = rect;
		ctx.palette = option.palette;
		doc->documentLayout()->draw(painter, ctx);
		painter->restore();

	if (layout)
		layout->setViewport(QRect());
}
