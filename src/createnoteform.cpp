#include "createnoteform.h"
#include "ui_createnoteform.h"

#include <QFont>

#include <QString>
#include <QDateTime>
#include <QMenu>

#include <QToolButton>
#include <QComboBox>

#include <QDebug>

#include "handlers/notehandler.h"
#include "handlers/taggednotehandler.h"
#include "handlers/taghandler.h"

const int FONT_SIZE_CHANGE_VALUE = 10;
const int SPACES_COUNT = 18; // Due to QTBUG

CreateNoteForm::CreateNoteForm(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::CreateNoteForm),
	_textColorCombobox(NULL)
{
    ui->setupUi(this);

	ui->te_NoteHtmlText->setUndoRedoEnabled(true);

	_cancelShortcut        .setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Escape));
	_okEnterShortcut       .setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Enter));
	_okReturnShortcut      .setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
	_okAndNewEnterShortcut .setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Return));
	_okAndNewReturnShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Enter));

	connect(&_okEnterShortcut,        SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okReturnShortcut,       SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okAndNewEnterShortcut,  SIGNAL(activated()), this, SLOT(finishAndNew()));
	connect(&_okAndNewReturnShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_cancelShortcut,         SIGNAL(activated()), this, SLOT(cancelCreation()));

	_colorMap.insert(0, ColorName("black",     QColor(0,0,0)));
	_colorMap.insert(1, ColorName("blue",      QColor(0,0,255)));
	_colorMap.insert(2, ColorName("darkgreen", QColor(0,125,0)));
	_colorMap.insert(3, ColorName("darkgrey",  QColor(127,127,127)));
	_colorMap.insert(4, ColorName("green",     QColor(0,0,255)));
	_colorMap.insert(5, ColorName("lightblue", QColor(0,255,255)));
	_colorMap.insert(6, ColorName("magenta",   QColor(255,0,255)));
	_colorMap.insert(7, ColorName("red",       QColor(255,0,0)));
	_colorMap.insert(8, ColorName("white",     QColor(255,255,255)));
	_colorMap.insert(9, ColorName("yellow",    QColor(255,255,0)));

	_textColorCombobox = new QComboBox(this);
	foreach(int key, _colorMap.keys())
	{
		ColorName cname = _colorMap[key];
		QString name = cname.first;
		QString capedName = name.at(0).toUpper() + name.mid(1);
		_textColorCombobox->addItem(QIcon(":icons/resources/" + name + ".ico"), capedName, name);
	}
	ui->editToolBar->addWidget(_textColorCombobox);

	QObject::connect(_textColorCombobox, SIGNAL(activated(int)),
					 this, SLOT(setForegroundColor(int)));
}

CreateNoteForm::~CreateNoteForm()
{
    delete ui;
}

void CreateNoteForm::setNoteTemplate(const QString &noteTemplate)
{
	_noteTemplate = noteTemplate;
}

void CreateNoteForm::setNoteTextTemplate(const QString &noteTextTemplate)
{
	_noteTextTemplate = noteTextTemplate;
}

void CreateNoteForm::setHtmlHeaderFooter(const QString &header, const QString &footer)
{
	_htmlHeader = header;
	_htmlFooter = footer;
}

void CreateNoteForm::resetEditFields()
{
	ui->te_NoteHtmlText->setHtml(_noteTextTemplate);
	_setShortcutsEnabled(true);
	ui->te_NoteHtmlText->setFocus();
}

void CreateNoteForm::adjustButtons(const QTextCharFormat &format)
{
	if (format.fontWeight() > static_cast<int>(QFont::Normal)) ui->actionBold->setChecked(true);
	else ui->actionBold->setChecked(false);

	if (format.fontItalic()) ui->actionItalic->setChecked(true);
	else ui->actionItalic->setChecked(false);

	if (format.fontUnderline()) ui->actionUnderline->setChecked(true);
	else ui->actionUnderline->setChecked(false);

	_adjustColorButtons(format);
}

void CreateNoteForm::setBold(bool bold)
{
	if (bold) ui->te_NoteHtmlText->setFontWeight(QFont::Bold);
	else      ui->te_NoteHtmlText->setFontWeight(QFont::Normal);
}

void CreateNoteForm::setForegroundColor(const int &colorIndex)
{
	ui->te_NoteHtmlText->setTextColor(_colorMap[colorIndex].second);
}

void CreateNoteForm::finishCreation()
{
	_setShortcutsEnabled(false);
	_createNote();
	emit noteCreated();
	this->close();
}

void CreateNoteForm::finishAndNew()
{
	_setShortcutsEnabled(false);
	_createNote();
	emit noteCreated();
	resetEditFields();
	ui->te_NoteHtmlText->setFocus();
}

void CreateNoteForm::cancelCreation()
{
	_setShortcutsEnabled(false);
	this->close();
}

void CreateNoteForm::incFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() + FONT_SIZE_CHANGE_VALUE);
}

