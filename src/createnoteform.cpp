#include "createnoteform.h"
#include "ui_createnoteform.h"

#include <QFont>

#include <QString>
#include <QDateTime>

#include <QDebug>

#include "handlers/notehandler.h"
#include "handlers/tagednotehandler.h"
#include "handlers/taghandler.h"

CreateNoteForm::CreateNoteForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNoteForm)
{
    ui->setupUi(this);

	ui->te_NoteHtmlText->setUndoRedoEnabled(true);

	_okEnterShortcut.setShortcut (QKeySequence(Qt::CTRL + Qt::Key_Enter));
	_okReturnShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
	_okAndNewEnterShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Return));
	_okAndNewReturnShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Enter));
	_cancelShortcut.setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Escape));

	connect(&_okEnterShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okReturnShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okAndNewEnterShortcut, SIGNAL(activated()), this, SLOT(finishAndNew()));
	connect(&_okAndNewReturnShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_cancelShortcut, SIGNAL(activated()), this, SLOT(cancelCreation()));
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
}

void CreateNoteForm::adjustButtons(const QTextCharFormat &format)
{
	if (format.fontWeight() > static_cast<int>(QFont::Normal)) ui->actionBold->setChecked(true);
	else ui->actionBold->setChecked(false);

	if (format.fontItalic()) ui->actionItalic->setChecked(true);
	else ui->actionItalic->setChecked(false);

	if (format.fontUnderline()) ui->actionUnderline->setChecked(true);
	else ui->actionUnderline->setChecked(false);
}

void CreateNoteForm::setBold(bool bold)
{
	if (bold) ui->te_NoteHtmlText->setFontWeight(QFont::Bold);
	else      ui->te_NoteHtmlText->setFontWeight(QFont::Normal);
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

void CreateNoteForm::_createNote()
{
	QString note = ui->te_NoteHtmlText->toHtml();
	QVariant noteID = NoteHandler::createNote(note, QDateTime::currentDateTime());
	Q_ASSERT(!noteID.isNull());

	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TagedNoteHandler::deleteTagedNotes(noteID);

	QStringList tagsList = ui->le_Tags->text().split(',', QString::SkipEmptyParts);

	if (tagsList.isEmpty())
		tagsList << QString("untaged");

	foreach (QString tag, tagsList)
		TagedNoteHandler::createTagedNote(_createTag(tag), noteID);
}

QVariant CreateNoteForm::_createTag(const QString &tagName)
{
	Qst::QstPlainQueryModel model;
	TagHandler th;
	th.setQuery(tagBatch());
	th.setModel(&model);
	th.updatePlaceholder("name", tagName);
	th.reload();
	QVariant tagID = th.fieldValue("id");

	if (tagID.isNull()) return TagHandler::createTag(tagName);
	return tagID;
}

void CreateNoteForm::_setShortcutsEnabled(bool enabled)
{
	_okEnterShortcut.setEnabled(enabled);
	_okReturnShortcut.setEnabled(enabled);
	_okAndNewEnterShortcut.setEnabled(enabled);
	_okAndNewReturnShortcut.setEnabled(enabled);
	_cancelShortcut.setEnabled(enabled);
}
