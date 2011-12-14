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

#include "editnoteform.h"
#include "ui_editnoteform.h"

#include <QFont>
#include <QString>
#include <QDateTime>
#include <QMenu>
#include <QToolButton>
#include <QComboBox>
#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "handlers/taghandler.h"

EditNoteForm::EditNoteForm(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::CreateNoteForm),
	_textColorCombobox(NULL)
{
    ui->setupUi(this);

	ui->te_NoteHtmlText->setUndoRedoEnabled(true);

	_cancelShortcut        .setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Escape));
	_okEnterShortcut       .setShortcut(QKeySequence(Qt::CTRL  + Qt::Key_Enter));
	_okReturnShortcut      .setShortcut(QKeySequence(Qt::CTRL  + Qt::Key_Return));
	_okAndNewEnterShortcut .setShortcut(QKeySequence(Qt::CTRL  + Qt::SHIFT + Qt::Key_Return));
	_okAndNewReturnShortcut.setShortcut(QKeySequence(Qt::CTRL  + Qt::SHIFT + Qt::Key_Enter));

	connect(&_okEnterShortcut,        SIGNAL(activated()), this, SLOT(finish()));
	connect(&_okReturnShortcut,       SIGNAL(activated()), this, SLOT(finish()));
	connect(&_cancelShortcut,         SIGNAL(activated()), this, SLOT(cancel()));

	_colorMap.insert(0,  ColorName("black",     QColor(0,0,0)));
	_colorMap.insert(1,  ColorName("blue",      QColor(0,0,255)));
	_colorMap.insert(2,  ColorName("darkgreen", QColor(0,127,0)));
	_colorMap.insert(3,  ColorName("darkgrey",  QColor(127,127,127)));
	_colorMap.insert(4,  ColorName("green",     QColor(0,255,0)));
	_colorMap.insert(5,  ColorName("lightblue", QColor(0,255,255)));
	_colorMap.insert(6,  ColorName("magenta",   QColor(255,0,255)));
	_colorMap.insert(7,  ColorName("red",       QColor(255,0,0)));
	_colorMap.insert(8,  ColorName("white",     QColor(255,255,255)));
	_colorMap.insert(9,  ColorName("yellow",    QColor(255,255,0)));
	_colorMap.insert(10, ColorName("orange",    QColor(255,127,0)));

	_textColorCombobox = new QComboBox(this);
	foreach(int key, _colorMap.keys())
	{
		ColorName cname = _colorMap[key];
		QString name = cname.first;
		QString capedName = name.at(0).toUpper() + name.mid(1);
		_textColorCombobox->addItem(QIcon(":icons/resources/edit-color-" + name + ".ico"), capedName, name);
	}
	ui->editToolBar->addWidget(_textColorCombobox);

	QObject::connect(_textColorCombobox, SIGNAL(activated(int)), this, SLOT(setForegroundColor(int)));

	_tagHandler.setQuery(tagBatch());
	_tagHandler.setModel(&_tagModel);
	_tagHandler.setTableView(ui->tv_Tags);
	_tagModel.setTagColumnIndex(_tagHandler.fieldColumnIndex("info_tag"));
	_tagModel.setTagSelectable("All",      false);
	_tagModel.setTagSelectable("Untagged", false);
}

EditNoteForm::~EditNoteForm()
{
    delete ui;
}


void EditNoteForm::setSettings(const SettingsMap &settings)
{
	_changeFontSizeStep  = settings[S_CHANGE_FONT_SIZE_STEP].toInt();
	_defaultColorTheme   = settings[S_DEFAULT_COLOR_THEME].toString();
	_newNoteTextTemplate = _loadFile(settings[S_NEW_NOTE_TEXT_TEMPLATE].toString());
	_noteShowingTemplate = _loadFile(settings[S_NOTE_SHOWING_TEMPLATE] .toString());
}

void EditNoteForm::setNote(const Note &note)
{
	_note = note;
	_setContents(_note);
}