void CreateNoteForm::decFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() - FONT_SIZE_CHANGE_VALUE);
}

void CreateNoteForm::_createNote()
{
	QString noteTitle  = ui->le_Title->text();
	QString noteHtml   = ui->te_NoteHtmlText->toHtml();
	QString noteSimple = ui->te_NoteHtmlText->toPlainText();
	QDateTime dateTime = QDateTime::currentDateTime();
	QString noteComplex = _noteComplexHtml(noteTitle, noteHtml, dateTime, _tagInfoList());

	QVariant noteID    = NoteHandler::createNote(noteTitle,
												 noteHtml,
												 noteSimple,
												 dateTime,
												 noteComplex);
	Q_ASSERT(!noteID.isNull());
	_updateTags(noteID);
}

void CreateNoteForm::_updateTags(const QVariant &noteID)
{
	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TaggedNoteHandler::deleteTaggedNotes(noteID);
	TagInfoList tagInfoList = _tagInfoList();

	TagInfoList::const_iterator iter = tagInfoList.begin();
	while (iter != tagInfoList.end())
	{
		QString simpleTagName = iter->first.simplified();
		if (!simpleTagName.isEmpty())
		{
			QVariant tagID = TagHandler::createTag(simpleTagName, iter->second);
			TaggedNoteHandler::createTaggedNote(tagID, noteID);
		}
		iter++;
	}
}

CreateNoteForm::TagInfoList CreateNoteForm::_tagInfoList()
{
	QStringList tagNamesList = ui->le_Tags->text().split(',', QString::SkipEmptyParts);
	TagInfoList tagInfoList;
	tagInfoList << TagInfo("All", 0);

	// If no tags entered, it should be untagged.
	if (tagNamesList.isEmpty())
		tagInfoList << TagInfo("Untagged", 1);

	foreach (QString tagName, tagNamesList)
		if (tagName != "All" && tagName != "Untagged")
			tagInfoList << TagInfo(tagName, 2);

	return tagInfoList;
}

QString CreateNoteForm::_tagsText(const TagInfoList &tagInfoList) const
{
	QString tags;
	for (int i=0; i < tagInfoList.count(); ++i)
		{
			tags += tagInfoList[i].first;
			if (i < (tagInfoList.count()-1))
				tags += ", ";
		}
	return tags;
}

QString CreateNoteForm::_noteComplexHtml(const QString &noteTitle,
										 const QString &noteHtml,
										 const QDateTime &datetime,
										 const TagInfoList &tagInfoList) const
{
	QString onlyHtmlText = _cutHtmlHeaders(ui->te_NoteHtmlText->toHtml());
	QString res = _noteTemplate;
	QString tags = _tagsText(tagInfoList);

	res.replace("%title_bkground_color%", "#fed3ce");
	res.replace("%title_text_color%", "#7b5955");
	res.replace("%title_datetime_color%", "#7b5955");
	res.replace("%note_bgcolor%", "#ffffff");
//	res.replace("%note_text_color%", "#000000");
	res.replace("%tags_bgcolor%", "#ffffff");
	res.replace("%tags_text_color%", "#a28a88");

	res.replace("%title_text%", noteTitle);
	res.replace("%title_datetime%", datetime.toString(Qst::DEFAULT_DATE_TIME_FORMAT));
	res.replace("%note_text%", onlyHtmlText);
	res.replace("%tags_text%", tags);

	return res;
}

//QString CreateNoteForm::_spaceAlignedTitle(const QString &noteTitle,
//										   const QDateTime &datetime) const
//{
//	QString spaces = " ";
//	QString res = noteTitle.simplified();
//	res += spaces.repeated(SPACES_COUNT - res.length());
//	res += datetime.toString(Qst::DEFAULT_DATE_TIME_FORMAT);
//	return res;
//}

void CreateNoteForm::_setShortcutsEnabled(bool enabled)
{
	_okEnterShortcut.setEnabled(enabled);
	_okReturnShortcut.setEnabled(enabled);
	_okAndNewEnterShortcut.setEnabled(enabled);
	_okAndNewReturnShortcut.setEnabled(enabled);
	_cancelShortcut.setEnabled(enabled);
}

QString CreateNoteForm::_cutHtmlHeaders(const QString &str) const
{
	QString res = str;
	int idx = res.indexOf("<body");
	while(res[idx] != QChar('>'))
		idx++;
	res.remove(0, idx+1);
	res = res.left(res.length() - QString("</body></html>").length());
	qDebug() << "\nSource html string: \n" << str;
	qDebug() << "\nCuted html string: \n" << res;
	return res;
}

void CreateNoteForm::_adjustColorButtons(const QTextCharFormat &format)
{
	QColor foregroudColor = format.foreground().color();

	foreach (int key, _colorMap.keys())
	{
		if (_colorMap[key].second == foregroudColor)
		{
			_textColorCombobox->setCurrentIndex(key);
			break;
		}
	}
}
