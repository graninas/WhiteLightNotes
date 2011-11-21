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

void CreateNoteForm::resetEditFields()
{
	ui->te_NoteHtmlText->setHtml(_noteTemplate);
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
	QString noteHtml   = ui->te_NoteHtmlText->toHtml();
	QString noteSimple = ui->te_NoteHtmlText->toPlainText();

	QVariant noteID = NoteHandler::createNote(noteHtml,
											  noteSimple,
											  QDateTime::currentDateTime());
	Q_ASSERT(!noteID.isNull());

	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TaggedNoteHandler::deleteTaggedNotes(noteID);

	QStringList tagNamesList = ui->le_Tags->text().split(',', QString::SkipEmptyParts);
	TagInfoList tagInfoList;

	if (tagNamesList.isEmpty())
		tagInfoList << TagInfo("Untagged", 1);
	tagInfoList << TagInfo("All", 0);

	foreach (QString tagName, tagNamesList)
	{
		if (tagName != "All" && tagName != "Untagged")
			tagInfoList << QPair<QString, int>(tagName, 2);
	}

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

void CreateNoteForm::_setShortcutsEnabled(bool enabled)
{
	_okEnterShortcut.setEnabled(enabled);
	_okReturnShortcut.setEnabled(enabled);
	_okAndNewEnterShortcut.setEnabled(enabled);
	_okAndNewReturnShortcut.setEnabled(enabled);
	_cancelShortcut.setEnabled(enabled);
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
