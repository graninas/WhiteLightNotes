#include "noteitemdelegate.h"

#include <QTextEdit>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "private/qtextdocumentlayout_p.h"
#include "private/qtextcontrol_p.h"

#include <QPaintEngine>
#include <QRect>

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
	QStyleOptionViewItemV4 options = option;
	initStyleOption(&options, index);

	painter->save();

	QString htmlText = index.data().toString();

	QTextDocument doc;
	doc.setHtml(htmlText);

	options.text = "";
	options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

	painter->translate(options.rect.left(), options.rect.top());
	QRect clip(0, 0, options.rect.width(), options.rect.height());
	doc.drawContents(painter, clip);

	painter->restore();
}

QSize NoteItemDelegate::sizeHint(const QStyleOptionViewItem &option,
								 const QModelIndex &index) const
{
	QStyleOptionViewItemV4 options = option;
	initStyleOption(&options, index);

	QTextDocument doc;
	doc.setHtml(options.text);
	doc.setTextWidth(options.rect.width());
	return QSize(doc.idealWidth(), doc.size().height());
}

void NoteItemDelegate::_paintItem(const QString &html,
								  QPainter *painter,
								  const QStyleOptionViewItem &option) const
{
}

/*
 if (qVariantCanConvert<QString>(index.data()))
 {
	 QString data = qVariantValue<QString>(index.data());

	 if (option.state & QStyle::State_Selected)
		 painter->fillRect(option.rect, option.palette.text());

	 _paintItem(data, painter, option);
 } else
	 QStyledItemDelegate::paint(painter, option, index);
*/
/*
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
	 layout->setViewport(QRect());*/