void EditNoteForm::loadAll()
{
	_tagHandler.reload();
	adjustTags(_selectedTags, _deselectedTags);

	QObject::connect(ui->tv_Tags->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
					 this, SLOT(adjustTags(QItemSelection,QItemSelection)));
	ui->le_Title->setFocus();
}

void EditNoteForm::adjustButtons(const QTextCharFormat &format)
{
	if (format.fontWeight() > static_cast<int>(QFont::Normal)) ui->actionBold->setChecked(true);
	else ui->actionBold->setChecked(false);

	if (format.fontItalic()) ui->actionItalic->setChecked(true);
	else ui->actionItalic ->setChecked(false);

	if (format.fontUnderline()) ui->actionUnderline->setChecked(true);
	else ui->actionUnderline->setChecked(false);

	_adjustColorButtons(format);
}

void EditNoteForm::setBold(bool bold)
{
	if (bold) ui->te_NoteHtmlText->setFontWeight(QFont::Bold);
	else      ui->te_NoteHtmlText->setFontWeight(QFont::Normal);
}

void EditNoteForm::setForegroundColor(const int &colorIndex)
{
	ui->te_NoteHtmlText->setTextColor(_colorMap[colorIndex].second);
	ui->te_NoteHtmlText->setFocus();
}

void EditNoteForm::incFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() + _changeFontSizeStep);
}

void EditNoteForm::decFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() - _changeFontSizeStep);
}

void EditNoteForm::adjustTags(QItemSelection selected, QItemSelection deselected)
{
	foreach (QModelIndex idx, selected.indexes())
		_note.appendTag(_tagHandler.fieldValue("name", idx).toString());
	foreach (QModelIndex idx, deselected.indexes())
		_note.removeTag(_tagHandler.fieldValue("name", idx).toString());

	_selectedTags = selected;
	_deselectedTags = deselected;

	ui->le_Tags->setText(_note.tags(true, true));
}

void EditNoteForm::adjustTags()
{
	_note.clearTags();
	QStringList tags = ui->le_Tags->text().split(",", QString::SkipEmptyParts);
	foreach (QString tag, tags)
		if (!tag.simplified().isEmpty())
			_note.appendTag(tag.simplified());

	adjustTags(_selectedTags, _deselectedTags);
}

void EditNoteForm::finish()
{
	if (_note.noteID().isNull())
		_note.create(ui->le_Title->text(),
					 ui->te_NoteHtmlText->toPlainText(),
					 ui->te_NoteHtmlText->toHtml(),
					 QDateTime::currentDateTime(),
					 _noteShowingTemplate);
	else
		_note.update(ui->le_Title->text(),
					 ui->te_NoteHtmlText->toPlainText(),
					 ui->te_NoteHtmlText->toHtml(),
					 ui->dte_Date->dateTime(),
					 _noteShowingTemplate);
	emit finishNote(_note);
}

void EditNoteForm::cancel()
{
	_note = Note();
	emit cancelNoteEditing();
}

void EditNoteForm::_setShortcutsEnabled(bool enabled)
{
	_okEnterShortcut       .setEnabled(enabled);
	_okReturnShortcut      .setEnabled(enabled);
	_okAndNewEnterShortcut .setEnabled(enabled);
	_okAndNewReturnShortcut.setEnabled(enabled);
	_cancelShortcut        .setEnabled(enabled);
}

void EditNoteForm::_adjustColorButtons(const QTextCharFormat &format)
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

void EditNoteForm::_setContents(const Note &note)
{
	if (note.noteID().isValid())
	{
		ui->le_Title->setText(note.title());
		ui->te_NoteHtmlText->setHtml(note.htmlText());
		ui->dte_Date->show();
		ui->l_Date->show();
		ui->dte_Date->setDateTime(note.date());
	}
	else
	{
		ui->le_Title->setText(QString());
		ui->te_NoteHtmlText->setHtml(_newNoteTextTemplate);
		ui->dte_Date->hide();
		ui->l_Date->hide();
	}
}

QString EditNoteForm::_loadFile(const QString &fileName) const
{
	QFile file(fileName);
	QString res;
	if (file.open(QFile::ReadOnly))
		res = file.readAll();
	return res;
}
